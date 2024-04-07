#if ARDUINO >= 100    
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#ifndef sensorACS_INCLUDED
#define sensorACS_INCLUDED


class sensorACS
{
  public :
    // contructeur
    sensorACS(byte pin_sensor, float sensibilite, byte unite_sensibilite, float frequence = 50, float tension = 230);

    void Etalonnage();
    float GetCourantCrete();
    float GetCourantEff();
    float GetPuissance();

  private :
    byte _PinSensor;
    float _Sensibilite;
    byte _UniteSensibilite;
    float _Tension;
    int _Echantillonnage;
    int _TensionRef;

    int ReadingSensor();
};

#endif