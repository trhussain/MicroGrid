const int largePower = 14;
const int smallPower = 12;
void sensorSetup() { 
  pinMode(largePower, INPUT);
  pinMode(smallPower, INPUT);
}

// Read sensor -> default 2.5 -> 4096/2

void sensorPrintOut() { 
  Serial.print("Large power raw: [");
  Serial.print(analogRead(largePower));
  Serial.println("]"); 
  Serial.print("Small power raw: [");
  Serial.print(analogRead(smallPower));
  Serial.println("]"); 
}

int return_large()  {
  auto largeOutput_raw = analogRead(largePower);
  return largeOutput_raw;

}
int return_small() { 
  auto smallOutput_raw = analogRead(smallPower);
  return smallOutput_raw; 
}
