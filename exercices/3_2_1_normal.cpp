#include <Arduino.h>

#define LED_PIN     2
#define T_ON        1250   // Ton = 50 x 25
#define T_OFF       750    // 2000 - Ton
const char* PREFIX = "[Binome 25 - TAGNON & KPANOU]";

void setup(){
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  Serial.printf("%s Mode NORMAL\n", PREFIX);
}

void loop(){
  digitalWrite(LED_PIN, HIGH);
  delay(T_ON);
  digitalWrite(LED_PIN, LOW);
  delay(T_OFF);
}
