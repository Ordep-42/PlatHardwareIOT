#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 13
#define DHTTYPE DHT11

#define HIGROMETRO 12

DHT_Unified dht(DHTPIN, DHTTYPE);


void setup()
{
  Serial.begin(921600);
  pinMode(HIGROMETRO, INPUT);

  dht.begin();
}

void loop()
{
  delay(1000);
  int higroVal = analogRead(HIGROMETRO);

  sensors_event_t event;
  Serial.print("HIGROMETRO: ");
  Serial.println(higroVal);  
  dht.temperature().getEvent(&event);
  Serial.print(F("Temperature: "));
  Serial.print(event.temperature);
  Serial.println(F("°C"));
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  Serial.print(F("Humidity: "));
  Serial.print(event.relative_humidity);
  Serial.println(F("%"));
}