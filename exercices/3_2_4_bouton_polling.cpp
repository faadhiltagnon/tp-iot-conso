#include <Arduino.h>

#define BTN_PIN 27   // bouton, pull-down externe : appuyé = HIGH
#define LED_PIN 2    // LED intégrée
const char* PREFIX = "[Binome 25 - TAGNON & KPANOU]";

void setup(){
  Serial.begin(115200);
  pinMode(BTN_PIN, INPUT);      // INPUT simple : la résistance de pull-down est externe
  pinMode(LED_PIN, OUTPUT);
  Serial.printf("%s Test reponse bouton -> LED (sans sommeil)\n", PREFIX);
}

void loop(){
  digitalWrite(LED_PIN, digitalRead(BTN_PIN));   // la LED recopie le bouton en permanence
}
