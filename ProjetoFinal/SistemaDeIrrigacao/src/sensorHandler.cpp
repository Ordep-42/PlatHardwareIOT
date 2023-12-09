#include "sensorHandler.h"


float brightnessMean = 0;
int flagEstaAgoando = 0;
int contLastWateredTime = 0;

void initGarden()
{
  initRelay();
  initSensors();
  initNTP();
}

void regar()
{
  Serial.println("Regando...");
  contLastWateredTime = 0;
  turnOnBomba();
}

void printValuesToSerial()
{

  float higroVal, LDRVal, tempVal, humVal;
  higroVal = readMoisture();
  LDRVal = readBrightness();
  tempVal = readDHTTemperature();
  humVal = readDHTHumidity();

  Serial.println("---------------------");
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
  }
  else
  {
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
  float higroVal, tempVal, humVal;
  contLastWateredTime++;

  // Pegando valores dos sensores
  higroVal = readMoisture();
  tempVal = readDHTTemperature();
  humVal = readDHTHumidity();

  // Se passou mais de 24 horas desde a última rega, rega
  if (contLastWateredTime > 3)
  {
    regar();
  }
  else // Se não, verifica se precisa regar
  {
    if (higroVal < 30 || tempVal > 33 || humVal < 30 || (tempVal >= 28 && higroVal < 45) || (tempVal > 30 && humVal < 40) || (higroVal < 45 && humVal < 40))
    {
      regar();
    }
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