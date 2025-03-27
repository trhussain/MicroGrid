

movingAvg five_c_avg(20); 
movingAvg load_c_avg(20); 
movingAvg solar_v_avg(5);

float five_current;
float load_current;
float solar_voltage; 

// const int adc_solarV = 34;
// const int adc_loadC = 35;
// const int adc_fiveCurrent = 32;

// const int sw_solar = 25;
// const int sw_five = 33;
// const int sw_nine = 19;

// const int sw_load1 = 21;
// const int sw_load2 = 22;
// const int sw_load3 = 23;
void sensorSetup() { 
  pinMode(adc_loadC, INPUT);
  pinMode(adc_fiveCurrent, INPUT);
  pinMode(adc_solarV, INPUT);

  pinMode(sw_solar, OUTPUT);
  pinMode(sw_five, OUTPUT);
  pinMode(sw_nine, OUTPUT);

  pinMode(sw_load1, OUTPUT);
  pinMode(sw_load2, OUTPUT);
  pinMode(sw_load3, OUTPUT);


  digitalWrite(sw_solar, LOW);
  digitalWrite(sw_five, LOW);
  digitalWrite(sw_nine, LOW);
  digitalWrite(sw_load1, LOW);
  digitalWrite(sw_load2, LOW);
  digitalWrite(sw_load3, LOW);

  five_c_avg.begin();
  load_c_avg.begin();
  solar_v_avg.begin();

}

// Read sensor -> default 2.5 -> 4096/2
void addToAverages() { 
  five_c_avg.reading(int(max(five_c_avg.getAvg() - zero_reading, 0)));
  load_c_avg.reading(int(max(load_c_avg.getAvg() - zero_reading, 0)));
  solar_v_avg.reading(int(max(solar_v_avg.getAvg() - zero_reading, 0)));

}
void sensorPrintOut() { 
  Serial.printf("Five V Line C-raw | avg: [%d] | [%d] \n", analogRead(adc_loadC), five_c_avg.getAvg());
  Serial.printf("Load C-raw | avg: [%d] | [%d] \n", analogRead(adc_fiveCurrent), load_c_avg.getAvg());
  Serial.printf("Solar Panel V-raw | avg: [%d] | [%d] \n", analogRead(adc_solarV), solar_v_avg.getAvg());

  //delay(500); 
}

void sensor_process() {
  float adc_voltage =  five_c_avg.getAvg() - zero_reading;
  float adc_zeroed = adc_voltage * (3.3 / 4096.0);
  float current_voltage = (adc_zeroed * (R1_acs+R2_acs)/R2_acs);
  five_current = (current_voltage) / 0.100;
  // Serial.print("5V Current: ");
  // Serial.println(five_current);


  float adc_voltage_loadC =  load_c_avg.getAvg() - zero_reading;
  float adc_zeroed_loadC = adc_voltage_loadC * (3.3 / 4096.0);
  float current_voltage_loadC = (adc_zeroed_loadC * (R1_acs+R2_acs)/R2_acs);
  load_current = (current_voltage_loadC) / 0.100;
  // Serial.print("Load Current: ");
  // Serial.println(load_current);

  float adc_voltage_solarV =  solar_v_avg.getAvg() - zero_reading;
  float adc_zeroed_solarV = adc_voltage_solarV * (3.3 / 4096.0);
  float current_voltage_solarV = (adc_zeroed_solarV * (R1_volt+R2_volt)/R2_volt);
  solar_voltage = (current_voltage_solarV) / 0.100;
  // Serial.print("Solar Voltage: ");
  // Serial.println(solar_voltage);

}

