#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <Arduino.h>

#define LED PB5

ISR(WDT_vect){
    // brauchen wir das?
}

int main() {
    Serial.begin(9600);
    // Serial.println("Irgendeinen den Status")

    // Pin 13 as output
    DDRB |= 1 << LED;

    // set the change enable bit
    WDTCSR |= 1 << WDCE | 1 << WDE;

    // setup the watchdog timer
    WDTCSR = 0; // TODO

    // sei();
    
    for (int i = 0;;i++) {
        PORTB ^= 1 << LED;
        Serial.print("Iterationen: ");
        Serial.println(i);
        _delay_ms(500);
    }
}