// TP IoT Conso - diagnostic : état brut de GPIO 27 (utilisé pour étudier l'instabilité du bouton)
#include <Arduino.h>

#define PREFIX "[Binome 25 - TAGNON & KPANOU]"
#define BTN_PIN 27

int last = -1;

void setup() {
  Serial.begin(115200);
  pinMode(BTN_PIN, INPUT);
}

void loop() {
  int s = digitalRead(BTN_PIN);
  if (s != last) {                 // on n'affiche que les changements
    Serial.println(String(PREFIX) + " GPIO27 = " + String(s));
    last = s;
  }
}
