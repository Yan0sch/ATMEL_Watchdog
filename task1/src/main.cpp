#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <Arduino.h>

#define LED PB5
ISR(WDT_vect){
    // TODO
}
int main() {
    Serial.begin(9600);
    // Pin 13 as output
    DDRB |= 1 << LED;
    
    // Deactivate external reset
    DDRD |= 1 << PD2;
    PORTD |= 0 << PD2;

    // set the change enable bit
    WDTCSR |= 1 << WDCE | 1 << WDE;

    // setup the watchdog timer
    WDTCSR = 0; // TODO

    sei();
    
    while(1);
}