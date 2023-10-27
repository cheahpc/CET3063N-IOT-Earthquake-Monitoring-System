#include "Wire.h"
#include "I2C.h"
// -------------------------------------------------
// Usage - Function
// -------------------------------------------------
// getAccel();
// getGyro();
// getMag();
// getTemp();

// Define debug to print respective value
// #define DEBUG_ACCEL  // Accelerator
// #define DEBUG_GYRO // Gyroscope
// #define DEBUG_MAGNETO  // Magnetometer
// #define DEBUG_TEMP // Temperature

// Define enable sensor
#define ENABLE_ACCEL
// #define ENABLE_GYRO
// #define ENABLE_MAGNETO
// #define ENABLE_TEMP

// -------------------------------------------------
// Glbal value
// -------------------------------------------------
#define ROUND_VALUE 2
#define INTERVAL_MS_PRINT 100


struct {
  struct {
    float x, y, z;
  } accelerometer, gyroscope, magnetometer;

  float temperature;
} normalized;

// -------------------------------------------------
// Function
// -------------------------------------------------
bool isImuReady() {
  uint8_t isReady;  // Interruption flag
  I2Cread(0x68, 58, 1, &isReady);
  return isReady & 0x01;  // Read register and wait for the RAW_DATA_RDY_INT
}

bool isMagnetometerReady() {
  uint8_t isReady;  // Interruption flag
  I2Cread(0x0C, 0x02, 1, &isReady);
  return isReady & 0x01;  // Read register and wait for the DRDY
}

// -------------------------------------------------
// Accelerometer
// -------------------------------------------------
#pragma region Accel
#ifdef ENABLE_ACCEL
#define ACC_FULL_SCALE_2G 0x00
#define ACC_FULL_SCALE_4G 0x08
#define ACC_FULL_SCALE_8G 0x10
#define ACC_FULL_SCALE_16G 0x18

struct accelerometer_raw {
  int16_t x, y, z;
} accelerometer;

void readRawAccel() {
  uint8_t buff[6];

  // Read output registers:
  // [59-64] Accelerometer
  I2Cread(0x68, 59, 6, buff);

  // Accelerometer, create 16 bits values from 8 bits data
  accelerometer.x = (buff[0] << 8 | buff[1]);
  accelerometer.y = (buff[2] << 8 | buff[3]);
  accelerometer.z = (buff[4] << 8 | buff[5]);
}

void normalize(accelerometer_raw accelerometer) {
  // Sensitivity Scale Factor (MPU datasheet page 9)
  normalized.accelerometer.x = accelerometer.x * 9.80665 / 16384;
  normalized.accelerometer.y = accelerometer.y * 9.80665 / 16384;
  normalized.accelerometer.z = accelerometer.z * 9.80665 / 16384;
}

float getAccel(int index = 0) {
  if (isImuReady()) {
    readRawAccel();
    normalize(accelerometer);
  }

  switch (index) {
    case 1:
      return normalized.accelerometer.x;
      break;
    case 2:
      return normalized.accelerometer.y;
      break;
    case 3:
      return normalized.accelerometer.z;
      break;
    default:
#ifdef DEBUG_ACCEL
      Serial.print("Accel:\t");
      Serial.print("X:");
      Serial.print(normalized.accelerometer.x, ROUND_VALUE);
      Serial.print("\t");
      Serial.print("Y:");
      Serial.print(normalized.accelerometer.y, ROUND_VALUE);
      Serial.print("\t");
      Serial.print("Z:");
      Serial.print(normalized.accelerometer.z, ROUND_VALUE);
      Serial.println();
#endif
      return 0.0;
  }
}
#endif
#pragma endregion Accel

// -------------------------------------------------
// Gyroscope
// -------------------------------------------------
#pragma region Gyro
#ifdef ENABLE_GYRO
#define GYRO_FULL_SCALE_250_DPS 0x00
#define GYRO_FULL_SCALE_500_DPS 0x08
#define GYRO_FULL_SCALE_1000_DPS 0x10
#define GYRO_FULL_SCALE_2000_DPS 0x18

struct gyroscope_raw {
  int16_t x, y, z;
} gyroscope;

void readRawGyro() {
  uint8_t buff[6];

  // Read output registers:
  // [67-72] Gyroscope
  I2Cread(0x68, 67, 6, buff);

  // Gyroscope, create 16 bits values from 8 bits data
  gyroscope.x = (buff[0] << 8 | buff[1]);
  gyroscope.y = (buff[2] << 8 | buff[3]);
  gyroscope.z = (buff[4] << 8 | buff[5]);
}

void normalize(gyroscope_raw gyroscope) {
  // Sensitivity Scale Factor (MPU datasheet page 8)
  normalized.gyroscope.x = gyroscope.x / 32.8;
  normalized.gyroscope.y = gyroscope.y / 32.8;
  normalized.gyroscope.z = gyroscope.z / 32.8;
}

