// TP IoT Conso - 1.4.2 : bouton avec interruption (pull-down externe, GPIO 27)
#include <Arduino.h>

#define PREFIX "[Binome 25 - TAGNON & KPANOU]"
#define BTN_PIN 27

volatile int counter = 0;
volatile unsigned long lastIrq = 0;
int lastPrinted = 0;

void IRAM_ATTR onRelease() {
  unsigned long now = millis();
  if (now - lastIrq > 50) {   // anti-rebond 50 ms
    counter++;
    lastIrq = now;
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(BTN_PIN, INPUT);
  // FALLING = relâchement (HIGH -> LOW)
  attachInterrupt(digitalPinToInterrupt(BTN_PIN), onRelease, FALLING);
}

void loop() {
  if (counter != lastPrinted) {
    lastPrinted = counter;
    Serial.println(String(PREFIX) + " Compteur (interruption) = " + String(lastPrinted));
  }
}
