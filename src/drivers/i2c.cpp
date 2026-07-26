#include "i2c.h"
#include <avr/io.h>

void i2c_init() {
    TWBR = 72;

    TWSR &= ~(1 << TWPS0) | (1 << TWPS1);
    TWCR |= (1 << TWEN);

}

void i2c_start() {
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);

    while (!(TWCR & (1 << TWINT)));    
}

void i2c_stop() {
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);

    while (TWCR & (1 << TWSTO));    
}

void i2c_write(uint8_t data) {
    TWDR = data;

    TWCR = (1 << TWINT) | (1 << TWEN); 
    while (!(TWCR & (1 << TWINT)));    

}