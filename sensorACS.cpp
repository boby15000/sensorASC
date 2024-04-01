#ifndef sensorACS_h
#include "sensorACS.h"
#endif

#include <simpleMinuteur.h>

simpleMinuteur minuteur(50);

/**
 * Constructeur
 * @sensibilite : sensibilité du capteur en mV
 * @pin_sensor : entrée analogique du capteur
*/
sensorACS::sensorACS(float sensibilite, byte pin_sensor){
   this->_Sensibilite = sensibilite;
   this->_PinSensor = pin_sensor;
}

/**
 * Constructeur
 * @sensibilite : sensibilité du capteur en mV
 * @pin_sensor : entrée analogique du capteur
 * @pin_sensor_ref_U : entrée analogique pour refence de tension
*/
sensorACS::sensorACS(float sensibilite, byte pin_sensor, byte pin_sensor_ref_U){
    this->_Sensibilite = sensibilite;
    this->_PinSensor = pin_sensor;
    this->_PinSensor_refU = pin_sensor_ref_U;
}

/**
 * Constructeur
 * @sensibilite : sensibilité du capteur en mV
 * @pin_sensor : entrée analogique du capteur
 * @frequence : valeur de la fréquence pour tension alternative
*/
sensorACS::sensorACS(float sensibilite, byte pin_sensor, float frequence){
    this->_Sensibilite = sensibilite;
    this->_PinSensor = pin_sensor;
    this->_Frequence = frequence;
}

/**
 * Constructeur
 * @sensibilite : sensibilité du capteur en mV
 * @pin_sensor : entrée analogique du capteur
 * @frequence : valeur de la fréquence pour tension alternative
 * @pin_sensor_ref_U : entrée analogique pour refence de tension
*/
sensorACS::sensorACS(float sensibilite, byte pin_sensor, float frequence, byte pin_sensor_ref_U){
    this->_Sensibilite = sensibilite;
    this->_PinSensor = pin_sensor;
    this->_Frequence = frequence;
    this->_PinSensor_refU = pin_sensor_ref_U;
}


/**
 * Void
 * @value : valeur de la tension (utiliser pour le calcul de la puissance)
*/
void sensorACS::SetTension(float value){
    this->_Tension = value;
}


/**
 * Void
 * Lecture de l'entrée analogique du capteur de courant
*/
void sensorACS::ReadSensorADC(){
    int valeur = 0;
    int valeurMax = 0;
    minuteur.demarrer(this->Echantillonnage(this->_Frequence));
    while ( !minuteur.estTermine() ){
    valeur = analogRead( this->_PinSensor );
        if ( valeur > valeurMax ) {
            valeurMax = valeur;
        }
    }
    this->_TensionRef =  analogRead(this->_PinSensor_refU);
    this->_Courant = max(valeurMax, (this->_TensionRef/2));
}


/**
 * Function
 * Return : la valeur Crete du Courant
*/
float sensorACS::GetCourantCrete(){
    return (this->_Courant-(this->_TensionRef/2))/((this->_Sensibilite/1000)*1024/5);
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
 * Return : le temps d'une période utilisé pour la durée de lecture de l'entrée analogique
*/
int sensorACS::Echantillonnage(float frequence){
    return (1/max(frequence, 20))*1000;
}