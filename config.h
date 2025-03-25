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

#include "LittleFS.h"

// pin definitions


// Define the SDA and SCL pins manually
#define OLED_SDA 22
#define OLED_SCL 23 // Update accordingly with your pinout 


// Other 

// OLED Parameters 
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define SCREEN_ADDRESS 0x3C  // Check your OLED's address if different
#define OLED_RESET    -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Soft Access Point credentials
const char* ssid = "jeffsboard";
const char* password = "REPLACE WITH YOUR BIRTHDAY";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

// Create a WebSocket object
AsyncWebSocket ws("/ws");

// Json Variable to Hold Sensor Readings
JSONVar readings;



// Auxiliar variables to store the current output state
String output26State = "off";
const int output26 = 26;

struct sensorData {
  float vBatt;
  float vSolar;
  float aSolar;
} mySensorData;

#endif  // CONFIG_H

