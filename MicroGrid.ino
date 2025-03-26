#include "config.h"
const int powerControl = 32; 
const int load_1 = 23; 
const int load_2 = 22; 
const int power2 = 33; 


void setup() {
  Serial.begin(115200);
  displaySetup();
  wifiSetup();
  delay(2000);
  infoPage();
  sensorSetup();
  pinMode(power2, OUTPUT);
  pinMode(powerControl, OUTPUT);
  pinMode(load_1, OUTPUT);
  pinMode(load_2, OUTPUT);


}


void loop() {
  if (WiFi.softAPgetStationNum() > 0) {
    EVERY_N_MILLIS(5000) { 
      dataPage();
    }
  } else {
      digitalWrite(powerControl, HIGH);
      digitalWrite(load_1, HIGH);
      digitalWrite(load_2, HIGH);
      digitalWrite(power2, HIGH);
      infoPage();
      sensorPrintOut();
      delay(5000);
      // digitalWrite(powerControl, LOW);
      digitalWrite(load_1, LOW);
      digitalWrite(load_2, LOW);
      // digitalWrite(power2, LOW);

      delay(1000);
  }
}
