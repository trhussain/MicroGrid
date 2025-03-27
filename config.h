/*
CONFIG.H 

Contains pinouts & all system configurations 

*/
#ifndef CONFIG_H
#define CONFIG_H
// libraries 
#include "ACS712.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <WiFi.h>
#include <AsyncTCP.h>
// #include <WebSocketsServer.h>     // Might not be needed but harmless
#include <ESPAsyncWebServer.h>    // Already in config.h — good
#include <AsyncWebSocket.h>  
#include <Arduino_JSON.h>
#include <FastLED.h>

#include <movingAvg.h>
#include "LittleFS.h"

// pin definitions


// Define the SDA and SCL pins manually
#define OLED_SDA 18
#define OLED_SCL 5 // Update accordingly with your pinout 


// Other 

// OLED Parameters 
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define SCREEN_ADDRESS 0x3C  // Check your OLED's address if different
#define OLED_RESET    -1                   

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Soft Access Point credentials
const char* ssid = "net_1";
const char* password = "my_pwd_1";
// change 3rd argument (4 initially) for different device ID's 
// IPAddress local_IP(192, 168, 4, 1);     // AP IP address
// IPAddress gateway(192, 168, 4, 1);      // Usually same as AP IP
// IPAddress subnet(255, 255, 255, 0);     // Subnet mask

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

// Create a WebSocket object
AsyncWebSocket ws("/ws");

// Json Variable to Hold Sensor Readings
JSONVar readings;



// Auxiliar variables to store the current output state
String load1State = "off";
String load2State = "off";
String load3State = "off";
String solarRailState = "off";
String fiveVRailState = "off";
String nineVRailState = "off";


/*
Analog ADC
Solar Panel Voltage: 34
Load Current: 35
5V Current: 32

Transistor Gates: 
Solar Panel: 25
5V Line: 33
9V Line: 19 
Loads: 21 22 23 
*/


const int adc_solarV = 34;
const int adc_loadC = 35;
const int adc_fiveCurrent = 32;

const int sw_solar = 25;
const int sw_five = 33;
const int sw_nine = 19;

const int sw_load1 = 21;
const int sw_load2 = 22;
const int sw_load3 = 23;

const int zero_reading = 850;

const int R1_acs = 47000;
const int R2_acs= 75000;
const int R1_volt = 10000;
const int R2_volt = 5000;




struct sensorData {
  float vBatt;
  float vSolar;
  float aSolar;
} mySensorData;


// 'download', 20x20px
const unsigned char epd_bitmap_download [] PROGMEM = {
	0xff, 0xff, 0xf0, 0xff, 0xf1, 0xf0, 0xff, 0xe0, 0xf0, 0xff, 0xf8, 0x70, 0xff, 0xde, 0x70, 0x8f, 
	0x8e, 0x70, 0x86, 0x0f, 0x70, 0x80, 0x0e, 0x70, 0x8c, 0x1c, 0x70, 0xc8, 0x00, 0xf0, 0xac, 0x00, 
	0x70, 0x9e, 0x00, 0x70, 0x80, 0x00, 0x70, 0x80, 0x04, 0x70, 0xe0, 0x0f, 0xf0, 0xf8, 0x43, 0x70, 
	0xf8, 0x59, 0x70, 0xfc, 0xdb, 0x70, 0xf8, 0xb0, 0xf0, 0xff, 0xff, 0xf0
};
int dinoX = 0;
int dinoSpeed = 5;  // pixels per frame
unsigned long lastFrame = 0;

#endif  //
