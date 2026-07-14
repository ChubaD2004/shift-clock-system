#include "shift_out.h"
#include <avr/io.h>

void shift_init(void) {
    // Set PB0, PB1, PB2 as outputs
    DDRB |= (1 << PB0) | (1 << PB1) | (1 << PB2); 

    // Set PB0, PB1, PB2 to LOW
    PORTB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2)); 
}

void shift_out_byte(uint8_t data) {
    // Loop 8 times to transmit all 8 bits
    for (uint8_t i = 0; i < 8; i++) {
        // Step 1: Set the DS (Data) pin state
        if (data & 0x80)
        {
            PORTB |= (1 << PB0);    // Set DS to HIGH
        } else 
            PORTB &= ~(1 << PB0);   // Set DS to LOW

        // Step 2: Pulse SHCP (Clock) to shift the bit into the register
        PORTB |= (1 << PB1);    // SHCP HIGH
        PORTB &= ~(1 << PB1);   // SHCP LOW

        // Step 3: Shift data left to prepare the next bit
        data <<= 1;
    }

    // Step 4: After shifting all 8 bits, pulse STCP (Latch) to output the data
    PORTB |= (1 << PB2);    // STCP HIGH
    PORTB &= ~(1 << PB2);   // STCP LOW

}
