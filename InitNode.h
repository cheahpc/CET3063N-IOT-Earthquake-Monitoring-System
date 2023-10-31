// -------------------------------------------------
// Node Option - Select which node to upload
// -------------------------------------------------
#define SENSOR
// #define PLATFORM

// -------------------------------------------------
// Wifi Option
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
// UDF
// -------------------------------------------------
#ifdef SENSOR
#ifdef FB_SET_METHOD_1
void getSensorJSON() {
  fbjson.clear();
#ifdef ENABLE_ACCEL
  fbjson.set(SENSOR_NODE_ACCEL_X_PATH, imu_GetAccel(1));
  fbjson.set(SENSOR_NODE_ACCEL_Y_PATH, imu_GetAccel(2));
  fbjson.set(SENSOR_NODE_ACCEL_Z_PATH, imu_GetAccel(3));
#endif
#ifdef ENABLE_GYRO
  fbjson.set(SENSOR_NODE_GYRO_X_PATH, imu_GetGyro(1));
  fbjson.set(SENSOR_NODE_GYRO_Y_PATH, imu_GetGyro(2));
  fbjson.set(SENSOR_NODE_GYRO_Z_PATH, imu_GetGyro(3));
#endif
#ifdef ENABLE_MAGNETO
  fbjson.set(SENSOR_NODE_MAG_X_PATH, imu_GetMag(1));
  fbjson.set(SENSOR_NODE_MAG_Y_PATH, imu_GetMag(2));
  fbjson.set(SENSOR_NODE_MAG_Z_PATH, imu_GetMag(3));
#endif
#ifdef ENABLE_TEMP
  fbjson.set(SENSOR_NODE_TEMP_PATH, imu_GetTemp());
#endif

#ifdef DEBUG_JSON
  fbjson.toString(Serial, true);
  Serial.println();
  Serial.println();
#endif
}
#endif

#ifdef FB_SET_METHOD_2
void setSensorData() {
#ifdef ENABLE_ACCEL
  fb_SetFloat(SENSOR_NODE_ACCEL_X_PATH, imu_GetAccel(1));
  delay(DELAY_TIME);
  fb_SetFloat(SENSOR_NODE_ACCEL_Y_PATH, imu_GetAccel(2));
  delay(DELAY_TIME);
  fb_SetFloat(SENSOR_NODE_ACCEL_Z_PATH, imu_GetAccel(3));
  delay(DELAY_TIME);
#endif
#ifdef ENABLE_GYRO
  fb_SetFloat(SENSOR_NODE_GYRO_X_PATH, imu_GetGyro(1));
  delay(DELAY_TIME);
  fb_SetFloat(SENSOR_NODE_GYRO_Y_PATH, imu_GetGyro(2));
  delay(DELAY_TIME);
  fb_SetFloat(SENSOR_NODE_GYRO_Z_PATH, imu_GetGyro(3));
  delay(DELAY_TIME);
#endif
#ifdef ENABLE_MAGNETO
  fb_SetFloat(SENSOR_NODE_MAG_X_PATH, imu_GetMag(1));
  delay(DELAY_TIME);
  fb_SetFloat(SENSOR_NODE_MAG_Y_PATH, imu_GetMag(2));
  delay(DELAY_TIME);
  fb_SetFloat(SENSOR_NODE_MAG_Z_PATH, imu_GetMag(3));
  delay(DELAY_TIME);
#endif
#ifdef ENABLE_TEMP
  fb_SetFloat(SENSOR_NODE_TEMP_PATH, imu_GetTemp());
  delay(DELAY_TIME);
#endif
  eSetVal(imu_GetAccel(1), imu_GetAccel(2), imu_GetAccel(3));
  fb_SetFloat(EARTHQUAKE_MAGNITUDE_PATH, eGetMagnitude());
  delay(DELAY_TIME);
  fb_SetInt(EARTHQUAKE_AMPLITUDE_PATH, eGetAmplitude());
  delay(DELAY_TIME);
}
#endif
#endif

void sendWiFiInfo() {
#ifdef SENSOR
  fb_SetString(SENSOR_NODE_WIFI_HOSTNAME_PATH,wifi_GetHostname());
  fb_SetString(SENSOR_NODE_WIFI_LOCAL_IP_PATH, wifi_GetLocalIP());
  fb_SetString(SENSOR_NODE_WIFI_SIGNAL_STRENGTH_PATH, wifi_GetSignalStrength());
#endif
#ifdef PLATFORM
  fb_SetString(ALARM_NODE_WIFI_HOSTNAME_PATH, wifi_GetHostname());
  fb_SetString(ALARM_NODE_WIFI_LOCAL_IP_PATH, wifi_GetLocalIP());
  fb_SetString(ALARM_NODE_WIFI_SIGNAL_STRENGTH_PATH, wifi_GetSignalStrength());
#endif
}
// -------------------------------------------------
// UDF End
// -------------------------------------------------


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
  sendWiFiInfo();  // Set wifi connection information into json

#ifdef PLATFORM
  // ------------------------------------------------ Server Init
  server.on("/", SendWebsite);
  server.on("/signal_0", handleSignal_0);
  server.on("/signal_1", handleSignal_1);
  server.on("/signal_2", handleSignal_2);
  server.on("/signal_3", handleSignal_3);
  server.on("/signal_4", handleSignal_4);
  server.on("/signal_5", handleSignal_5);
  server.on("/signal_6", handleSignal_6);
  server.on("/signal_7", handleSignal_7);

  // Start Server
  server.begin();
  // Add your web page to the server
  Serial.println("Web server started");
#endif
}
#pragma endregion setup_init

// -------------------------------------------------
// Init Node END
// -------------------------------------------------

// -------------------------------------------------
// Routine Program
// -------------------------------------------------
#ifdef SENSOR
unsigned long prevT_Amplitude = 0;
unsigned long prevT_Magnitude = 0;
unsigned long prevT_RTDB = 0;
unsigned long tTres_Amplitude_SampleRate = 5;
unsigned long tTres_Magnitude_SampleRate = 500;
unsigned long tTres_RTDB = 500;
float currentAmplitude = 0;
float maxAmplitude = 0;

void sensorRoutine() {
  // Sample amplitude change
  if ((millis() - prevT_Amplitude) >= tTres_Amplitude_SampleRate) {
    // Sample amplitude
    currentAmplitude = eGetAmplitude(imu_GetAccel(3));
    // Set new maximum amplitude
    maxAmplitude = max(maxAmplitude, currentAmplitude);

    prevT_Amplitude = millis();
  }

  // Set magnitude base on max amplitude
  if ((millis() - prevT_Magnitude) >= tTres_Magnitude_SampleRate) {
    // Update RTDB with new magnitude
    fb_SetFloat(EARTHQUAKE_MAGNITUDE_PATH, eGetMagnitude(maxAmplitude));
    fb_SetInt(EARTHQUAKE_LEVEL_PATH, eGetLevel());

    // Reset maximum amplitude
    maxAmplitude = 0;
    prevT_Magnitude = millis();
  }

  if ((millis() - prevT_RTDB) >= tTres_RTDB) {
    // Send Sensor data
    getSensorJSON();
    updateNodeAsync();
  }
}
#endif

#ifdef PLATFORM
void platformRoutine() {
  loopSignal();
  server.handleClient();
}
#endif