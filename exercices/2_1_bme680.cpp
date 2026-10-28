#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME680.h>

#define PREFIX "[Binome 25 - TAGNON & KPANOU]"
#define SDA_PIN 21
#define SCL_PIN 22

Adafruit_BME680 bme(&Wire);

void setup() {
  Serial.begin(115200);
  Wire.begin(SDA_PIN, SCL_PIN);

  // Adresse I2C par defaut : 0x77. Certains modules utilisent 0x76.
  if (!bme.begin(0x77) && !bme.begin(0x76)) {
    Serial.println(String(PREFIX) + " BME680 introuvable : verifier le cablage");
    while (true) delay(1000);
  }

  // Lignes de configuration (a savoir expliquer) :
  bme.setTemperatureOversampling(BME680_OS_8X);  // 8 mesures moyennees : moins de bruit
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);    // filtre qui lisse les mesures successives
  bme.setGasHeater(320, 150);                    // plaque chauffante : 320 degres C pendant 150 ms
}

void loop() {
  if (!bme.performReading()) {
    Serial.println(String(PREFIX) + " echec de la lecture");
    delay(2000);
    return;
  }
  float tempC = bme.temperature;
  float tempF = tempC * 9.0 / 5.0 + 32.0;
  Serial.println(String(PREFIX) + " T = " + String(tempC, 1) + " C / " +
                 String(tempF, 1) + " F, humidite = " + String(bme.humidity, 1) + " %");
  delay(2000);
}