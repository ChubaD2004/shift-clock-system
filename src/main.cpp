#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "display.h"
#include "shift_out.h"

volatile uint32_t system_seconds = 57240; 

int main(void) {
    // Init Peripherals
    shift_init();
    display_init();
    timer1_init();

    sei();                                  // Enable global interrupts

    while (1) {
        // Main cycle
    }
    return 0;
}

ISR(TIMER1_COMPA_vect) {
    static uint8_t active_digit = 0;
    static uint16_t tick_counter = 0;
    
    // Set PD2, PD3, PD4 to LOW
    PORTD &= ~((1 << PD2) | (1 << PD3) | (1 << PD4)); 

    shift_out_byte(display_buffer[active_digit]);

    if (active_digit == 0)
    {
        PORTD |= (1 << PD2);
        active_digit++;
    } else if (active_digit == 1) {
        PORTD |= (1 << PD3);
        active_digit++;
    } else if (active_digit == 2){
        PORTD |= (1 << PD4);
        active_digit = 0;
    }

    tick_counter++;

    if (tick_counter >= 400)
    {
        tick_counter = 0;
        system_seconds++;

        if (system_seconds >= 86400) {
            system_seconds = 0;
        }
                    
        format_time(system_seconds);       
    }
    

}

