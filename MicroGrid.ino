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


  delay(2000);
  float adc_voltage_solarV =  analogRead(adc_solarV);        
  float adc_zeroed_solarV = adc_voltage_solarV * (3.3 / 4096.0);
  float current_voltage_solarV = (adc_zeroed_solarV * (R1_volt+R2_volt)/R2_volt); // error reading offset
  Serial.printf("Solar V %.2f:      \n", current_voltage_solarV);
  Serial.println("");
  // dataPage();
}
