#include "config.h"
#include "libraries/LedControl/src/LedControl.cpp"
#include "libraries/LedControl/src/LedControl.h"

volatile long count_z;
volatile long count_x;
volatile long count_w;
volatile long count_c;
volatile bool lamp = true;

volatile byte prevPort = 0;   // previous axis port state
volatile byte curPort = PIND; // current axis port state
volatile byte delta = 0;      // change between current and prevPort

bool units = true; // display units in mm (false = inches)
char buf[9];
byte dp = 0;

LedControl leds = LedControl(PIN_LED_DATA, PIN_LED_CLK, PIN_LED_CS);

/* Gray code transition table:
 * curAxis++ = return 1, curAxis-- = return -1, anything else no change
 * prevAxis     curAxis++     curAxis--
 * ...00       ...01          ...10
 * ...01       ...11          ...00
 * ...11       ...10          ...01
 * ...10       ...00          ...11
 */
const int8_t transition[4][4] = {
    { 0,  1, -1,  0},
    {-1,  0,  0,  1},
    { 1,  0,  0, -1},
    { 0, -1,  1,  0}
};

void setup()
{
  for (int i = 0; i < leds.getDeviceCount(); i++)
  {
    leds.shutdown(i, false);
    leds.setIntensity(i, DISPLAY_INTENSITY);
    leds.clearDisplay(i);
  }

  pinMode(11, OUTPUT);    // TODO: send power to encoder for bench testing
  digitalWrite(11, HIGH); // TODO: in final circuit REMOVEME

  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  delay(100);
  digitalWrite(13, LOW);

  cli();             // clear interrupts during setup
  DDRD = 0b00000000; // PD0..7 (PCI2) as inputs
  DDRC = 0b11111110; // PC0 as input

  PORTD |= 0b11111111; // PD0..7 pull-up resistor
  PORTC |= 0b11111111; // PC0 pull-up resistor

  PCICR |= (1 << PCIE2) | (1 << PCIE1) | (1 << PCIE0);
  PCMSK2 = 0b11111111; // PD0..7 (PCI2) pin enable
  sei();               // re-enable interrupts
}

void loop()
{
  // lamp = (count_z == 0)? LOW:HIGH;
  digitalWrite(13, lamp);

  dtostrf(count_z, 9, 3, buf);   // TODO: I take up ~2k0 of program space
  snprintf(buf, 10, "%8s", buf); // TODO: I take up ~1k6 of program space

  for (int i = 0; i < 9; i++)
  {
    if (buf[i] == '.')
      continue;

    if (i < 8 && buf[i + 1] == '.')
    {
      leds.setChar(0, 8 - i + dp, (byte)buf[i], true);
      dp = 1;
    }
    else
      leds.setChar(0, 8 - i + dp, (byte)buf[i], false);
  }

  delay(5); // don't update too frequently or
            // people will spaz out on tiny changes
}

ISR(PCINT2_vect) { portTick(); }

// fast method to count axis travel
void portTick()
{
  delta = prevPort ^ PIND; // which pin changed
  switch (delta)
  {
  case 0x01: // Z axis
  case 0x02: // Z axis
    axisTick(0x00, count_z);
    break;

  case 0x04: // X axis
  case 0x08: // X axis
    axisTick(0x02, count_x);
    break;

  case 0x10: // W axis
  case 0x20: // W axis
    axisTick(0x04, count_w);
    break;

  case 0x40: // C axis
  case 0x80: // C axis
    axisTick(0x06, count_c);
    break;
  }

  prevPort = PIND; // record port state
}

volatile long *axisTick(byte shift, volatile long *count)
{
  byte prevAxis = (prevPort >> shift);
  byte curAxis = (PORTD >> shift);

  count += transition[prevAxis][curAxis];

  return count;
}
