// TP IoT Conso - 1.3.2 : communication série
#include <Arduino.h>

#define PREFIX "[Binome 25 - TAGNON & KPANOU]"

void setup() {
  Serial.begin(115200);
}

void loop() {
  Serial.println(String(PREFIX) + " Hello Arduino World!");
  delay(2000);
}
