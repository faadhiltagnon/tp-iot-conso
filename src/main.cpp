#include <Arduino.h>
#include <driver/adc.h>

#define PREFIX "[Binome 25 - TAGNON & KPANOU]"
#define LDR_PIN 36   // GPIO 36 = ADC1_CH0 (broche VP)

void setup() {
  Serial.begin(115200);
  // Atténuation 12 dB : plage mesurable 150 mV à 3100 mV
  analogSetPinAttenuation(LDR_PIN, (adc_attenuation_t)ADC_ATTEN_DB_12);
  analogSetWidth(12);   // résolution 12 bits : 0 à 4095
}

void loop() {
  int value = analogRead(LDR_PIN);                 // 0 à 4095
  int millivolts = analogReadMilliVolts(LDR_PIN);  // tension lue en mV
  Serial.println(String(PREFIX) + " LDR = " + String(value)
                 + " (0-4095), " + String(millivolts) + " mV");
  delay(1000);   // une lecture par seconde
}