#include <Arduino.h>
#include <driver/adc.h>

#define PREFIX "[Binome 25 - TAGNON & KPANOU]"
#define POT_PIN 36   // ADC1_CH0, meme broche que la LDR

void setup() {
  Serial.begin(115200);
  analogSetPinAttenuation(POT_PIN, (adc_attenuation_t)ADC_ATTEN_DB_12);
  analogSetWidth(12);
}

void loop() {
  int raw = analogRead(POT_PIN);
  int calibrated = map(raw, 0, 4095, 0, 255);
  Serial.println(String(PREFIX) + " POT brut = " + String(raw) +
                 " (0-4095) -> calibre = " + String(calibrated) + " (0-255)");
  delay(500);
}
