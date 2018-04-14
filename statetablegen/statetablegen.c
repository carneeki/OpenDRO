/*
 * DO NOT USE
 *
 * State table would be about 500k in size (255x255x8 bytes)
 */
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXROWS 255

uint8_t gray_enc(uint8_t n) { return n ^ (n >> 1); }

uint8_t count(bool up, uint8_t mask, uint8_t shift, uint8_t n)
{
  //printf("0 input: 0x%02X\n", n);
  uint8_t r = (mask & n); // get just the bits we want
  //printf("1  mask: 0x%02X\n", r);
  r = r >> shift;         // shift them right
  //printf("2 shift: 0x%02X\n", r);

  switch (r)
  {
  case (0x00):
    //printf("0x%02X %s\n", r, up?"u":"d");
    r = up ? 0x01 : 0x02; // new value
    break;
  case (0x01):
    //printf("0x%02X %s\n", r, up?"u":"d");
    r = up ? 0x03 : 0x00; // new value
    break;
  case (0x03):
    //printf("0x%02X %s\n", r, up?"u":"d");
    r = up ? 0x02 : 0x01; // new value
    break;
  case (0x02):
    //printf("0x%02X %s\n", r, up?"u":"d");
    r = up ? 0x00 : 0x03; // new value
    break;
  default:
    //printf("nope r=0x%02X", r);
    break;
  }

  //printf("3 count: 0x%02X\n", r);
  r = r << shift;  // shift into position
  //printf("4 shift: 0x%02X\n", r);
  n = n & ~(mask); // mask out old value
  //printf("5 /mask: 0x%02X\n", n);
  n = n | r;       // OR the new bits into place
  //printf("6    or: 0x%02X\n", n);
  return n;        // return the value
}

int main(int argc, char **argv)
{
  int8_t **ttable;
  ttable = (int8_t**) calloc(MAXROWS, sizeof(int8_t));
  for(uint8_t i=0; i<=MAXROWS; i++)
    ttable[i] = (int8_t*) calloc(MAXROWS, sizeof(int8_t));

  for(uint8_t i=0; i<=MAXROWS; i++)
  {
    /*
    printf("0x%02X = { 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X }\n", gray_enc(i),
      count(true , 0x03, 0x00, gray_enc(i)),  // z inc
      count(false, 0x03, 0x00, gray_enc(i)),  // z dec

      count(true , 0x0C, 0x02, gray_enc(i)),  // x inc
      count(false, 0x0C, 0x02, gray_enc(i)),  // x dec

      count(true , 0x30, 0x04, gray_enc(i)),  // w inc
      count(false, 0x30, 0x04, gray_enc(i)),  // w dec

      count(true , 0xC0, 0x06, gray_enc(i)),  // c inc
      count(false, 0xC0, 0x06, gray_enc(i))   // c dec
    );
    */

//    for(int j=0; j<= MAXROWS; j++)
//      printf("ttable[%i][%i] = %i \n", i, j, ttable[i][j]);
    uint8_t j = count(true , 0x03, 0x00, gray_enc(i));
    printf("ttable[0x%02X][0x%02X]\n", i, j);
    ttable[i][count(true , 0x03, 0x00, gray_enc(i))] =  1;  // z inc
    printf("ttable[0x%02X][0x%02X] = %i \n", i, j, ttable[i][j]);
//    ttable[i][count(false, 0x03, 0x00, gray_enc(i))] = -1;  // z dec
//    ttable[i][count(true , 0x0C, 0x02, gray_enc(i))] =  1;  // x inc
//    ttable[i][count(false, 0x0C, 0x02, gray_enc(i))] = -1;  // x dec
//    ttable[i][count(true , 0x30, 0x04, gray_enc(i))] =  1;  // w inc
//    ttable[i][count(false, 0x30, 0x04, gray_enc(i))] = -1;  // w dec
//    ttable[i][count(true , 0xC0, 0x06, gray_enc(i))] =  1;  // c inc
//    ttable[i][count(false, 0xC0, 0x06, gray_enc(i))] = -1;  // c dec
  }

  return 0;
}
