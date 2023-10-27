
// Initialize all necessary library and values
#include <ESP8266WiFi.h>

// -------------------------------------------------
// Wifi
// -------------------------------------------------
#define SSID "PasswordIsPassword"
#define PASSWORD "password"
void initWifi() {
  // Connect to Wifi
  WiFi.begin(SSID, PASSWORD);
  Serial.println("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println("");
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
}
