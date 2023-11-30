#include "sensorHandler.h"

void initGarden()
{
  initRelay();
  initSensors();
  initNTP();
}

void BrightnessMeanCalc()
{
  if (getHour() >= 6 && getHour() < 18)
  {
    brightnessMean = (brightnessMean + readBrightness()) / 2;
  }
}

void sensorHandler()
{
  float higroVal, LDRVal, tempVal, humVal;
  higroVal = readMoisture();
  LDRVal = readBrightness();
  tempVal = readDHTTemperature();
  humVal = readDHTHumidity();
  
  BrightnessMeanCalc();

  int hour = getHour();
  int LastWateringHour;
  int contLastWateringHour = 0;

  if (hour == 0 || hour == 6 || hour == 12 || hour == 18)
  {
    if(higroVal)

    LastWateringHour = hour;
  }
  {
  }
  

}

/*
Umidade do ar:
  Máxima : 100%
  Mínima : 0%
  Ideal  : <40%

Umidade do solo:
  Máxima : 100%
  Mínima : 0%
  Ideal  : 60% - 80%
  Crítico: >30%


Luminosidade:
  Máxima : 100%
  Mínima : 0%
  Ideal  : <30%

Temperatura:
  Máxima : 40ºC
  Mínima : 20ºC
  Ideal  : 25ºC - 30ºC





*/