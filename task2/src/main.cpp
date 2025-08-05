#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <util/delay.h>
#include <Arduino.h>

#define LED PB5

ISR(WDT_vect){
    // brauchen wir das?
}

uint8_t reset_flags __attribute__((section(".noinit")));
__attribute__((naked)) __attribute__((section(".init3")))
void save_mcusr(void) {
    reset_flags = MCUSR;
    MCUSR = 0;
    wdt_disable();
}

int main() {
    Serial.begin(9600);
    // Serial.println("Irgendeinen den Status")

    // Pin 13 as output
    DDRB |= 1 << LED;

    // activate external reset
    DDRD |= 1 << PD2;
    PORTD |= 1 << PD2;

    // set the change enable bit
    //WDTCSR |= 1 << WDCE | 1 << WDE;

    // setup the watchdog timer
    //WDTCSR = 0; // TODO

    sei();
    
    for (int i = 0;;i++) {
        PORTB ^= 1 << LED;
        Serial.print("Iterationen: ");
        Serial.print(i);
        Serial.print(" ");
        if (reset_flags & (1 << WDRF)) Serial.println("WatchDog Reset");
        if (reset_flags & (1 << EXTRF)) Serial.println("external Reset");
        if (reset_flags & (1 << PORF)) Serial.println("Power-on Reset");
        Serial.println(reset_flags);
        _delay_ms(500);
    }
}
