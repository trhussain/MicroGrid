#include "config.h"



bool powerCycleOn = false;
unsigned long powerStartTime = 0;
const unsigned long cycleInterval = 15000; // 10 seconds
unsigned long lastToggleTime = 0;

void setup() {
  Serial.begin(115200);
  sensorSetup();
  digitalWrite(sw_solar, HIGH);
  digitalWrite(sw_five, HIGH);

  
}


void loop() {
  addToAverages();
  sensorPrintOut();
  sensor_process();

  unsigned long currentTime = millis();

  if (currentTime - lastToggleTime >= cycleInterval) {
    lastToggleTime = currentTime;
    powerCycleOn = !powerCycleOn;  // toggle state

    if (powerCycleOn) {
      digitalWrite(sw_load1, HIGH);
      digitalWrite(sw_load2, HIGH);
      digitalWrite(sw_load3, HIGH);


      Serial.println("Power ON");

    } else {
      digitalWrite(sw_load1, LOW);
      digitalWrite(sw_load2, LOW);
      digitalWrite(sw_load3, LOW);

      // optionally:
      // digitalWrite(powerControl, LOW);
      // digitalWrite(power2, LOW);
      Serial.println("Power OFF");
    }
  }
  delay(500);
}
