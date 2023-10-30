// Initialize all necessary library and values
#include <ESP8266WiFi.h>
#ifdef PLATFORM
// #include "WiFiClient.h"
// #include "WebServer.h"
#include <ESP8266WebServer.h>
#include "webpage.h"
ESP8266WebServer server(80);  //Server on port 80
#endif

void initWifi() {
  //Set new hostname
  WiFi.hostname(HOSTNAME);

  // Connect to Wifi
  WiFi.begin(WSSID, WPASSWORD);
  Serial.println("Connecting to Wi-Fi");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
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
