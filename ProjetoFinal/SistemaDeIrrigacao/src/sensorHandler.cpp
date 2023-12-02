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
  flagEstaAgoando = 1;
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

// NOTA IMPORTANTE: Ainda tem que melhorar isso aqui, n sei se ta 100% a lógica mas acho q ta no caminho certo

void sensorHandler() 
{
  float higroVal, LDRVal, tempVal, humVal;

  // Na prática não vai ter pra que criar uma lógica com a luminosidade
  LDRVal = readBrightness();

  // Então criei pelo menos uma função pra calcular a media da luminosidade, se tiver num nivel razoavel ele diz e tals
  brightnessMeanCalc();

  // Esses tem que usar mesmo
  higroVal = readMoisture();
  tempVal = readDHTTemperature();
  humVal = readDHTHumidity();

  int hour = getHour();

  // Pegando aqui os minutos
  unsigned long int milis = millis();
  unsigned long int minutes = milis / 60000;
  unsigned long int lastBombaTime = 0;
  // Quero testar na prática pra ver se ele vai conseguir ler o tempo certo, se não, vou ter que usar o millisecond direto sepa, ai é meio merda
  // Se a bomba ta ligada, vê se passou 5m
  if (bombaStatus)
  {
    if (minutes - lastBombaTime > 5)
    {
      turnOffBomba();
      flagEstaAgoando = 0;
    }
    lastBombaTime = minutes;
  }
  // Se não, vê se ta em um horário de regar, ai é pra chegar as condições de temperatura, umidade do ar e do solo pra decidir se rega ou não
  else
  {
    if (contLastWateredTime > 3)
    {
      contLastWateredTime = 0;
      regar();
    }
    else
    {
      if (hour == 0 || hour == 6 || hour == 12 || hour == 18 && flagEstaAgoando == 0)
      {
        contLastWateredTime++;
        if (higroVal < 30)
        {
          regar();
        }
        else if (tempVal > 30 && higroVal < 60)
        {
          regar();
        }
        else if (tempVal > 30 && humVal < 40)
        {
          regar();
        }
      }
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