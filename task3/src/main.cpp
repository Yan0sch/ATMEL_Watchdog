#include <Wire.h>
#include <Arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/wdt.h>

uint8_t requestData();

void setup() {
    Wire.begin(); // Startet I2C als Master
    Serial.begin(9600);

    // Deactivate external reset
    DDRD |= 1 << PD2;
    PORTD |= 0 << PD2;

    wdt_enable(WDTO_2S);
}

void loop() {
    Serial.print("Random Sensor Value ");
    int data = requestData();
    Serial.println(data);
    wdt_reset();

    delay(1000); // 1 Sekunde warten
}

uint8_t requestData(){
    // 2. Antwort vom Slave anfordern
    Wire.requestFrom(0x08, 1); // 1 Byte anfordern
    
    uint8_t response = 0;
    if(Wire.available()){
        response = Wire.read();
    } 

    while(!response);

    return response;
}