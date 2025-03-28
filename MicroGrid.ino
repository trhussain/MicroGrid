#include "config.h"
 
bool networkCon = false;
void setup() {
  Serial.begin(115200);
  wifiSetup();
  displaySetup();
  sensorSetup();
  infoPage();
  delay(2000);

}



void loop() {

  // okay read in raw value 
  // its 0-4096
  // what if i attached the 9v batter just to test ?
  // such a bad idea... shits down to 1 nearly lmfao 
  // delay(5000);
  // float adc_voltage_solarV =  analogRead(adc_solarV);        
  // float adc_zeroed_solarV = adc_voltage_solarV * (3.3 / 4096.0);
  // float current_voltage_solarV = (adc_zeroed_solarV * (R1_volt+R2_volt)/R2_volt);
  // float solar_voltage = (current_voltage_solarV) / 0.100;
  // Serial.printf("Raw Voltage: %.2f - ", adc_voltage_solarV);
  // Serial.printf("Solar V %.2f:      \n", current_voltage_solarV);
  // Serial.println("");
  // float pleasWork = map(adc_voltage_solarV, 0, 1023, 0, 10);
  // Serial.printf("Mapped: %.2f\n", pleasWork); 
  // dataPage();
}
