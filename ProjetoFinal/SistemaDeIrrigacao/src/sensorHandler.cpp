#include "sensorHandler.h"
#include "relayHandler.h"
#include "setupSensors.h"

void initGarden(){
  initRelay();
  initSensors();  
}


void sensorHandler()
{
  float higroVal, LDRVal, tempVal, humVal;
  higroVal = readMoisture();
  LDRVal = readBrightness();
  tempVal = readDHTTemperature();
  humVal = readDHTHumidity();

  if(higroVal < 40)
  {
    turnOnBomba();
  }
  else
  {
    turnOffBomba();
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
  Ideal  : ???

Luminosidade:
  Máxima : 100%
  Mínima : 0%
  Ideal  : ???

Temperatura:
  Máxima : 40ºC
  Mínima : 20ºC
  Ideal  : 25ºC - 30ºC





*/