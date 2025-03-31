/*
DISPLAY 

Utility functions for OLED 128x64 module 

*/
#include "config.h"


void displaySetup() {
  Wire.begin(OLED_SDA, OLED_SCL);
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println("OLED init failed");
    while (true)
      ;  // Halt
  }
      display.setTextSize(1);
  display.setTextColor(WHITE);
  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  Serial.println("Splash screen here");

  delay(2000); // Pause for 2 seconds
  display.clearDisplay();

}

void infoPage()  {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Hello! Take a pic of");
  display.println("the following info:");

  display.print("Wifi Name: ");
  display.println(ssid);
  display.print("PWD: ");
  display.println(password);
  IPAddress IP = WiFi.softAPIP(); // Get the IP address of the AP
  display.print("IP: ");
  display.println(IP);
  // 7 spaces
  display.print("  --No Connections--");
  display.display();

}
void connectedNoBrowserPage() { 
  display.clearDisplay();
  display.setCursor(0,0);
  display.println("User connected to network, open a Chrome/Safari browser and enter this IP address");
  IPAddress IP = WiFi.softAPIP(); // Get the IP address of the AP
  display.print("IP: ");
  display.println(IP);
}

void dataPage()  {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Connected!");
  // myDataSensors someSensorData = sensor_process();
  float solarVoltage = readSolarVoltage();
  display.print("Solar V: ");
  display.print(solarVoltage , 2);  // 2 decimal places
  display.println("V");

  display.print("Inst. Load C: ");
  display.print(myLoadCurrent, 2);
  display.println("mA");

  display.display();

  }

