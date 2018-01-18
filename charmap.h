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

// numbers
char c0 = SEG_A|SEG_B|SEG_C|SEG_D|SEG_E|SEG_F;
char c1 = SEG_B|SEG_C;
char c2 = SEG_A|SEG_B|SEG_G|SEG_E|SEG_D;
char c3 = SEG_A|SEG_B|SEG_G|SEG_C|SEG_D;
char c4 = SEG_F|SEG_G|SEG_B|SEG_C;
char c5 = SEG_A|SEG_F|SEG_G|SEG_C|SEG_D;
char c6 = SEG_A|SEG_F|SEG_E|SEG_G|SEG_C|SEG_D;
char c7 = SEG_A|SEG_B|SEG_C;
char c8 = SEG_A|SEG_B|SEG_C|SEG_D|SEG_E|SEG_F|SEG_G;
char c9 = SEG_A|SEG_F|SEG_G|SEG_B|SEG_C|SEG_D;

// letters
char cA = SEG_E|SEG_F|SEG_A|SEG_B|SEG_C|SEG_G;
char cb = SEG_G|SEG_E|SEG_D|SEG_C|SEG_B;
char cC = SEG_A|SEG_F|SEG_E|SEG_D;
char cc = SEG_G|SEG_E|SEG_D;
char cd = SEG_G|SEG_E|SEG_D|SEG_C|SEG_B;
char cE = SEG_A|SEG_F|SEG_G|SEG_E|SEG_D;
char cF = SEG_A|SEG_F|SEG_G|SEG_E;
char cG = SEG_A|SEG_F|SEG_G|SEG_B|SEG_C|SEG_D;
char cH = SEG_F|SEG_E|SEG_G|SEG_B|SEG_C;
char cI = SEG_F|SEG_E;
char ci = SEG_E;
char cJ = SEG_B|SEG_C|SEG_D;
char cj = SEG_C|SEG_D;
char cL = SEG_F|SEG_E|SEG_D;
char cn = SEG_E|SEG_G|SEG_C;
char co = SEG_G|SEG_E|SEG_D|SEG_C;
char cP = SEG_F|SEG_E|SEG_A|SEG_B|SEG_G;
char cq = SEG_A|SEG_F|SEG_G|SEG_B|SEG_C;
char cr = SEG_E|SEG_G;
char cS = SEG_A|SEG_F|SEG_G|SEG_C|SEG_D;
char cU = SEG_F|SEG_E|SEG_D|SEG_C|SEG_B;
char cu = SEG_E|SEG_D|SEG_C;
char cX = SEG_F|SEG_E|SEG_G|SEG_B|SEG_C;
char cY = SEG_F|SEG_G|SEG_B|SEG_C|SEG_D;
char cZ = SEG_A|SEG_B|SEG_G|SEG_E|SEG_D;

// characters
char cTack = SEG_G;
char cDp = SEG_DP;
