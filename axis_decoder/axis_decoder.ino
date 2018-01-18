/**
 * Name:    axis_decoder.ino
 * Author:  Adam Carmichael <carneeki@carneeki.net>
 * Purpose: Decode quadrature (fast) and store counts until
 *          polled by another chip using I2C. Counts are unitless, no
 *          millimetres, inches, or smoots here, let another chip handle that.
 * Chip:    ATtiny 85. Use TinyCore + Arduino environment. See
 *          TinyCore: https://github.com/SpenceKonde/ATTinyCore
 *          ATtiny85 datasheet: http://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-2586-AVR-8-bit-Microcontroller-ATtiny25-ATtiny45-ATtiny85_Datasheet.pdf
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <Wire.h>

/* ATtiny85 PDIP package:
 *                  _____
 * [PCINT5] PB5  1 |     | 8 Vcc
 * [PCINT3] PB3  2 |     | 7 PB2 [PCINT2]
 * [PCINT4] PB4  3 |     | 6 PB1 [PCINT1]
 *          Gnd  4 |_____| 4 PB0 [PCINT0]
 */
const uint8_t      addr       = 8;      // I2C slave address
const unsigned int resetDelta = 10000U; // counts between encoder resets

// LEAVE EVERYTHING BELOW WELL ALONE
bool          dir        = false; // true = direction increasing
volatile long count      = 0L;    // reported encoder count
volatile long lastRcount = 0L;    // encoder position at last reset
volatile bool stateSigA  = false; // signal A value
volatile bool stateSigB  = false; // signal B value
volatile bool lastSigA   = false; // previous signal A value
volatile bool lastSigB   = false; // previous signal B value

void setup()
{
  Wire.begin(addr);
  Wire.onRequest(sendCount);
  cli(); // disable interrupts during setup()

  attachInterrupt(PCINT5,tickA, CHANGE);
  attachInterrupt(PCINT3,tickB, CHANGE);
  attachInterrupt(PCINT4,tickR, RISING);

  stateSigA = digitalRead(PB5);
  stateSigB = digitalRead(PB3);

  sei(); // enable interrupts
}

void loop()
{
  // empty loop
}

void sendCount()
{
  Wire.write(count);
}


// called on encoder tick A
void tickA()
{
  stateSigA = digitalRead(PB5);

  if(stateSigB ^ lastSigA)
  {
    count++;
    dir = true;
  }
  else
  {
    count--;
    dir = false;
  }

  lastSigA = stateSigA;
}

// called on encoder tick B
void tickB()
{
  stateSigB = digitalRead(PB3);

  if(stateSigA ^ lastSigB)
  {
    count++;
    dir = true;
  }
  else
  {
    count--;
    dir = false;
  }

  lastSigB = stateSigB;
}

// called on encoder tick R
void tickR()
{
  if(count && dir)
    count = lastRcount + resetDelta;
  if(count && !dir)
    count = lastRcount - resetDelta;

  lastRcount = count;
}
