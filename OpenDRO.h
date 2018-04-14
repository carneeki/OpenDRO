#ifndef OPENDRO_H
#define OPENDRO_H
#include <avr/io.h>

void portTick();
volatile long* axisTick(byte, volatile long *);

#endif
