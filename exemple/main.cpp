#include <Arduino.h>
#include <sensorACS.h>

// DEFINITION DES PINS
byte PIN_CAPTEUR_COURANT = A0;
byte PIN_CAPTEUR_REF_TENSION = A1;
byte SENSIBILITE_CAPT = 100;
byte FREQUENCE = 50;

sensorACS ACS712(SENSIBILITE_CAPT, PIN_CAPTEUR_COURANT, FREQUENCE, PIN_CAPTEUR_REF_TENSION );

void setup() {
  Serial.begin(9600);
  ACS712.SetTension(230.0);
}

void loop() {
  // fonction à placer dans le loop
  ACS712.ReadSensorADC();
  
  Serial.print("Courant Max : ");
  Serial.print(ACS712.GetCourantCrete());
  Serial.println("A");
  Serial.print("Courant Eff : ");
  Serial.print(ACS712.GetCourantEff());
  Serial.println("A");
  Serial.print("Puissance : ");
  Serial.print(ACS712.GetPuissance());
  Serial.println("W");
  Serial.println("-----------------");

  delay(2000);
}