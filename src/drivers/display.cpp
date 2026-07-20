#include "display.h"
#include <avr/io.h>

static const uint8_t segment_lut[10] = {
    0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90
};


void display_init(void) {
    // Set PD2, PD3, PD4 as outputs
    DDRD |= (1 << PD2) | (1 << PD3) | (1 << PD4); 

    // Set PD2, PD3, PD4 to LOW
    PORTD &= ~((1 << PD2) | (1 << PD3) | (1 << PD4)); 
}

void timer1_init(void) {
    // 1. Reset Control Register A to default (not strictly needed, but good practice)
    TCCR1A = 0; 

    // 2. Set CTC mode (WGM12) and Prescaler /64 (CS11 and CS10)
    TCCR1B |= (1 << WGM12) | (1 << CS11) | (1 << CS10);

    // 3. Set Compare Match value for 400Hz
    OCR1A = 624;  
    
    // 4. Enable Timer1 Compare Match A Interrupt
    TIMSK1 |= (1 << OCIE1A);  
}

void format_time(uint32_t seconds) {
    uint32_t hours = seconds/3600;
    uint32_t minutes = (seconds % 3600) / 60;

    display_buffer[0] = segment_lut[hours/10];
    display_buffer[1] = segment_lut[hours % 10] & 0x7F;
    display_buffer[2] = segment_lut[minutes/10];
}