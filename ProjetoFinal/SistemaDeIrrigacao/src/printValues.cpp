#include "printValues.h"
#include "setupSensors.h"
#include "sensorHandler.h"

void printValues()
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
  } else{
    Serial.println("O dia está com uma baixa luminosidade!");
  }
}