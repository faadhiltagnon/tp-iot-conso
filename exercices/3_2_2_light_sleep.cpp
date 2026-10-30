#include <Arduino.h>

#define uS_TO_mS_FACTOR 1000ULL
#define LED_PIN 2               // même broche que pour le mode normal
#define T_ON    1250            // Ton = 50 x 25
#define T_OFF   750             // 2000 - Ton
const char* PREFIX = "[Binome 25 - TAGNON & KPANOU]";

void setup(){
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  esp_sleep_enable_timer_wakeup(T_OFF * uS_TO_mS_FACTOR);      // réveil après 750 ms
  Serial.printf("%s Mode LIGHT SLEEP\n", PREFIX);
}

void loop(){
  digitalWrite(LED_PIN, HIGH);
  delay(T_ON);                 // LED allumée, processeur éveillé
  digitalWrite(LED_PIN, LOW);
  Serial.flush();              // vider le buffer série avant de dormir
  esp_light_sleep_start();     // sommeil 750 ms, reprise ici au réveil
}
