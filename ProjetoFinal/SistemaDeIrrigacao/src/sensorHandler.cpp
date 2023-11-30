#include "sensorHandler.h"

float brightnessMean = 0;

void initGarden()
{
  initRelay();
  initSensors();
  initNTP();
}

void printValuesToSerial()
{

  float higroVal, LDRVal, tempVal, humVal;
  higroVal = readMoisture();
  LDRVal = readBrightness();
  tempVal = readDHTTemperature();
  humVal = readDHTHumidity();

  Serial.println("---------------------");
  Serial.println("%");
  Serial.print("Higrômetro: ");
  Serial.print(higroVal);
  Serial.println("%");
  Serial.print(F("Temperature: "));
  Serial.print(tempVal);
  Serial.println(F("°C"));
  Serial.print(F("Humidity: "));
  Serial.print(humVal);
  Serial.println(F("%"));
  Serial.print("LDR: ");
  Serial.println(LDRVal);
  if (brightnessMean < 50)
  {
    Serial.println("O dia está com uma boa luminosidade!");
  } else {
    Serial.println("O dia está com uma baixa luminosidade!");
  }
}

void brightnessMeanCalc()
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
  
  brightnessMeanCalc();

  int hour = getHour();
  int LastWateringHour;
  int contLastWateringHour = 0;

  if (hour == 0 || hour == 6 || hour == 12 || hour == 18)
  {
    if(higroVal)

    LastWateringHour = hour;
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