// -------------------------------------------------
// Node Option - Select which node to upload
// -------------------------------------------------
// #define SENSOR
#define PLATFORM

// -------------------------------------------------
// Wifi
// -------------------------------------------------
#define WSSID "PasswordIsPassword"
#define WPASSWORD "password"

#ifdef SENSOR
#define HOSTNAME "Sensor1"
#endif
#ifdef PLATFORM
#define HOSTNAME "Platform"
#endif


// -------------------------------------------------
// MPU9250 Option
// -------------------------------------------------
// Define debug to print respective value
// #define DEBUG_ACCEL  // Accelerator
// #define DEBUG_GYRO // Gyroscope
// #define DEBUG_MAGNETO  // Magnetometer
// #define DEBUG_TEMP // Temperature

// Define enable sensor
#define ENABLE_ACCEL
#define ENABLE_GYRO
#define ENABLE_MAGNETO
#define ENABLE_TEMP

// -------------------------------------------------
// MPU9250 Values
// -------------------------------------------------
#define ROUND_VALUE 2
#define INTERVAL_MS_PRINT 100

// -------------------------------------------------
// Firebase Option
// -------------------------------------------------
// #define ANONYMOUS
// #define FIREBASE_VERBOSE
#define DELAY_TIME 50

// -------------------------------------------------
// Firebase Value
// -------------------------------------------------
#ifndef ANONYMOUS
#define USER_EMAIL "estupido404@gmail.com"
#define USER_PASSWORD "Stupido@404"
#endif
#define API_KEY "AIzaSyCTZj09mjxN2LfGO_O2gbCziAixP8GOl4M"
#define DB_URL "https://earthquake-6db21-default-rtdb.asia-southeast1.firebasedatabase.app/"

#define SENSOR_NODE_ACCEL_X_PATH "Sensor/1/Accelerometer/X"
#define SENSOR_NODE_ACCEL_Y_PATH "Sensor/1/Accelerometer/Y"
#define SENSOR_NODE_ACCEL_Z_PATH "Sensor/1/Accelerometer/Z"
#define SENSOR_NODE_GYRO_X_PATH "Sensor/1/Gyroscope/X"
#define SENSOR_NODE_GYRO_Y_PATH "Sensor/1/Gyroscope/Y"
#define SENSOR_NODE_GYRO_Z_PATH "Sensor/1/Gyroscope/Z"
#define SENSOR_NODE_MAG_X_PATH "Sensor/1/Magnetometer/X"
#define SENSOR_NODE_MAG_Y_PATH "Sensor/1/Magnetometer/Y"
#define SENSOR_NODE_MAG_Z_PATH "Sensor/1/Magnetometer/Z"
#define SENSOR_NODE_TEMP_PATH "Sensor/1/Temperature/"

#define SENSOR_NODE_WIFI_HOSTNAME_PATH "Connection/Sensor 1/Hostname"
#define SENSOR_NODE_WIFI_LOCAL_IP_PATH "Connection/Sensor 1/Local IP"
#define SENSOR_NODE_WIFI_SIGNAL_STRENGTH_PATH "Connection/Sensor 1/Signal Strength"

#define ALARM_NODE_WIFI_HOSTNAME_PATH "Connection/Platform/Hostname"
#define ALARM_NODE_WIFI_LOCAL_IP_PATH "Connection/Platform/Local IP"
#define ALARM_NODE_WIFI_SIGNAL_STRENGTH_PATH "Connection/Platform/Signal Strength"

#define EARTHQUAKE_MAGNITUDE_PATH "Earthquake/Sensor 1/Magnitude"
#define EARTHQUAKE_LEVEL_PATH "Earthquake/Sensor 1/Level"

// -------------------------------------------------
// Eartquake option
// -------------------------------------------------
#define FORMULA_A
// #define FORMULA_B

// -------------------------------------------------
// Signal Value
// -------------------------------------------------
#define signalPin D0

// -------------------------------------------------
// Include Library
// -------------------------------------------------
#include "Wifi.h"
#include "Firebase.h"
#include "Earthquake.h"
#ifdef SENSOR
#include "MPU9250.h"
#endif
#ifdef PLATFORM
#include "Server.h"
#include "Signal.h"
#endif

// -------------------------------------------------
// Init Node
// -------------------------------------------------
#pragma region setup_init
void initNode() {
  // Begin serial
  Serial.begin(115200);

// ------------------------------------------------ MPU9250 Init
#ifdef SENSOR
  initMPU9250();
#endif
// ------------------------------------------------ Signal Init
#ifdef PLATFORM
  initSignal();
#endif

  // ------------------------------------------------ Wifi Init
  initWifi();

  // ------------------------------------------------ Firebase Init
  initFirebase();
  // Send Connection detail
#ifdef SENSOR
  fb_SetString(SENSOR_NODE_WIFI_HOSTNAME_PATH, wifi_GetHostname());
  delay(DELAY_TIME);
  fb_SetString(SENSOR_NODE_WIFI_LOCAL_IP_PATH, wifi_GetLocalIP());
  delay(DELAY_TIME);
  fb_SetString(SENSOR_NODE_WIFI_SIGNAL_STRENGTH_PATH, wifi_GetSignalStrength());
  delay(DELAY_TIME);
#endif
#ifdef PLATFORM
  fb_SetString(ALARM_NODE_WIFI_HOSTNAME_PATH, wifi_GetHostname());
  delay(DELAY_TIME);
  fb_SetString(ALARM_NODE_WIFI_LOCAL_IP_PATH, wifi_GetLocalIP());
  delay(DELAY_TIME);
  fb_SetString(ALARM_NODE_WIFI_SIGNAL_STRENGTH_PATH, wifi_GetSignalStrength());
  delay(DELAY_TIME);

  // ------------------------------------------------ Server Init
  server.on("/", SendWebsite);
  server.on("/signal_0", handleSignal_0);
  server.on("/signal_1", handleSignal_1);
  server.on("/signal_2", handleSignal_2);
  server.on("/signal_3", handleSignal_3);
  server.on("/signal_4", handleSignal_4);
  server.on("/signal_5", handleSignal_5);

  // Start Server
  server.begin();
  // Add your web page to the server
  Serial.println("Web server started");
#endif
}
#pragma endregion setup_init
