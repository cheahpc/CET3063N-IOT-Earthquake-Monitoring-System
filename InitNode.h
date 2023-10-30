// -------------------------------------------------
// Node Option - Select which node to upload
// -------------------------------------------------
#define SENSOR
// #define PLATFORM

// -------------------------------------------------
// Firebase Option
// -------------------------------------------------
// #define ANONYMOUS
// #define FIREBASE_VERBOSE

#define DELAY_TIME 50

#include "Wifi.h"
#include "Firebase.h"
#include "Earthquake.h"
#ifdef SENSOR
#include "MPU9250.h"
#endif
#ifdef PLATFORM
#include "Vibrator.h"
#include "Server.h"
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
// ------------------------------------------------ Vibrator Init
#ifdef PLATFORM
  initVibrator();
// TODO Initialize Alarm Node
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
  server.on("/btnMute", handleBtnMute);

  // Start Server
  server.begin();
  // Add your web page to the server
  Serial.println("Web server started");
#endif
}
#pragma endregion setup_init