#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define PREFIX "[Binome 25 - TAGNON & KPANOU]"
#define SDA_PIN 21
#define SCL_PIN 22

LiquidCrystal_I2C* lcd;

const String TITRE = "Great IoT Tutorial!";   // 19 caracteres > 16 colonnes : defilement
String texte;                                 // titre + espaces, lu en boucle
int offset = 0;
unsigned long dernierDefilement = 0;
unsigned long dernierSecond = 0;
unsigned long secondes = 0;

// Les adaptateurs I2C courants ont l'adresse 0x27 ou 0x3F
uint8_t trouverAdresse() {
  const uint8_t candidates[] = {0x27, 0x3F};
  for (uint8_t a : candidates) {
    Wire.beginTransmission(a);
    if (Wire.endTransmission() == 0) return a;
  }
  return 0;
}

void afficherLigne1() {
  String fenetre = "";
  for (int i = 0; i < 16; i++) fenetre += texte[(offset + i) % texte.length()];
  lcd->setCursor(0, 0);
  lcd->print(fenetre);
}

void afficherLigne2() {
  String s = "Launched for " + String(secondes) + "s";
  if (s.length() > 16) s = "Launched " + String(secondes) + "s";   // au-dela de 99 s
  while (s.length() < 16) s += ' ';
  lcd->setCursor(0, 1);
  lcd->print(s);
  Serial.println(String(PREFIX) + " LCD ligne 2 : " + s);
}

void setup() {
  Serial.begin(115200);
  Wire.begin(SDA_PIN, SCL_PIN);

  uint8_t addr = trouverAdresse();
  if (addr == 0) {
    Serial.println(String(PREFIX) + " LCD introuvable : verifier le cablage");
    while (true) delay(1000);
  }
  Serial.println(String(PREFIX) + " LCD trouve a l'adresse 0x" + String(addr, HEX));

  lcd = new LiquidCrystal_I2C(addr, 16, 2);
  lcd->init();
  lcd->backlight();

  texte = TITRE + "    ";
  afficherLigne1();
  afficherLigne2();
}

void loop() {
  unsigned long now = millis();
  if (now - dernierDefilement >= 350) {      // la ligne 1 defile
    dernierDefilement = now;
    offset = (offset + 1) % texte.length();
    afficherLigne1();
  }
  if (now - dernierSecond >= 1000) {         // la ligne 2 compte les secondes
    dernierSecond = now;
    secondes++;
    afficherLigne2();
  }
}