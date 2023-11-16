#include <Arduino.h>

#include <FS.h>
#include "SPIFFS.h"
#include <WiFi.h>
#include <NTPClient.h>

#define LED 2
#define botao 4

const char *ssid = "nome-da-rede";
const char *password = "senha-da-rede";

String str;
String s;

int botaoVal, ledVal = 0, oldVal = 0, oldLedVal;

WiFiUDP udp;
NTPClient ntp(udp); /* Cria um objeto "NTP" com as configurações.utilizada no Brasil */
String data;

void writeFile(String state, String path, char format[])
{                                         // escreve conteúdo em um arquivo
  File rFile = SPIFFS.open(path, format); // a para anexar
  if (!rFile)
  {
    Serial.println("Erro ao abrir arquivo!");
  }
  else
  {
    rFile.println(state);
  }
  rFile.close();
}

String readFile(String path)
{
  Serial.println("Read file");
  File rFile = SPIFFS.open(path, "r+"); // r+ leitura e escrita
  if (!rFile)
  {
    Serial.println("Erro ao abrir arquivo!");
  }
  else
  {
    while (rFile.position() < rFile.size())
    {
      s = rFile.readStringUntil('\n');
      s.trim();
      Serial.println(s);
    }
    rFile.close();
    return s;
  }
}

void formatFile()
{
  Serial.println("Formantando SPIFFS");
  SPIFFS.format();
  Serial.println("Formatou SPIFFS");
}

void openFS(void)
{
  if (!SPIFFS.begin())
  {
    Serial.println("\nErro ao abrir o sistema de arquivos");
  }
  else
  {
    Serial.println("\nSistema de arquivos aberto com sucesso!");
  }
}

void setup()
{
  pinMode(botao, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
  Serial.begin(921600);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);                    /* Aguarda meio segundo */
    Serial.println(WiFi.status()); /* Conectando */
  }
  Serial.println("Conectado"); /* Conectado */
  delay(200);

  ntp.begin();       /* Inicia o protocolo */
  ntp.forceUpdate(); /* Atualização */
  ntp.setTimeOffset(-10800);
  // formatFile();

  openFS();
  String s = readFile("/ledState.txt");
  oldLedVal = s.toInt();
  digitalWrite(LED, oldLedVal);
}

void loop()
{
  botaoVal = !digitalRead(botao);
  if (botaoVal == 1 && botaoVal != oldVal)
  {
    ledVal = (ledVal == LOW ? HIGH : LOW);
    digitalWrite(LED, ledVal);
    delay(50);
    data = ntp.getFormattedDate();
    writeFile(data, "/ledLog.txt", "a+");
    readFile("/ledLog.txt");
  }
  oldVal = botaoVal;

  str = String(ledVal);
  writeFile(str, "/ledState.txt", "w+");
  delay(100);
}
