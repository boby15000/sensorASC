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
    sensorACS(float sensibilite, byte pin_sensor);
    sensorACS(float sensibilite, byte pin_sensor, byte pin_sensor_ref_U);
    sensorACS(float sensibilite, byte pin_sensor, float frequence);
    sensorACS(float sensibilite, byte pin_sensor, float frequence, byte pin_sensor_ref_U);

    void SetTension(float value);
    void ReadSensorADC();
    float GetCourantCrete();
    float GetCourantEff();
    float GetPuissance();

  private :
    byte _PinSensor;
    byte _PinSensor_refU;
    int _Sensibilite;
    float _Frequence;
    float _Tension;
    float _Courant;
    float _TensionRef;
};

#endif