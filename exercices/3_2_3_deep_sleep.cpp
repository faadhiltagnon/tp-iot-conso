#include <Arduino.h>

#define uS_TO_mS_FACTOR 1000ULL
#define LED_PIN 2               // même broche que les 2 autres modes
#define T_ON     1250           // Ton = 50 x 25
#define T_SLEEP 7250            // Tsleep = 1 + 0.25 x 25 = 7,25 s
const char* PREFIX = "[Binome 25 - TAGNON & KPANOU]";

void setup(){
  Serial.begin(115200);
  Serial.printf("%s Mode DEEP SLEEP - reveil\n", PREFIX);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);
  delay(T_ON);
  digitalWrite(LED_PIN, LOW);
  esp_sleep_enable_timer_wakeup(T_SLEEP * uS_TO_mS_FACTOR);
  Serial.flush();
  esp_deep_sleep_start();      // la carte redémarre entièrement au réveil
}

void loop(){}                  // jamais atteint
