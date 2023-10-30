#include "InitNode.h"

void setup() {
  // Start Everything
  initNode();
}

void loop() {
// aWriteVibrator(200);
// delay(5000);
// aWriteVibrator(255);
// delay(5000);
#ifdef SENSOR
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
  fb_SetFloat(EARTHQUAKE_MAGNITUDE_PATH, e_GetRitcherMagnitude(imu_GetAccel(1), imu_GetAccel(2), imu_GetAccel(3)));
  delay(DELAY_TIME);
  fb_SetInt(EARTHQUAKE_LEVEL_PATH, e_GetLevel());
  delay(DELAY_TIME);
#endif

#ifdef PLATFORM
  Server.handleClient();
#endif
}