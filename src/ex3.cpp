#include "Arduino.h"

#define LIGHT_PIN 33

unsigned long lastReadMs = 0;
const unsigned long INTERVAL_MS = 500;

void setup(void)
{
    Serial.begin(115200);
    pinMode(LIGHT_PIN, INPUT);
}

void loop(void)
{
    if (millis() - lastReadMs >= INTERVAL_MS) {
        lastReadMs = millis();

        int raw = analogRead(LIGHT_PIN);
        Serial.print("raw=");
        Serial.println(raw);
    }
}