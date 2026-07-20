#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>

void display_init(void);

void timer1_init(void);

void format_time(uint32_t seconds);



volatile uint8_t display_buffer[3];

#endif // DISPLAY_H