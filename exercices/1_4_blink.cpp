// TP IoT Conso - 1.4.2 : blink LED intégrée (Ton = 50 x N = 1250 ms, période 2000 ms)
#include <Arduino.h>

#define PREFIX "[Binome 25 - TAGNON & KPANOU]"
#define LED_PIN 2        // LED intégrée de la carte
#define T_ON 1250        // 50 x 25
#define PERIOD 2000

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_PIN, HIGH);
  Serial.println(String(PREFIX) + " LED ON");
  delay(T_ON);
  digitalWrite(LED_PIN, LOW);
  Serial.println(String(PREFIX) + " LED OFF");
  delay(PERIOD - T_ON);  // 750 ms
}
