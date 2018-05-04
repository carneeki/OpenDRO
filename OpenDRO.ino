#include "config.h"
#include "libraries/LedControl/src/LedControl.cpp"
#include "libraries/LedControl/src/LedControl.h"

#define TESTING 1 // if true, certain things for bench testing
                  // will be turned on

#define NOP __asm__("nop\n\t");

unsigned long int prev_display_time = 0;
unsigned long int prev_button_time[BUTTON_COUNT];

volatile long int count_z;
volatile long int count_x;
volatile long int count_w;
volatile long int count_c;
volatile bool lamp = false;

volatile byte prevPort = 0;   // previous axis port state
volatile byte curPort = PIND; // current axis port state

bool units = true; // display units in mm (false = inches)

LedControl leds = LedControl(PIN_LED_DATA, PIN_LED_CLK, PIN_LED_CS);
int buttons[BUTTON_COUNT] = { PIN_Z_RESET, PIN_X_RESET, PIN_W_RESET, PIN_C_RESET, PIN_UNITS };
boolean button_state[BUTTON_COUNT];
boolean last_button_readings[BUTTON_COUNT];

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
  cli();             // clear interrupts during setup
  DDRB = 0b11011100; // PB0..7 as inputs (except PB2,3,4,6,7)
  DDRC = 0b00000000; // PC0 as input
  DDRD = 0b00000000; // PD0..7 (PCI2) as inputs

  PORTB |= 0b00100011; // PB0..7 pull-up resistor (except PB2,3,4,6,7)
  PORTC |= 0b11111111; // PC0..7 pull-up resistor
  PORTD |= 0b11111111; // PD0..7 pull-up resistor

  PCICR |= (1 << PCIE2) | (1 << PCIE1) | (1 << PCIE0);
  PCMSK2 = 0b11111111; // PD0..7 (PCI2) pin enable
  PCMSK1 = 0b00000010; // PC1 pin enable
  sei();               // re-enable interrupts

  for (int i = 0; i < leds.getDeviceCount(); i++)
  {
    leds.shutdown(i, false);
    leds.setIntensity(i, DISPLAY_INTENSITY);
    leds.clearDisplay(i);
  }

  for(int i=0; i<=9; i++)
  {
    leds.setChar(0, 0, i, false);
    delay(LOOP_DELAY);
    leds.clearDisplay(0);
  }

  for( int i=0; i<=BUTTON_COUNT-1; i++)
  {
    pinMode(buttons[i], INPUT_PULLUP);
  }

  prevPort = PIND;
}

void loop()
{
  unsigned long int current_time = millis();

  // don't update too frequently or
  // people will spaz out on tiny changes
  // but don't use delay in case loop is needed for other stuff
  if(current_time - prev_display_time >= LOOP_DELAY)
  {
    prev_display_time = current_time;
    writeDisplay(0, &count_z, TICK_Z_MM);
  }

  if(!digitalRead(PIN_Z_RESET)) count_z = 0;
  if(!digitalRead(PIN_X_RESET)) count_x = 0;
  if(!digitalRead(PIN_W_RESET)) count_w = 0;
  if(!digitalRead(PIN_C_RESET)) count_c = 0;
  if(!digitalRead(PIN_UNITS)) units = !units;
}

void writeDisplay(uint8_t display, volatile long int* count, double ticks)
{
  char buf[10];
  double dist (*count * ticks);
  byte dp = 0;
  if (!units)
    dist = dist/25.4;

  leds.clearDisplay(display);

  dtostrf(dist, 9, 4, buf);     // TODO: make me better
  snprintf(buf, 9, "%9s", buf); // this approach takes up substantial pgmmem

  // NOTE: MUST be of the form
  // [-]ddd.ddd
  for (int i = 0; i <= 8; i++)
  {
    if (buf[i] == '.')
      continue;

    if (i < 8 && buf[i + 1] == '.')
    {
      leds.setChar(display, 7 - i + dp, (byte)buf[i], true);
      dp = 1;
    }
    else
      leds.setChar(display, 7 - i + dp, (byte)buf[i], false);
  }
}

// port D got a tick
ISR(PCINT2_vect)
{
  uint8_t delta = (prevPort ^ PIND);

  if (delta & 0x03) // Z axis // TODO: checkme... if I work, use me below. Saves an OR and a compare per if()
    if (axisTick(0x00, &count_z) != 0)
      prevPort = PIND;

  if (delta == 0x04 || delta == 0x08) // X axis
    if (axisTick(0x0C, &count_x) != 0)
      prevPort = PIND;

  if (delta == 0x10 || delta == 0x20) // W axis
    if (axisTick(0x30, &count_w) != 0)
      prevPort = PIND;

  if (delta == 0x40 || delta == 0x80) // C axis
    if (axisTick(0xC0, &count_c) != 0)
      prevPort = PIND;
}


ISR(PCINT1_vect)
{
/*
  switch(PINC & 0x02)
  {
    case 0x01: // Z index
    break;
    case 0x02: // Z zero
      count_z = 0;
    break;
    case 0x04: // X index
    break;
    case 0x08: // X zero
      count_x = 0;
    break;
    case 0x10: // W index
    break;
    case 0x20: // W zero
      count_w = 0;
    break;
  }
*/
}


int8_t axisTick(uint8_t shift, volatile long int *count)
{
  uint8_t prevAxis = ((prevPort >> shift) & 0x03);
  uint8_t curAxis = ((PIND >> shift) & 0x03);
  *count += transition[prevAxis][curAxis];
  return transition[prevAxis][curAxis]; // TODO: check me: return *count;
                                        // saves 10 bytes... ~ 2 instructions?
}
