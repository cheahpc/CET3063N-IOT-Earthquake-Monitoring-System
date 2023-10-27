// Define which node to initialize
#define SENSOR
// #define ALARM

// Initialize all necessary library and values
#ifdef SENSOR
#include "Wire.h"
#include "I2C.h"
#include "MPU9250.h"
#endif

// -------------------------------------------------
// Init Node
// -------------------------------------------------
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
}