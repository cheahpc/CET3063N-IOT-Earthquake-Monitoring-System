// Define which node to initialize
// #define SENSOR
#define ALARM

#ifdef SENSOR
#include "MPU9250.h"
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

#ifdef ALARM
// TODO Initialize Alarm Node
// Initialize Alarm node
#endif

  // ------------------------------------------------ Wifi Init
  initWifi();

  // ------------------------------------------------ Firebase Init
  initFirebase();
}
#pragma endregion setup_init