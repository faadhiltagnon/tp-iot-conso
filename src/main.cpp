#include <Arduino.h>
#include <driver/adc.h>
#include <math.h>

#define PREFIX "[Binome 25 - TAGNON & KPANOU]"
#define LDR_PIN 36
#define R_FIXE 10000.0     // ohms : resistance fixe (10 kohms)
#define VCC_MV 3300.0
#define R10 15000.0        // ohms a 10 lux (datasheet GL5528 : 10 a 20 kohms)
#define GAMMA 0.6          // datasheet GL5528

void setup() {
  Serial.begin(115200);
  analogSetPinAttenuation(LDR_PIN, (adc_attenuation_t)ADC_ATTEN_DB_12);
  analogSetWidth(12);
}

void loop() {
  float vout = analogReadMilliVolts(LDR_PIN);
  if (vout < 1 || vout > VCC_MV - 1) {
    Serial.println(String(PREFIX) + " hors plage (Vout = " + String(vout, 0) + " mV)");
  } else {
    float rldr = R_FIXE * (VCC_MV - vout) / vout;
    float lux = 10.0 * pow(R10 / rldr, 1.0 / GAMMA);
    Serial.println(String(PREFIX) + " Vout = " + String(vout, 0) + " mV, R_LDR = " +
                   String(rldr / 1000.0, 1) + " kOhm, E = " + String(lux, 1) + " lux");
  }
  delay(1000);
}