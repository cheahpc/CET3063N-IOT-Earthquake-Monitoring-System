// Define which node to initialize
// #define SENSOR
#define ALARM

// Firebase
// #define ANONYMOUS
// #define FIREBASE_VERBOSE

#define DELAY_TIME 0

#ifdef SENSOR
#include "MPU9250.h"
#endif
#ifdef ALARM
#include "Vibrator.h"
#endif

#include "Wifi.h"
#include "Firebase.h"
#include "Earthquake.h"

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
// ------------------------------------------------ ALARM Init
#ifdef ALARM
  initVibrator();
// TODO Initialize Alarm Node
// Initialize Alarm node
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
#ifdef ALARM
  fb_SetString(ALARM_NODE_WIFI_HOSTNAME_PATH, wifi_GetHostname());
  delay(DELAY_TIME);
  fb_SetString(ALARM_NODE_WIFI_LOCAL_IP_PATH, wifi_GetLocalIP());
  delay(DELAY_TIME);
  fb_SetString(ALARM_NODE_WIFI_SIGNAL_STRENGTH_PATH, wifi_GetSignalStrength());
  delay(DELAY_TIME);
#endif
}
#pragma endregion setup_init