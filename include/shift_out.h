#ifndef SHIFT_OUT_H
#define SHIFT_OUT_H

#include <stdint.h>

// Initialize GPIO pins for 74HC595 as outputs
void shift_init(void);

// Send 8-bit data to 74HC595 and latch it
void shift_out_byte(uint8_t data);

#endif // SHIFT_OUT_H