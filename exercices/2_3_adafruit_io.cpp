#include <Arduino.h>
#include <Wire.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <Adafruit_BME680.h>
#include "secrets.h"

#define PREFIX "[Binome 25 - TAGNON & KPANOU]"
#define SDA_PIN 21
#define SCL_PIN 22
#define INTERVALLE_MS 15000     // une publication toutes les 15 s (limite gratuite : 30 donnees/min)

Adafruit_BME680 bme;
WiFiClient wifiClient;
PubSubClient mqtt(wifiClient);

const String TOPIC_TEMPERATURE = String(IO_USERNAME) + "/feeds/temperature";
const String TOPIC_HUMIDITE = String(IO_USERNAME) + "/feeds/humidite";

unsigned long dernierEnvoi = 0;

bool connecterWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.println(String(PREFIX) + " Connexion au Wi-Fi...");
  unsigned long debut = millis();
  while (WiFi.status() != WL_CONNECTED) {
    if (millis() - debut > 20000) {
      Serial.println(String(PREFIX) + " Echec de connexion Wi-Fi");
      return false;
    }
    delay(500);
  }
  Serial.println(String(PREFIX) + " Wi-Fi connecte, adresse IP : " + WiFi.localIP().toString());
  return true;
}

bool connecterMQTT() {
  if (mqtt.connected()) return true;
  mqtt.setServer("io.adafruit.com", 1883);
  String id = "esp32-binome25-" + String((uint32_t)ESP.getEfuseMac(), HEX);
  for (int essai = 0; essai < 3; essai++) {
    if (mqtt.connect(id.c_str(), IO_USERNAME, IO_KEY)) {
      Serial.println(String(PREFIX) + " Connecte a Adafruit IO");
      return true;
    }
    // 4 = identifiants refuses, 5 = non autorise
    Serial.println(String(PREFIX) + " MQTT : echec, code " + String(mqtt.state()));
    delay(5000);
  }
  return false;
}

void setup() {
  Serial.begin(115200);
  delay(2000);
  Wire.begin(SDA_PIN, SCL_PIN);

  if (!bme.begin(0x77) && !bme.begin(0x76)) {
    Serial.println(String(PREFIX) + " BME680 introuvable : verifier le cablage");
    while (true) delay(1000);
  }
  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme.setGasHeater(320, 150);

  connecterWiFi();
}

void loop() {
  if (WiFi.status() != WL_CONNECTED && !connecterWiFi()) {
    delay(5000);
    return;
  }
  if (!connecterMQTT()) {
    delay(5000);
    return;
  }
  mqtt.loop();                    // garde la connexion active

  if (millis() - dernierEnvoi >= INTERVALLE_MS) {
    dernierEnvoi = millis();
    if (!bme.performReading()) {
      Serial.println(String(PREFIX) + " Erreur de lecture du BME680");
      return;
    }
    float temp = bme.temperature;
    float hum = bme.humidity;

    bool okT = mqtt.publish(TOPIC_TEMPERATURE.c_str(), String(temp, 1).c_str());
    bool okH = mqtt.publish(TOPIC_HUMIDITE.c_str(), String(hum, 1).c_str());

    Serial.println(String(PREFIX) + " Publie : T = " + String(temp, 1) + " C (" +
                   (okT ? "OK" : "echec") + "), humidite = " + String(hum, 1) + " % (" +
                   (okH ? "OK" : "echec") + ")");
  }
}