#include <SPI.h>

void setup() {
    Serial.begin(9600);
    pinMode(8, OUTPUT);
    digitalWrite(8, HIGH);
    int lightIsOn = digitalRead(8);
    if(lightIsOn = true) {
        Serial.print("on");
    }else {
        Serial.print("off");
    }
    // put your setup code here, to run once:
}

void loop() {
    // put your main code here, to run repeatedly:
}
