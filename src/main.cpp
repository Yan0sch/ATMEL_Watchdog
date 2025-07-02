#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <Arduino.h>

#define LED PB5

ISR(WDT_vect){
    PORTB ^= 1 << LED;
}

int main() {
    Serial.begin(9600);
    // Pin 13 as o
    DDRB |= 1 << LED;

    // set the change enable b
    WDTCSR |= 1 << WDCE | 1 << WDE;

    // setup the watchdog timer
    WDTCSR = 1 << WDIE | 1 << WDP2 | 1 << WDP0;

    sei();
    
    while(1);
}
