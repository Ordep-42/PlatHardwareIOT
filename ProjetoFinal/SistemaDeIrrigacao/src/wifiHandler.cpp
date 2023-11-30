#include "wifiHandler.h"

WiFiClient wifi_client;

const char* wifi_ssid = "NPITI-IoT";
const char* wifi_password = "NPITI-IoT";
int wifi_timeout = 100000;

void initWiFi() {
    Serial.println("Inicializando WiFi...");
    WiFi.mode(WIFI_STA);
    WiFi.begin(wifi_ssid, wifi_password);
    connectWiFi();
}

void connectWiFi() {
  Serial.println("Conectando à rede WiFi .. ");

  unsigned long tempoInicial = millis();
  while (WiFi.status() != WL_CONNECTED && (millis() - tempoInicial < wifi_timeout)) {
    Serial.print("Status: ");
    Serial.println(WiFi.status());
    delay(100);
  }
  Serial.println();

  if (WiFi.status() != WL_CONNECTED) {
    printDisconnectedWiFiStatus();
  } else {
    printConnectedWiFiStatus();
  }
}

void printConnectedWiFiStatus() {
    Serial.println("Conectado à rede WiFi!");
    Serial.print("Endereço IP: ");
    Serial.println(WiFi.localIP());
}

void printDisconnectedWiFiStatus() {
    Serial.println("WiFi não conectado!");
}

void printWiFiScanStatus(int networksFound) {
    if (networksFound == 0) {
        Serial.println("Nenhuma rede WiFi encontrada!");
    } else {
        Serial.print(networksFound);
        Serial.println(" redes WiFi encontradas!");
    }
}

void printDiscoveredWiFiNetworks(int networksFound) {
    for (int i = 0; i < networksFound; i++) {
        Serial.print(i + 1);
        Serial.print(": ");
        Serial.print(WiFi.SSID(i));
        Serial.print(" (");
        Serial.print(WiFi.RSSI(i));
        Serial.print(")");
        Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? " " : "*");
        delay(10);
    }
}

void scanAvailableWiFiNetworks() {
    int networksFound = WiFi.scanNetworks();
    printWiFiScanStatus(networksFound);
    if (networksFound > 0) {
        printDiscoveredWiFiNetworks(networksFound);
    }
}
