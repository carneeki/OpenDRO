#include "config.h"
#include "libraries/LedControl/src/LedControl.cpp"
#include "libraries/LedControl/src/LedControl.h"

#define NOP __asm__("nop\n\t");

volatile int count_z;
volatile long int count_x;
volatile long int count_w;
volatile long int count_c;
volatile bool lamp = true;

volatile byte prevPort = 0;   // previous axis port state
volatile byte curPort = PIND; // current axis port state

bool units = true; // display units in mm (false = inches)
char buf[9];
byte dp = 0;

LedControl leds = LedControl(PIN_LED_DATA, PIN_LED_CLK, PIN_LED_CS);

/* Gray code transition table:
 * curAxis++ = return 1, curAxis-- = return -1, else no change
 * prevAxis     curAxis++     curAxis--
 * ...00       ...01          ...10
 * ...01       ...11          ...00
 * ...11       ...10          ...01
 * ...10       ...00          ...11
 */
const volatile int8_t transition[4][4] = {
    // 00g  01g  10g  11g <-- curAxis
    {0, 1, -1, 0}, // 00g  prevAxis
    {-1, 0, 0, 1}, // 01g
    {1, 0, 0, -1}, // 10g
    {0, -1, 1, 0}, // 11g
};

void setup()
{
  for (int i = 0; i < leds.getDeviceCount(); i++)
  {
    leds.shutdown(i, false);
    leds.setIntensity(i, DISPLAY_INTENSITY);
    leds.clearDisplay(i);
  }

  pinMode(A5, OUTPUT);    // TODO: send power to encoder for bench testing
  digitalWrite(A5, HIGH); // TODO: in final circuit REMOVEME

  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);

  cli();             // clear interrupts during setup
  DDRD = 0b00000000; // PD0..7 (PCI2) as inputs
  DDRC = 0b11111110; // PC0 as input

  PORTD |= 0b11111111; // PD0..7 pull-up resistor
  PORTC |= 0b11111111; // PC0 pull-up resistor

  PCICR |= (1 << PCIE2) | (1 << PCIE1) | (1 << PCIE0);
  PCMSK2 = 0b11111111; // PD0..7 (PCI2) pin enable
  sei();               // re-enable interrupts

  prevPort = PIND;
}

void loop()
{
  // DEBUG START
  // lamp = (count_z == 0) ? false:true;
  digitalWrite(13, lamp);

  leds.clearDisplay(0);
  snprintf(buf, 9, "%08i", count_z);

  for (int i = 0; i < 8; i++)
    leds.setChar(0, 7 - i, buf[i], false);

  // DEBUG END

  // dtostrf(count_z, 9, 3, buf);   // TODO: I take up ~2k0 of program space
  // snprintf(buf, 10, "%8s", buf); // TODO: I take up ~1k6 of program space

  delay(5); // don't update too frequently or
            // people will spaz out on tiny changes
}

// port D got a tick
ISR(PCINT2_vect)
{
  uint8_t delta = (prevPort ^ PIND);

  if (delta == 0x01 || delta == 0x02) // Z axis
    if (axisTick(0x00, &count_z) != 0)
      prevPort = PIND;

  if (delta == 0x04 || delta == 0x08) // X axis
    if (axisTick(0x0C, &count_z) != 0)
      prevPort = PIND;

  if (delta == 0x10 || delta == 0x20) // W axis
    if (axisTick(0x30, &count_z) != 0)
      prevPort = PIND;

  if (delta == 0x40 || delta == 0x80) // C axis
    if (axisTick(0xC0, &count_z) != 0)
      prevPort = PIND;
}

int8_t axisTick(uint8_t shift, volatile int *count)
{
  uint8_t prevAxis = ((prevPort >> shift) & 0x03);
  uint8_t curAxis = ((PIND >> shift) & 0x03);
  *count += transition[prevAxis][curAxis];
  return transition[prevAxis][curAxis];
}
