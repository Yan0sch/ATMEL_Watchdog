#include <avr/io.h>
#include <util/delay.h>
#include <Arduino.h>
#include <Wire.h>

#define LED PB5

void response();

void setup(){
    Wire.begin(0x08); // I2C als Slave mit Adresse 0x08
    Wire.onRequest(response); // Callback-Funktion bei Datenempfang
    randomSeed(analogRead(0));

    Serial.begin(9600);
    // Pin 13 as output
    DDRB |= 1 << LED;
    PORTB |= 1 << LED;

    DDRD &= ~(1 << PD2);
}

void loop(){
    if ((PIND & (1 << PD2))){
        Serial.println("Send reset.");
        // set the reset pin
        PORTB &= ~(1 << LED);
        _delay_ms(10);
        // unset reset
        PORTB |= 1 << LED;
        _delay_ms(10000);
    }
}

void response() {
    if(random(0, 100) > 70){
        Serial.println("Simulated error!");
        return;
    }
    int randint = random(1, 100); // Zufallswert zwischen 0 und 99
    Wire.write(randint);      // Ein Byte senden
    Serial.print("Gesendet: ");
    Serial.println(randint);
}