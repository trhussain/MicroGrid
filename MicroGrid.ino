#include "config.h"



bool powerCycleOn = false;
unsigned long powerStartTime = 0;
const unsigned long cycleInterval = 15000; // 10 seconds
unsigned long lastToggleTime = 0;

void setup() {
  Serial.begin(115200);
  displaySetup();
  wifiSetup();
  delay(2000);
  infoPage();
  sensorSetup();
}


void loop() {

  Serial.println("Test print");
  delay(500);
}
