/**
 * Name:    master_controller.ino
 * Author:  Adam Carmichael <carneeki@carneeki.net>
 * Purpose: Read counts from axis_decoders, process the buttons, and keep track
 *          of the distance on each axis.
 * Chip:    Probably ATmega328 or ATmega2560 (Arduino or Arduino Mega). TBD.
 */

// I2C slave addresses
const uint8_t      Xaddr      =  8; // cross slide
const uint8_t      Yaddr      =  9; //
const uint8_t      Zaddr      = 10; // carriage
const uint8_t      Waddr      = 11; // tailstock
const uint8_t      Caddr      = 11; // spindle angle
const uint8_t      Taddr      = 12; // spindle tacho
const uint8_t      Daddr      = 13; // 16x2 LCD

void setup()
{

}

void loop()
{

}

typedef struct
{
  char first [4];  // first four chars
  char last  [4];  // last four chars
  bool dp;         // decimal point in the middle
} display_pair;

// convert a float into  cccc.cccc
// range -999.999 to 9999.9999
// negatives should appear:
//                |   0.0000|
//                |  -1.0000|
//                |-999.9999|
display_pair dp_from_float(float in)
{
  display_pair ret; // return value
  int whole;        // whole part
  int frac;         // fractional part

  if(in < -999.9999 || in > 9999.9999)
  {
    ret.first = "err.";
    ret.last  = "long";
    return ret;
  }

  whole = trunc(in);

  if(in < 0) in *= -1;
  in = in - whole;

  in *= 1000;
  frac = trunc(in);

  ret.first = itoa(whole);
  ret.last  = itoa(frac);

  if( (whole < 1000 && whole > 0) || whole < -100)
    strcat(ret.first, " ");           // one space
  else if( (whole < 100 && whole > 0) || whole < -10)
    strcat(ret.first, "  ");          // two spaces
  else if( (whole < 10 && whole > 0))
    strcat(ret.first, "   ");         // three spaces

  ret.first = itoa(whole);
  ret.last  = itoa(frac);
  ret.dp = true;

  return ret;
}