float getGyro(int index = 0) {
  if (isImuReady()) {
    readRawGyro();
    normalize(gyroscope);
  }

  switch (index) {
    case 1:
      return normalized.gyroscope.x;
      break;
    case 2:
      return normalized.gyroscope.y;
      break;
    case 3:
      return normalized.gyroscope.z;
      break;
    default:
#ifdef DEBUG_GYRO
      Serial.print("Gyro:\t");
      Serial.print("X:");
      Serial.print(normalized.gyroscope.x, ROUND_VALUE);
      Serial.print("\t");
      Serial.print("Y:");
      Serial.print(normalized.gyroscope.y, ROUND_VALUE);
      Serial.print("\t");
      Serial.print("Z:");
      Serial.print(normalized.gyroscope.z, ROUND_VALUE);
      Serial.println();
#endif
      return 0.0;
  }
}
#endif
#pragma endregion Gyro

// -------------------------------------------------
// Magnetometer
// -------------------------------------------------
#pragma region Magneto
#ifdef ENABLE_MAGNETO
struct magnetometer_raw {
  int16_t x, y, z;

  struct {
    int8_t x, y, z;
  } adjustment;
} magnetometer;

void initMagnetometer() {
  uint8_t buff[3];

  I2CwriteByte(0x0C, 0x0A, 0x1F);  // Set 16-bits output & fuse ROM access mode

  delay(1000);

  I2Cread(0x0C, 0x10, 3, buff);  // Read adjustments

  magnetometer.adjustment.x = buff[0];  //Adjustment for X axis
  magnetometer.adjustment.y = buff[1];  //Adjustment for Y axis
  magnetometer.adjustment.z = buff[2];  //Adjustment for Z axis

  I2CwriteByte(0x0C, 0x0A, 0x10);  // Power down
}

void readRawMagnetometer() {
  uint8_t buff[7];

  // Read output registers:
  // [0x03-0x04] X-axis measurement
  // [0x05-0x06] Y-axis measurement
  // [0x07-0x08] Z-axis measurement
  I2Cread(0x0C, 0x03, 7, buff);

  // Magnetometer, create 16 bits values from 8 bits data
  magnetometer.x = (buff[1] << 8 | buff[0]);
  magnetometer.y = (buff[3] << 8 | buff[2]);
  magnetometer.z = (buff[5] << 8 | buff[4]);
}

void normalize(magnetometer_raw magnetometer) {
  // Sensitivity Scale Factor (MPU datasheet page 10)
  // 0.6 µT/LSB (14-bit)
  // 0.15µT/LSB (16-bit)
  // Adjustment values (MPU register page 53)
  normalized.magnetometer.x = magnetometer.x * 0.15 * (((magnetometer.adjustment.x - 128) / 256) + 1);
  normalized.magnetometer.y = magnetometer.y * 0.15 * (((magnetometer.adjustment.y - 128) / 256) + 1);
  normalized.magnetometer.z = magnetometer.z * 0.15 * (((magnetometer.adjustment.z - 128) / 256) + 1);
}

float getMag(int index = 0) {
  if (isMagnetometerReady()) {
    readRawMagnetometer();
    normalize(magnetometer);
  }

  switch (index) {
    case 1:
      return normalized.magnetometer.x;
      break;
    case 2:
      return normalized.magnetometer.y;
      break;
    case 3:
      return normalized.magnetometer.z;
      break;
    default:
#ifdef DEBUG_GYRO
      Serial.print("Mag:\t");
      Serial.print("X:");
      Serial.print(normalized.magnetometer.x, ROUND_VALUE);
      Serial.print("\t");
      Serial.print("Y:");
      Serial.print(normalized.magnetometer.y, ROUND_VALUE);
      Serial.print("\t");
      Serial.print("Z:");
      Serial.print(normalized.magnetometer.z, ROUND_VALUE);
      Serial.println();
#endif
      return 0.0;
  }
}
#endif
#pragma endregion Magneto

// -------------------------------------------------
// Temperature
// -------------------------------------------------
#pragma region Temp
#ifdef ENABLE_TEMP
#define TEMPERATURE_OFFSET 21  // As defined in documentation

struct temperature_raw {
  int16_t value;
} temperature;

void readRawTemp() {
  uint8_t buff[2];

  // Read output registers:
  // [65-66] Temperature
  I2Cread(0x68, 65, 2, buff);

  // Temperature, create 16 bits values from 8 bits data
  temperature.value = (buff[0] << 8 | buff[1]);
}

void normalize(temperature_raw temperature) {
  // Sensitivity Scale Factor (MPU datasheet page 11) & formula (MPU registers page 33)
  normalized.temperature = ((temperature.value - TEMPERATURE_OFFSET) / 333.87) + TEMPERATURE_OFFSET;
}

float getTemp(int index = 0) {
  if (isImuReady()) {
    readRawAccel();
    normalize(temperature);
  }

  switch (index) {
    case 1:
      return normalized.temperature.x;
      break;
    default:
#ifdef DEBUG_ACCEL
      Serial.print("Temp:\t");
      Serial.print("X:");
      Serial.print(normalized.temperature.x, ROUND_VALUE);
      Serial.println();
#endif
      return 0.0;
  }
}
#endif
#pragma endregion Temp

#pragma region Init
void initMPU9250() {
  // Initialize Sensor node
  // Begin Wire
  Wire.begin();
// ------------------------------------------------ MPU9250 Init
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
}
#pragma endregion Init
