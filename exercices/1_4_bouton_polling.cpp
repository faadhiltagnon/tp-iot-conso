// TP IoT Conso - 1.4.2 : bouton sans interruption (pull-down externe, GPIO 27)
#include <Arduino.h>

#define PREFIX "[Binome 25 - TAGNON & KPANOU]"
#define BTN_PIN 27

int counter = 0;
bool lastState = LOW;    // LOW = relâché

void setup() {
  Serial.begin(115200);
  pinMode(BTN_PIN, INPUT);
}

void loop() {
  bool state = digitalRead(BTN_PIN);

  // appui (LOW -> HIGH) puis relâchement (HIGH -> LOW) : un cycle complet
  if (lastState == HIGH && state == LOW) {
    counter++;
    Serial.println(String(PREFIX) + " Compteur (polling) = " + String(counter));
  }
  lastState = state;
  delay(20);  // anti-rebond simplifié
}
