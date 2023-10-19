#include <SoftwareSerial.h>

#define LEDPin 12;

SoftwareSerial ArduinoMaster(10, 11);

String msg = ""; 
String sensor = "";
String button = "";

int ledVal = 0;
int sensorVal = 0, oldSensorVal = 0;
int buttonVal = 0;

void setup() {
  Serial.begin(9600);
  ArduinoMaster.begin(9600);
  pinMode(12, OUTPUT);
}

void loop() {
  readMasterPort();
  convertMsgToCmd();

  
  if (buttonVal == 1) {
    digitalWrite(12, 1);
  } else {
    if (sensorVal != oldSensorVal) {
    Serial.print("Master sent: ");
    Serial.println(sensorVal);
    Serial.println(buttonVal);

    ledVal = map(sensorVal, 511, 0, 0, 255);
    if (ledVal < 0){
      ledVal = 0;
    }

    Serial.print("LED Value: ");
    Serial.println(ledVal);
    ArduinoMaster.print(ledVal);
    analogWrite(12, ledVal);

    oldSensorVal = sensorVal;
    }  
  }
}

void readMasterPort() {
  while (ArduinoMaster.available()) {
    delay(10);
    if (ArduinoMaster.available() > 0) {
      char c = ArduinoMaster.read();
      msg += c;
    }
  }
  int separador = msg.indexOf("*");
  for (int i = 0; i < msg.length(); i++) {
    Serial.print("caractere atual ");
    if (i < separador) {
      sensor += msg[i];
      Serial.println(msg[i]);
    } else if (i > separador) {
      button += msg[i];
      Serial.println(msg[i]);
    }
  }

  ArduinoMaster.flush();
}

void convertMsgToCmd() {
  if (msg.length() > 0) {
    char sensorArray[4];
    char buttonChar[2];
    Serial.print("Strings ");
    Serial.print(sensor);
    Serial.print(", ");
    Serial.println(button);
    sensor.toCharArray(sensorArray, sizeof(sensorArray));
    button.toCharArray(buttonChar, sizeof(buttonChar));
    sensorVal = atoi(sensorArray);
    buttonVal = atoi(buttonChar);

    msg = "";
    sensor = "";
    button = "";
  }
}