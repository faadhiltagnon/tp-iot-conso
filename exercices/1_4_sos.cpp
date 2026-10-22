// TP IoT Conso - 1.4.2 : SOS en morse (u = 200 ms)
#include <Arduino.h>

#define PREFIX "[Binome 25 - TAGNON & KPANOU]"
#define LED_PIN 2
#define U 200

void dot()  { digitalWrite(LED_PIN, HIGH); delay(1 * U); digitalWrite(LED_PIN, LOW); }
void dash() { digitalWrite(LED_PIN, HIGH); delay(3 * U); digitalWrite(LED_PIN, LOW); }

void letterS() {
  for (int i = 0; i < 3; i++) {
    dot();
    if (i < 2) delay(1 * U);
  }
}

void letterO() {
  for (int i = 0; i < 3; i++) {
    dash();
    if (i < 2) delay(1 * U);
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  Serial.println(String(PREFIX) + " SOS");
  letterS();
  delay(3 * U);   // pause entre lettres
  letterO();
  delay(3 * U);   // pause entre lettres
  letterS();
  delay(7 * U);   // pause entre mots
}
