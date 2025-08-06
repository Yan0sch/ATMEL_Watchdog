#include <Arduino.h>
#include <avr/sleep.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>

volatile bool watchdog_triggered = false;

ISR(WDT_vect) {
  watchdog_triggered = true; // check that the WDT was triggered
}

void setup() {
    Serial.begin(9600);
    delay(200);

    // deactivate external reset
    DDRD |= 1 << PD2;
    PORTD |= 0 << PD2;

    WDTCSR |= (1 << WDCE) | (1 << WDE); // Watchdog-Konfiguration freischalten
    WDTCSR = (1 << WDIE) | (1 << WDP3) | (1 << WDP0); // 8s Interrupt-Modus

    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
}

void loop() {
    if (watchdog_triggered) {
        watchdog_triggered = false;
        Serial.println("WatchDog Triggered! Send very important data ...");
        _delay_ms(100);
    }
    
    // go to sleep
    noInterrupts();
    sleep_bod_disable();
    interrupts();
    sleep_cpu();      

    // Program starts here after wake up
}

