#include <SoftwareSerial.h>
#define ButtonPin 12

SoftwareSerial ArduinoSlave(10, 11);

String answer;
String msg;
String sensor;
String botao;
int sensorValue = 0, oldSensorValue = 0;
int buttonValue = 0, oldButtonValue = 0;

void setup() {
  Serial.begin(9600);
  ArduinoSlave.begin(9600);
  pinMode(ButtonPin, INPUT_PULLUP);
}

void loop() {
  sensorValue = analogRead(A0);
  buttonValue = !digitalRead(ButtonPin);

  sensor = String(sensorValue);
  botao = String(buttonValue);

  msg = sensor + "*" + botao;

  readSlavePort();

  if (oldSensorValue != sensorValue || oldButtonValue != buttonValue) {
    Serial.print("Master sent: ");
    Serial.println(msg);
    ArduinoSlave.print(msg);
    if (sensorValue < 50) {
      Serial.println("Baixa luminosidade!");
    }
    oldSensorValue = sensorValue;
    oldButtonValue = buttonValue;
  }

  if (answer != "") {
    Serial.print("Luminosidade do LED");
    Serial.println(answer);
    answer = "";
  }

  delay(500);
}

void readSlavePort() {
  while(ArduinoSlave.available()) {
    delay(10);
    if (ArduinoSlave.available() > 0) {
      char c = ArduinoSlave.read();
      answer += c;
    }
  }
}