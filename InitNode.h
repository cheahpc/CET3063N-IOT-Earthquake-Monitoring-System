// Define which node to initialize
#define SENSOR
// #define ALARM

// Initialize all necessary library and values
#include <ESP8266WiFi.h>
#ifdef SENSOR
#include "Wire.h"
#include "I2C.h"
#include "MPU9250.h"
#endif

// -------------------------------------------------
// Wifi Value
// -------------------------------------------------
const char* ssid = "earth";
const char* password = "12345678";
WiFiServer server(80);

// -------------------------------------------------
// Init Node
// -------------------------------------------------
#pragma region setup_init
void initNode() {
  // Begin serial
  Serial.begin(115200);

#ifdef SENSOR
  // Initialize Sensor node
  // Begin Wire
  Wire.begin();
// MPU9250 Init
#ifdef ENABLE_ACCEL
  I2CwriteByte(0x68, 28, ACC_FULL_SCALE_2G);  // Configure accelerometer range
#endif

#ifdef ENABLE_GYRO
  I2CwriteByte(0x68, 27, GYRO_FULL_SCALE_1000_DPS);  // Configure gyroscope range
#endif

#ifdef ENABLE_MAGNETO
  I2CwriteByte(0x68, 55, 0x02);  // Set by pass mode for the magnetometers
  initMagnetometer();
  I2CwriteByte(0x68, 56, 0x01);  // Enable interrupt pin for raw data
#endif

#endif

#ifdef ALARM
  // Initialize Alarm node

#endif
  // Wifi Init
  // Connect to wifi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  server.begin();
  Serial.println();
  Serial.println("Server started at port 80.");
  Serial.println("Controller has connected to WLAN");
  // Print some message
  Serial.print("URL=http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}
#pragma endregion setup_init