#include <Arduino.h>
#include <NTPClient.h> /* https://github.com/arduino-libraries/NTPClient */
#include <WiFi.h> /* Biblioteca do WiFi. */

/*-------- Configurações de Wi-fi----------- */
const char* ssid = "NPITI-IoT"; /* Substitua pelo nome da rede */
const char* password = "NPITI-IoT";    /* Substitua pela senha */
/* -------- Configurações de relógio on-line----------- */
WiFiUDP udp;
NTPClient ntp(udp);/* Cria um objeto "NTP" com as configurações.utilizada no Brasil */
String hora;            /* Variável que armazena */
String dia;

void setup()
{
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  delay(2000);               /* Espera a conexão. */
  ntp.begin();               /* Inicia o protocolo */
  ntp.forceUpdate();    /* Atualização */
  ntp.setTimeOffset(-10800);
}
void loop()
{
  /* Armazena na variável hora, o horário atual. */
  //dia = ntp.getDay();
  hora = ntp.getFormattedDate();
  //Serial.print(dia);
  //Serial.print(" ");
  Serial.println(hora);     /* Escreve a hora no monitor serial. */
  delay(1000);              /* Espera 1 segundo. */
}