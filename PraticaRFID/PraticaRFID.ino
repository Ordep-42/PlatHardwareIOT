#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>

//Definição dos pinos de conexão do projeto
#define PINO_SS 9
#define PINO_RST 8
#define PINO_LED_VERM 21
#define PINO_LED_VERD 20
#define PINO_BUZZER 19


//Cria o item para configurar o módulo RC522
MFRC522 mfrc522(PINO_SS, PINO_RST);
int contador = 0;

void setup() {
  pinMode(PINO_LED_VERM, OUTPUT);
  pinMode(PINO_LED_VERD, OUTPUT);
  pinMode(PINO_BUZZER, OUTPUT);
  Serial.begin(9600);  // Inicializa a serial
  SPI.begin();         // Inicializa a comunicação SPI
  mfrc522.PCD_Init();  // Inicializa o módulo MFRC522
  Serial.println("Sistema Inicializado: Aproxime o token");
  digitalWrite(PINO_LED_VERM, HIGH);
  digitalWrite(PINO_LED_VERD, LOW);
}

void loop() {
  if (!mfrc522.PICC_IsNewCardPresent()) return;
  if (!mfrc522.PICC_ReadCardSerial()) return;

  String conteudo = "";         //Cria uma variável vazia, do tipo string
  byte letra;

  for (byte i = 0; i < mfrc522.uid.size; i++) {
    if (mfrc522.uid.uidByte[i] < 0x10) {
      conteudo.concat(String(" 0"));
    } else {
      conteudo.concat(String(" "));
    }
    conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  conteudo.toUpperCase();  //Coloca todas as letras da string em
  if (conteudo.substring(1) == "E3 38 63 0D") {
    Serial.println("Acesso Liberado");
    digitalWrite(PINO_LED_VERM, LOW);
    digitalWrite(PINO_LED_VERD, HIGH);
    delay(10000);
    digitalWrite(PINO_LED_VERM, HIGH);
    digitalWrite(PINO_LED_VERD, LOW);
    contador = 0;
  } else {
    contador++;
    if (contador == 5) {
      Serial.println("SISTEMA BLOQUEADO");
      for (int i = 0; i < 60; i++) {
        digitalWrite(PINO_BUZZER, HIGH);
        digitalWrite(PINO_LED_VERM, LOW);
        delay(150);
        digitalWrite(PINO_LED_VERM, HIGH);
        delay(350);
      }
      digitalWrite(PINO_BUZZER, LOW);
      contador = 0;
    } else {
      Serial.println("Cartão inválido");
      for (int i = 0; i < 6; i++) {
        digitalWrite(PINO_LED_VERM, LOW);
        digitalWrite(PINO_LED_VERD, LOW);
        delay(300);
        digitalWrite(PINO_LED_VERM, HIGH);
        delay(100);
      }
    }
  }
  delay(100);
}