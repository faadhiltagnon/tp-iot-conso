#include <Arduino.h>
#include <driver/adc.h>

#define PREFIX "[Binome 25 - TAGNON & KPANOU]"
#define LM35_PIN 36   // ADC1_CH0

void setup() {
  Serial.begin(115200);
  // 0 dB : plage la plus fine (environ 100 a 950 mV), adaptee a 10 mV/degre
  analogSetPinAttenuation(LM35_PIN, ADC_0db);
  analogSetWidth(12);
}

void loop() {
  long sum = 0;
  for (int i = 0; i < 16; i++) {      // moyenne de 16 mesures contre le bruit
    sum += analogReadMilliVolts(LM35_PIN);
    delay(5);
  }
  float millivolts = sum / 16.0;
  float temperature = millivolts / 10.0;   // 10 mV par degre C

  Serial.println(String(PREFIX) + " LM35 = " + String(millivolts, 1) +
                 " mV -> " + String(temperature, 1) + " C");
  delay(1000);
}