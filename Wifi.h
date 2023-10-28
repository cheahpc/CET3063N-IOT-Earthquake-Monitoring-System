// Initialize all necessary library and values
#include <ESP8266WiFi.h>
#ifdef ALARM
// #include "WiFiClient.h"
// #include "WebServer.h"
#include "webpage.h"
#endif
// -------------------------------------------------
// Wifi
// -------------------------------------------------
#define SSID "PasswordIsPassword"
#define PASSWORD "password"
#ifdef SENSOR
#define HOSTNAME "SENSOR_NODE"
#endif
#ifdef ALARM
#define HOSTNAME "ALARM_NODE"
// Create a web server object
ESP8266WebServer server(80);  //Server on port 80
#endif

WiFiClient client;
void initWifi() {
  //Set new hostname
  WiFi.hostname(HOSTNAME);

  // Connect to Wifi
  WiFi.begin(SSID, PASSWORD);
  Serial.println("Connecting to Wi-Fi");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }

#ifdef ALARM
  // Start Server
  server.begin();
  Serial.println("Web server started");

  // Add your web page to the server
  server.on("/", []() {
    server.sendContent(MAIN_page);
  });
#endif
}

String wifi_GetLocalIP() {
  return String(WiFi.localIP().toString().c_str());
}

String wifi_GetHostname() {
  return String(WiFi.hostname().c_str());
}

String wifi_GetSignalStrength() {
  return String(WiFi.RSSI());
}


// TODO send html page to client with information.