#include "Arduino.h"

#define YELLOW_LED_PIN 12
#define BUTTON_PIN     25
#define LIGHT_PIN      33

int  lastButton = LOW;
unsigned long lastPressMs = 0;
const unsigned long DEBOUNCE_MS = 50;
const unsigned long FLASH_MS = 100;

void setup(void)
{
    Serial.begin(115200);
    pinMode(YELLOW_LED_PIN, OUTPUT);
    pinMode(BUTTON_PIN, INPUT_PULLDOWN);
    pinMode(LIGHT_PIN, INPUT);
    digitalWrite(YELLOW_LED_PIN, LOW);
}

void loop(void)
{
    int current = digitalRead(BUTTON_PIN);

    // Faqat bosilgan payt (LOW -> HIGH)
    if (current == HIGH && lastButton == LOW && millis() - lastPressMs > DEBOUNCE_MS) {
        lastPressMs = millis();

        int raw = analogRead(LIGHT_PIN);
        Serial.print("snapshot=");
        Serial.println(raw);

        // Tasdiqlash uchun sariq LED'ni qisqa yoqib-o'chirish
        digitalWrite(YELLOW_LED_PIN, HIGH);
        delay(FLASH_MS);
        digitalWrite(YELLOW_LED_PIN, LOW);
    }

    lastButton = current;
}