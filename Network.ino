#include "config.h"

// Get Sensor Readings and return JSON object
String getSensorReadings() {

  return JSON.stringify(readings);
}

// Initialize LittleFS
void initLittleFS() {
if (!LittleFS.begin(true)) {
  Serial.println("Failed to mount LittleFS!");
} else {
  Serial.println("LittleFS mounted.");
  File root = LittleFS.open("/");
  File file = root.openNextFile();
  while (file) {
    Serial.print("Found file: ");
    Serial.println(file.name());
    file = root.openNextFile();
  }
}
}

// Notify all WebSocket clients with sensor readings
void notifyClients(String sensorReadings) {
  ws.textAll(sensorReadings);
}
String getGPIOStates() {
  readings["solarRailState"] = solarRailState;
  return JSON.stringify(readings);
}

void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
  AwsFrameInfo *info = (AwsFrameInfo*)arg;
  if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
    // Create a properly null-terminated string from received data
    char message[len + 1]; // Add space for the null terminator
    memcpy(message, data, len);
    message[len] = '\0'; // Null-terminate the string

    Serial.println(message); // Print the clean message for debugging

    // Check if "toggle26" is part of the message
    if (strstr(message, "toggleNine") != NULL) {
      nineVRailState = (nineVRailState == "off") ? "on" : "off";
      digitalWrite(sw_nine, (nineVRailState == "on") ? HIGH : LOW);
      notifyClients(getGPIOStates());
    }

    // Handle other messages, like "getReadings"
    else if (strstr(message, "getReadings") != NULL) {
      notifyClients(getSensorReadings());
    }
  }
}



// WebSocket event handler
void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {
  switch (type) {
    case WS_EVT_CONNECT:
      Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
      break;
    case WS_EVT_DISCONNECT:
      Serial.printf("WebSocket client #%u disconnected\n", client->id());
      break;
    case WS_EVT_DATA:
      handleWebSocketMessage(arg, data, len);
      break;
    case WS_EVT_PONG:
    case WS_EVT_ERROR:
      break;
  }
}

// Initialize WebSocket
void initWebSocket() {
  ws.onEvent(onEvent);
  server.addHandler(&ws);
}

// Initialize WiFi as a Soft Access Point
void initWiFi() {
  WiFi.softAP(ssid, password); // With password
  IPAddress IP = WiFi.softAPIP(); // Get the IP address of the AP
  Serial.print("Access Point IP address: ");
  Serial.println(IP);
}



void wifiSetup() { 
 // Initialize components
  initLittleFS();
  initWebSocket();
  initWiFi();

  // Serve HTML file from LittleFS
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    if (LittleFS.exists("/index.html")) {
      request->send(LittleFS, "/index.html", "text/html");
    } else {
      Serial.println("Nothing found fool");
      request->send(500, "text/plain", "File not found, contact Workshop leader");
    }
  });

  // Serve static files (CSS, JS, etc.) from LittleFS
  server.serveStatic("/", LittleFS, "/");

  // Start the server
  server.begin();

  // Configure the LED 
  pinMode(sw_solar, OUTPUT);
  digitalWrite(sw_solar, HIGH);
}




void printIP(){ 
  IPAddress IP = WiFi.softAPIP(); // Get the IP address of the AP
  Serial.print("Access Point IP address: ");
  Serial.println(IP);

}