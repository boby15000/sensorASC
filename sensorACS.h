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
    float GetCourant();
    float GetPuissance();

  private :
    byte _PinSensor;
    byte pin_sensor_ref;
    int _Sensibilite;

};

#endif