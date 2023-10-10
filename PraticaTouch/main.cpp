#include <Arduino.h>

#define LED_START 2
#define BLINK_INTERVAL 500
#define TOUCH_PIN_1 14
#define TOUCH_PIN_2 12
#define START 4

int ledState = LOW;

unsigned long previousMillis = 0;
unsigned long player1Millis = 0;
unsigned long player2Millis = 0;

void imprimirInformacoes()
{
  Serial.print("Touch start:    ");
  Serial.println(touchRead(START));
  Serial.print("\nTouch Player 1: ");
  Serial.println(touchRead(TOUCH_PIN_1));
  Serial.print("\nTouch Player 2: ");
  Serial.println(touchRead(TOUCH_PIN_2));
  Serial.print("\n\n");
}

void joguinho()
{
  int jogador = 0;
  for (int i = 0; i < 3; i++)
  {
    digitalWrite(LED_START, HIGH);
    delay(500);

    digitalWrite(LED_START, LOW);
    if (i < 2)
    {
      delay(500);
    }
  }
  unsigned long startMillis = millis();
  Serial.println("Jogo iniciado!\n");
  while (jogador == 0)
  {
    if (player1Millis == 0 && player2Millis == 0)
    {
      if (touchRead(TOUCH_PIN_1) < 30)
      {
        player1Millis = millis();
        Serial.println("Jogador 1 ganhou!");
        Serial.print("Tempo de reação: ");
        Serial.print(player1Millis - startMillis);
        Serial.println("ms");
        digitalWrite(22, HIGH);
        delay(3000);
        digitalWrite(22, LOW);
        jogador = 1;
      }
      else if (touchRead(TOUCH_PIN_2) < 30)
      {

        player2Millis = millis();
        Serial.println("Jogador 2 ganhou!");
        Serial.print("Tempo de reação: ");
        Serial.print(player2Millis - startMillis);
        Serial.println("ms");
        digitalWrite(15, HIGH);
        delay(3000);
        digitalWrite(15, LOW);
        jogador = 1;
      }
    }
  }
}

void setup()
{
  Serial.begin(9600);
  Serial.println("JOGO DO REFLEXO");
  delay(1000);
  pinMode(LED_START, OUTPUT);

  pinMode(22, OUTPUT);

  pinMode(15, OUTPUT);


}

void loop()
{
  // imprimirInformacoes();
  digitalWrite(22,LOW);
  digitalWrite(15,LOW);
  int start = 0;
  Serial.println("\nAperte start para começar o jogo...");
  while (start == 0)
  {
    if (touchRead(START) < 30)
    {
      joguinho();
      start = 1;
    }
  }
  player1Millis = 0;
  player2Millis = 0;
  delay(500);
}
