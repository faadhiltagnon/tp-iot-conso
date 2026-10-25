#include <Arduino.h>
#include <driver/adc.h>

#define PREFIX "[Binome 25 - TAGNON & KPANOU]"
#define LDR_PIN 36

int sensorMin = 4095;
int sensorMax = 0;

void calibrate(const char* consigne) {
  Serial.println(String(PREFIX) + " >>> " + consigne + " (5 s)");
  delay(2000);                       // AJOUT : temps de te placer avant la mesure
  unsigned long start = millis();
  while (millis() - start < 5000) {
    int v = analogRead(LDR_PIN);
    if (v < sensorMin) sensorMin = v;
    if (v > sensorMax) sensorMax = v;
    delay(10);
  }
}

void setup() {
  Serial.begin(115200);
  analogSetPinAttenuation(LDR_PIN, (adc_attenuation_t)ADC_ATTEN_DB_12);
  analogSetWidth(12);
  delay(3000);  // temps d'ouvrir le moniteur

  calibrate("ECLAIREZ la LDR avec le flash");
  calibrate("CACHEZ la LDR avec la main");

  Serial.println(String(PREFIX) + " Calibration : min = " + String(sensorMin) +
                 ", max = " + String(sensorMax));
}

void loop() {
  int raw = analogRead(LDR_PIN);
  int calibrated = 0;
  if (sensorMax > sensorMin) {
    calibrated = map(raw, sensorMin, sensorMax, 0, 255);
    calibrated = constrain(calibrated, 0, 255);
  }
  Serial.println(String(PREFIX) + " brut = " + String(raw) +
                 " -> calibre = " + String(calibrated) + " (0-255)");
  delay(1000);
}