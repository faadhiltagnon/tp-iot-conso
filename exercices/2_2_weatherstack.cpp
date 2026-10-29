#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "secrets.h"

#define PREFIX "[Binome 25 - TAGNON & KPANOU]"

const char* VILLE = "Paris";

bool connecterWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.println(String(PREFIX) + " Connexion au Wi-Fi...");

  unsigned long debut = millis();
  while (WiFi.status() != WL_CONNECTED) {
    if (millis() - debut > 20000) {
      Serial.println(String(PREFIX) + " Echec de connexion Wi-Fi (verifier le mot de passe, reseau 2,4 GHz)");
      return false;
    }
    delay(500);
  }
  Serial.println(String(PREFIX) + " Wi-Fi connecte, adresse IP : " + WiFi.localIP().toString());
  return true;
}

void recupererMeteo() {
  // Le compte gratuit Weatherstack n'accepte que le HTTP (pas HTTPS)
  String url = String("http://api.weatherstack.com/current?access_key=") +
               WEATHERSTACK_KEY + "&query=" + VILLE;

  HTTPClient http;
  http.begin(url);
  int code = http.GET();
  if (code != 200) {
    Serial.println(String(PREFIX) + " Erreur HTTP : " + String(code));
    http.end();
    return;
  }
  String reponse = http.getString();
  http.end();

  JsonDocument doc;
  DeserializationError err = deserializeJson(doc, reponse);
  if (err) {
    Serial.println(String(PREFIX) + " Erreur JSON : " + String(err.c_str()));
    return;
  }
  if (!doc["error"].isNull()) {   // l'API renvoie un objet "error" en cas de probleme
    Serial.println(String(PREFIX) + " Erreur API : " + String(doc["error"]["info"].as<const char*>()));
    return;
  }

  const char* ville = doc["location"]["name"];
  const char* heure = doc["location"]["localtime"];
  int temperature = doc["current"]["temperature"];
  int vent = doc["current"]["wind_speed"];

  Serial.println(String(PREFIX) + " Ville : " + String(ville));
  Serial.println(String(PREFIX) + " Heure locale : " + String(heure));
  Serial.println(String(PREFIX) + " Temperature : " + String(temperature) + " C");
  Serial.println(String(PREFIX) + " Vitesse du vent : " + String(vent) + " km/h");
}

void setup() {
  Serial.begin(115200);
  delay(2000);                        // laisse le temps d'ouvrir le moniteur
  if (connecterWiFi()) recupererMeteo();
}

void loop() {
  // Un seul appel au demarrage : le compte gratuit est limite a 100 appels par mois.
  delay(1000);
}