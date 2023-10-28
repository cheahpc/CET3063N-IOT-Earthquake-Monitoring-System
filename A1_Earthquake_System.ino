#include "InitNode.h"

int status;

void setup() {
  // Initialize Sensor, Wifi, Firebase
  initNode();
}

void loop() {
#ifdef SENSOR
  fb_SetFloat(SENSOR_NODE_ACCEL_X_PATH, imu_GetAccel(1));
  delay(DELAY_TIME);
  fb_SetFloat(SENSOR_NODE_ACCEL_Y_PATH, imu_GetAccel(2));
  delay(DELAY_TIME);
  fb_SetFloat(SENSOR_NODE_ACCEL_Z_PATH, imu_GetAccel(3));
  delay(DELAY_TIME);
  fb_SetFloat(SENSOR_NODE_GYRO_X_PATH, imu_GetGyro(1));
  delay(DELAY_TIME);
  fb_SetFloat(SENSOR_NODE_GYRO_Y_PATH, imu_GetGyro(2));
  delay(DELAY_TIME);
  fb_SetFloat(SENSOR_NODE_GYRO_Z_PATH, imu_GetGyro(3));
  delay(DELAY_TIME);
  fb_SetFloat(SENSOR_NODE_MAG_X_PATH, imu_GetMag(1));
  delay(DELAY_TIME);
  fb_SetFloat(SENSOR_NODE_MAG_Y_PATH, imu_GetMag(2));
  delay(DELAY_TIME);
  fb_SetFloat(SENSOR_NODE_MAG_Z_PATH, imu_GetMag(3));
  delay(DELAY_TIME);
  fb_SetFloat(SENSOR_NODE_TEMP_PATH, imu_GetTemp());
  delay(DELAY_TIME);
  fb_SetFloat(EARTHQUAKE_MAGNITUDE_PATH, e_GetEarthquakeMagnitude((1), imu_GetAccel(2), imu_GetAccel(3)));
  delay(DELAY_TIME);
  fb_SetInt(EARTHQUAKE_LEVEL_PATH, e_GetEarthquakeLevel(imu_GetAccel(1), imu_GetAccel(2), imu_GetAccel(3)));
  delay(DELAY_TIME);
#endif

#ifdef ALARM
  setHostname(getHostname());
  server.handleClient();
#endif
}
