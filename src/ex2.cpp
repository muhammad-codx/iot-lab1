#include "Arduino.h"

#define GREEN_LED_PIN 27
#define BUTTON_PIN    25

bool greenState = false;       // LED hozir yoniqmi
int  lastButton = LOW;         // tugmaning oldingi holati
unsigned long lastChangeMs = 0;
const unsigned long DEBOUNCE_MS = 50;

void setup(void)
{
    Serial.begin(115200);
    pinMode(GREEN_LED_PIN, OUTPUT);
    pinMode(BUTTON_PIN, INPUT_PULLDOWN); // active high: bosilganda HIGH
    digitalWrite(GREEN_LED_PIN, LOW);
}

void loop(void)
{
    int current = digitalRead(BUTTON_PIN);

    // Faqat LOW -> HIGH o'tishida (bosilgan payt) va debounce vaqtidan keyin
    if (current == HIGH && lastButton == LOW && millis() - lastChangeMs > DEBOUNCE_MS) {
        greenState = !greenState;                        // holatni almashtirish
        digitalWrite(GREEN_LED_PIN, greenState ? HIGH : LOW);
        Serial.print("GREEN=");
        Serial.println(greenState ? 1 : 0);
        lastChangeMs = millis();
    }

    lastButton = current;
}