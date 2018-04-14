#ifndef CONFIG_H
#define CONFIG_H
#include <avr/io.h>

#if defined(__AVR_ATmega328P__)
#include "config_328.h"
#elif defined(__AVR_ATmega2560__)
#include "config_2560.h"
#endif

#define DISPLAY_COUNT 8  // how many display boards?
#define DISPLAY_INTENSITY 1

#define IDX_Z_DELTA 10000 // number of pulses between index pulses
#define TICK_Z_MM 0.005   // distance between pulses
#define IDX_X_DELTA 10000 // number of pulses between index pulses
#define TICK_Z_MM 0.005   // distance between pulses
#define IDX_W_DELTA 10000 // number of pulses between index pulses
#define TICK_Z_MM 0.005   // distance between pulses
#define IDX_C_DELTA 360   // number of pulses between index pulses
#define TICK_Z_DEG 0.005  // angular distance (on spindle) between pulses

#endif
