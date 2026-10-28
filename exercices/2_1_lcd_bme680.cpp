#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_BME680.h>

#define PREFIX "[Binome 25 - TAGNON & KPANOU]"
#define SDA_PIN 21
#define SCL_PIN 22

LiquidCrystal_I2C* lcd;
Adafruit_BME680 bme;

// Les adaptateurs I2C courants ont l'adresse 0x27 ou 0x3F
uint8_t trouverAdresse() {
  const uint8_t candidates[] = {0x27, 0x3F};
  for (uint8_t a : candidates) {
    Wire.beginTransmission(a);
    if (Wire.endTransmission() == 0) return a;
  }
  return 0;
}

String completer(String s) {          // complete a 16 caracteres
  while (s.length() < 16) s += ' ';
  return s;
}

void setup() {
  Serial.begin(115200);
  Wire.begin(SDA_PIN, SCL_PIN);

  uint8_t addr = trouverAdresse();
  if (addr == 0) {
    Serial.println(String(PREFIX) + " LCD introuvable : verifier le cablage");
    while (true) delay(1000);
  }
  lcd = new LiquidCrystal_I2C(addr, 16, 2);
  lcd->init();
  lcd->backlight();

  if (!bme.begin(0x77) && !bme.begin(0x76)) {
    Serial.println(String(PREFIX) + " BME680 introuvable : verifier le cablage");
    lcd->setCursor(0, 0);
    lcd->print("BME680 absent   ");
    while (true) delay(1000);
  }

  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme.setGasHeater(320, 150);
}

void loop() {
  if (!bme.performReading()) {
    Serial.println(String(PREFIX) + " Erreur de lecture du BME680");
    delay(2000);
    return;
  }
  float temp = bme.temperature;
  float hum = bme.humidity;

  // Ligne 1 : "Temp: 24.5 °C"
  lcd->setCursor(0, 0);
  lcd->print(completer("Temp: " + String(temp, 1) + " "));
  lcd->setCursor(13, 0);
  lcd->write((uint8_t)223);          // symbole degre de l'afficheur
  lcd->print("C");

  // Ligne 2 : "Hum : 45.2 %"
  lcd->setCursor(0, 1);
  lcd->print(completer("Hum : " + String(hum, 1) + " %"));

  Serial.println(String(PREFIX) + " T = " + String(temp, 1) +
                 " C, humidite = " + String(hum, 1) + " %");
  delay(2000);
}