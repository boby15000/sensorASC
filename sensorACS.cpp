#ifndef sensorACS_h
#include "sensorACS.h"
#endif

#include <simpleMinuteur.h>

const byte UNITE_VOLT = 1 ;
const byte UNITE_AMPERE = 2 ;
const int TENSION_MAX_ADC = 1024; 

simpleMinuteur minuteur(20);

/**
 * Constructeur
 * @pin_sensor : entrée analogique du capteur
 * @sensibilite : sensibilité du capteur
 * @unite_sensibilite : unité de la sensibilité Volt ou Ampère
 * @frequence : fréquence du réseau mesuré (par défaut 50hz)
 * @tension : tension du réseau mesuré (par défaut 230V)
*/
sensorACS::sensorACS(byte pin_sensor, float sensibilite, byte unite_sensibilite, float frequence = 50, float tension = 230){
   this->_PinSensor = pin_sensor;
   this->_Sensibilite = sensibilite;
   this->_UniteSensibilite = unite_sensibilite;
   this->_Echantillonnage = (1/max(frequence, 50))*1000;
   this->_Tension = tension;
   this->_TensionRef = TENSION_MAX_ADC/2;
}

/**
 * Void
 * Lecture de l'entrée analogique du capteur de courant sans circulation de courant
*/
void sensorACS::Etalonnage(){
    this->_TensionRef = this->ReadingSensor();
}


/**
 * Function
 * Return : la valeur Crete du Courant
*/
float sensorACS::GetCourantCrete(){
    int valueTension = this->ReadingSensor();
    switch (true)
    {
    case 1:
        /* Sensibilité en Volt */
        return (valueTension-(this->_TensionRef))/((this->_Sensibilite/1000)*TENSION_MAX_ADC/5);
        break;
        /* Sensibilité en Ampere */
    default:
        return (valueTension-(this->_TensionRef))*(this->_Sensibilite*TENSION_MAX_ADC/5);
        break;
    }   
}

/**
 * Function
 * Return : la valeur Efficace du Courant
*/
float sensorACS::GetCourantEff(){
    return this->GetCourantCrete()/sqrt(2);
}

/**
 * Function
 * Return : puissance consommé
*/
float sensorACS::GetPuissance(){
    return (this->GetCourantEff() * this->_Tension);
}

/**
 * Function
 * Return : la valeur numérique du Courant
*/
int sensorACS::ReadingSensor(){
    int valeur = 0;
    int valeurMax = 0;
    minuteur.demarrer(this->_Echantillonnage);
    while ( !minuteur.estTermine() ){
    valeur = analogRead( this->_PinSensor );
        if ( valeur > valeurMax ) {
            valeurMax = valeur;
        }
    }
    return valeurMax;
}