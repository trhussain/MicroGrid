#include "config.h"

void setup() {
  Serial.begin(115200);
  displaySetup();
  wifiSetup();
  delay(2000);
  infoPage();
}


void loop() {
  // playBouncingEarsAnimation();
  delay(1000);
  printIP();
}
