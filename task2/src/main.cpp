#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <util/delay.h>
#include <Arduino.h>

#define LED PB5

void setup(){
    Serial.begin(9600);
    // Serial.println("Irgendeinen den Status")

    // Pin 13 as output
    DDRB |= 1 << LED;

    // activate external reset
    DDRD |= 1 << PD2;
    PORTD |= 1 << PD2;

    wdt_enable(WDTO_2S);
}

void loop(){
    for (int i = 0;;i++) {
        PORTB ^= 1 << LED;
        Serial.print("Iterationen: ");
        Serial.println(i);
        _delay_ms(500);
    }
}
