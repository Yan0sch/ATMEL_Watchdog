#include <avr/io.h>
#include <util/delay.h>
#include <Arduino.h>

#define LED PB5

int main() {
    Serial.begin(9600);
    // Pin 13 as output
    DDRB |= 1 << LED;
    PORTB |= 1 << LED;

    DDRD &= ~(1 << PD2);
    
    while(1) {
        if (!(PIND & (1 << PD2))) continue;
        // set the reset pin
        PORTB &= ~(1 << LED);
        _delay_ms(10);
        // unset reset
        PORTB |= 1 << LED;
        _delay_ms(10000);
    }
}
