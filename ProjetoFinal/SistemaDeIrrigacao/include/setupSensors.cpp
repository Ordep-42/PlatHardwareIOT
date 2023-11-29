#include "setupSensors.h"

DHT_Unified dht(DHTPIN, DHTTYPE);
const unsigned long readInterval = 5000;

float readDHTTemperature() {
    static unsigned long lastReadTime = 0;
    if (millis() - lastReadTime > readInterval) {
        lastReadTime = millis();
        sensors_event_t event;
        dht.temperature().getEvent(&event);
        float data = event.temperature;
        return data;
    }
}

float readDHTHumidity() {
    static unsigned long lastReadTime = 0;
    if (millis() - lastReadTime > readInterval) {
        lastReadTime = millis();
        sensors_event_t event;
        dht.humidity().getEvent(&event);
        float data = event.relative_humidity;
        return data;
    }
}

float readBrightness() {
    static unsigned long lastReadTime = 0;
    if (millis() - lastReadTime > readInterval) {
        lastReadTime = millis();
        float data = fmap(analogRead(LDRPIN), 4095, 500, 100, 0);
        return data;
    }
}

float readMoisture() {
    static unsigned long lastReadTime = 0;
    if (millis() - lastReadTime > readInterval) {
        lastReadTime = millis();
        float data = fmap(analogRead(HIGROMETROPIN), 2900, 1400, 100, 0);
        return data;
    }
}