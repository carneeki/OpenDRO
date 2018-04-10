#include <math.h>

/**
 * no-decode mode data bits and corresponding line segments
 *
 *     A
 *     -
 *  F | | B
 *     -  G
 *  E | | C
 *     -D    . DP
 *
 * D7 D6 D5 D4 D3 D2 D1 D0
 * DP  A  B  C  D  E  F  G
 */
#define SEG_DP    0x80 // 1000 0000
#define SEG_A     0x40 // 0100 0000
#define SEG_B     0x20 // 0010 0000
#define SEG_C     0x10 // 0001 0000
#define SEG_D     0x08 // 0000 1000
#define SEG_E     0x04 // 0000 0100
#define SEG_F     0x02 // 0000 0010
#define SEG_G     0x01 // 0000 0001
#define SEG_EMPTY 0x00 // 0000 0000

// all
char cAll = 0xFF;

// numbers
char c0 = SEG_A|SEG_B|SEG_C|SEG_D|SEG_E|SEG_F;
char c1 =       SEG_B|SEG_C;
char c2 = SEG_A|SEG_B|      SEG_D|SEG_E|      SEG_G;
char c3 = SEG_A|SEG_B|SEG_C|SEG_D|SEG_G;
char c4 =       SEG_B|SEG_C|            SEG_F|SEG_G;
char c5 = SEG_A|      SEG_C|SEG_D|      SEG_F|SEG_G;
char c6 = SEG_A|      SEG_C|SEG_D|SEG_E|SEG_F|SEG_G;
char c7 = SEG_A|SEG_B|SEG_C;
char c8 = SEG_A|SEG_B|SEG_C|SEG_D|SEG_E|SEG_F|SEG_G;
char c9 = SEG_A|SEG_B|SEG_C|SEG_D|      SEG_F|SEG_G;

// letters
char cA = SEG_A|SEG_B|SEG_C|SEG_E|SEG_F|SEG_G;
char cb =             SEG_C|SEG_D|SEG_E|SEG_F|SEG_G;
char cC = SEG_A|            SEG_D|SEG_E|SEG_F;
char cc =                   SEG_D|SEG_E|      SEG_G;
char cd = SEG_B|      SEG_C|SEG_D|SEG_E|      SEG_G;
char cE = SEG_A|            SEG_D|SEG_E|SEG_F|SEG_G;
char cF = SEG_A|                  SEG_E|SEG_F|SEG_G;
char cG = SEG_A|SEG_B|SEG_C|SEG_D|      SEG_F|SEG_G;
char cH = SEG_B|SEG_C|            SEG_E|SEG_F|SEG_G;
char cI =       SEG_B|SEG_C;
char ci =             SEG_C;
char cJ =       SEG_B|SEG_C|SEG_D;
char cj =             SEG_C|SEG_D;
char cL =                   SEG_D|SEG_E|SEG_F;
char cn =             SEG_C|SEG_E|            SEG_G;
char co =             SEG_C|SEG_D|SEG_E|      SEG_G;
char cP = SEG_A|SEG_B|            SEG_E|SEG_F|SEG_G;
char cq = SEG_A|SEG_B|SEG_C|            SEG_F|SEG_G;
char cr =                         SEG_E|      SEG_G;
char cS = SEG_A|      SEG_C|SEG_D|      SEG_F|SEG_G;
char cU =       SEG_B|SEG_C|SEG_D|SEG_E|SEG_F;
char cu =             SEG_C|SEG_D|SEG_E;
char cX =       SEG_B|SEG_C|      SEG_E|SEG_F|SEG_G;
char cY =       SEG_B|SEG_C|SEG_D|      SEG_F|SEG_G;
char cZ = SEG_A|SEG_B|SEG_D|SEG_E|SEG_G;

// characters
char cTack = SEG_G;
char cDp = SEG_DP;
