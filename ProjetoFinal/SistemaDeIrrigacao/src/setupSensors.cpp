#include "setupSensors.h"

DHT_Unified dht(DHTPIN, DHTTYPE);

float readDHTTemperature() {
    sensors_event_t event;
    dht.temperature().getEvent(&event);
    float data = event.temperature;
    return data;
}

float readDHTHumidity() {
    sensors_event_t event;
    dht.humidity().getEvent(&event);
    float data = event.relative_humidity;
    return data;
}

float readBrightness() {
    float data = fmap(analogRead(LDRPIN), 4095, 500, 0, 100);
    if (data > 100) {
        data = 100;
    }
    return data;
}

float readMoisture() {
    float data = fmap(analogRead(HIGROMETROPIN), 2900, 1400, 0, 100);
    if (data < 0) {
        data = 0;
    } else if (data > 100) {
        data = 100;
    }
    return data;
}

void initSensors() {
    pinMode(HIGROMETROPIN, INPUT);
    pinMode(LDRPIN, INPUT);
    dht.begin();
}