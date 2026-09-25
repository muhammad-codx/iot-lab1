#include "Arduino.h"

#define RED_LED_PIN    26
#define GREEN_LED_PIN  27
#define BLUE_LED_PIN   14
#define YELLOW_LED_PIN 12
#define LIGHT_PIN      33

unsigned long lastReadMs = 0;
const unsigned long INTERVAL_MS = 500;

void allOff()
{
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(GREEN_LED_PIN, LOW);
    digitalWrite(BLUE_LED_PIN, LOW);
    digitalWrite(YELLOW_LED_PIN, LOW);
}

void setup(void)
{
    Serial.begin(115200);
    pinMode(RED_LED_PIN, OUTPUT);
    pinMode(GREEN_LED_PIN, OUTPUT);
    pinMode(BLUE_LED_PIN, OUTPUT);
    pinMode(YELLOW_LED_PIN, OUTPUT);
    pinMode(LIGHT_PIN, INPUT);
    allOff();
}

void loop(void)
{
    if (millis() - lastReadMs < INTERVAL_MS) return;
    lastReadMs = millis();

    int raw = analogRead(LIGHT_PIN);
    const char* band;
    int pin;

    if (raw <= 1023)      { band = "BLUE";   pin = BLUE_LED_PIN; }
    else if (raw <= 2047) { band = "GREEN";  pin = GREEN_LED_PIN; }
    else if (raw <= 3071) { band = "YELLOW"; pin = YELLOW_LED_PIN; }
    else                  { band = "RED";    pin = RED_LED_PIN; }

    allOff();                 // avval hammasini o'chiramiz
    digitalWrite(pin, HIGH);  // keyin faqat bittasini yoqamiz

    Serial.print("band=");
    Serial.println(band);
}