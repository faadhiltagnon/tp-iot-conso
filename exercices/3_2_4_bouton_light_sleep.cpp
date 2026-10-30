// Version light sleep avec réveil par GPIO : écrite mais NON MESURÉE (oscilloscope repris).
#include <Arduino.h>
#include "driver/gpio.h"
#include "esp_sleep.h"

#define BTN_PIN 27
#define LED_PIN 2
const char* PREFIX = "[Binome 25 - TAGNON & KPANOU]";

void setup(){
  Serial.begin(115200);
  pinMode(BTN_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  // Réveil quand GPIO 27 passe à l'état HAUT (bouton appuyé)
  gpio_wakeup_enable((gpio_num_t)BTN_PIN, GPIO_INTR_HIGH_LEVEL);
  esp_sleep_enable_gpio_wakeup();
  Serial.printf("%s Test reponse bouton -> LED (light sleep + reveil GPIO)\n", PREFIX);
}

void loop(){
  if (digitalRead(BTN_PIN) == HIGH) {
    digitalWrite(LED_PIN, HIGH);      // bouton appuyé : LED allumée
  } else {
    digitalWrite(LED_PIN, LOW);       // bouton relâché : LED éteinte...
    Serial.flush();
    esp_light_sleep_start();          // ... et on dort jusqu'au prochain appui
  }
}
