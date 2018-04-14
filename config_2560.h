// TODO: rewrite me for 2560

// axis A/B pairs
#define PIN_Z_A PD0      // D0
#define PIN_Z_B PD1      // D1
#define PIN_X_A PD2      // D2
#define PIN_X_B PD3      // D3
#define PIN_W_A PD4      // D4
#define PIN_W_B PD5      // D5

// axis index pin + reset button
#define PIN_Z_Z     PC0  // A0
#define PIN_Z_RESET PC1  // A1
#define PIN_X_Z     PC2  // A2
#define PIN_X_RESET PC3  // A3
#define PIN_W_Z     PC4  // A4
#define PIN_W_RESET PC5  // A5

// MAX7219 output pins
#define PIN_LED_CLK  PB5 // D13
#define PIN_LED_DATA PB4 // D12
#define PIN_LED_CS   PB3 // D11
#define DISPLAY_COUNT 4  // how many display boards?

// units button
#define PIN_UNITS    PB0 // D8

// multiplexed 8x8 keypad
#define KEY_COL_A PA0 // colums PA0..7
#define KEY_COL_B PA1
#define KEY_COL_C PA2
#define KEY_COL_D PA3
#define KEY_COL_E PA4
#define KEY_COL_F PA5
#define KEY_COL_G PA6
#define KEY_COL_H PA7
#define KEY_ROW_0 PC0 // rows   PC0..7
#define KEY_ROW_1 PC1
#define KEY_ROW_2 PC2
#define KEY_ROW_3 PC3
#define KEY_ROW_4 PC4
#define KEY_ROW_5 PC5
#define KEY_ROW_6 PC6
#define KEY_ROW_7 PC7
