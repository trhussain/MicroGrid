#include "config.h"
 
void setup() {
  Serial.begin(115200);
  wifiSetup();
  displaySetup();
  sensorSetup();
  infoPage();
  delay(2000);

}



void loop() {

  if (webpageOpened) {
    dataPage();
  }

  delay(1000);  
  float fiveIn = readFiveVoltage();
  Serial.printf("Five input: ");
  Serial.println(fiveIn);

}
