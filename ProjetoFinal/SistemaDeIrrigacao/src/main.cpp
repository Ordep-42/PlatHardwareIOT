#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 13
#define DHTTYPE DHT11
#define HIGROMETRO 12
#define BOMBA 2
#define LDR 14

int higroVal = 0;
int higroValMapped = 0;
int LDRVal = 0;
int LDRValMapped = 0;
sensors_event_t eventTemp;
sensors_event_t eventHum;

DHT_Unified dht(DHTPIN, DHTTYPE);

void readValues()
{
  higroVal = analogRead(HIGROMETRO);
  higroValMapped = map(higroVal, 2900, 1400, 0, 100);

  if (higroValMapped < 0)
  {
    higroValMapped = 0;
  }
  else if (higroValMapped > 100)
  {
    higroValMapped = 100;
  }

  LDRVal = analogRead(LDR);
  LDRValMapped = map(LDRVal, 4095, 500, 0, 100);
  if (LDRValMapped > 100)
  {
    LDRValMapped = 100;
  }
  //Ler temperatura
  dht.temperature().getEvent(&eventTemp);
  //Ler umidade
  dht.humidity().getEvent(&eventHum);
}

void printValues(){
Serial.println("---------------------");
  Serial.print("LDR: ");
  Serial.print(LDRValMapped);
  Serial.println("%");
  Serial.print("Higrômetro: ");
  Serial.print(higroValMapped);
  Serial.println("%");
  Serial.print(F("Temperature: "));
  Serial.print(eventTemp.temperature);
  Serial.println(F("°C"));
  Serial.print(F("Humidity: "));
  Serial.print(eventHum.relative_humidity);
  Serial.println(F("%"));
}

void setup()
{
  Serial.begin(921600);
  pinMode(LDR, INPUT);
  pinMode(HIGROMETRO, INPUT);
  pinMode(BOMBA, OUTPUT);
  dht.begin();
}

void loop()
{
  delay(1000);
  readValues();
  printValues();
  if (higroValMapped <= 30)
  {
    digitalWrite(BOMBA, HIGH);
  }
  else if (higroValMapped > 70)
  {
    digitalWrite(BOMBA, LOW);
  }
}