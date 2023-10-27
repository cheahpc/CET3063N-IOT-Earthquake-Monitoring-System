// Define debug to print respective value
#define debugA  // Accelerator
// #define debugG // Gyroscope
#define debugM  // Magnetometer
// #define debugT // Temperature

// Define enable sensor
#define ENABLE_ACCEL
// #define ENABLE_GYRO
// #define ENABLE_MAGNETO
// #define ENABLE_TEMP

// -------------------------------------------------
// Define value
// -------------------------------------------------

#define INTERVAL_MS_PRINT 100

#define G 9.80665


struct {
  struct {
    float x, y, z;
  } accelerometer, gyroscope, magnetometer;

  float temperature;
} normalized;

unsigned long lastPrintMillis = 0;
unsigned long lastSampleMicros = 0;


// -------------------------------------------------
// Accelerometer
// -------------------------------------------------
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
  normalized.accelerometer.x = accelerometer.x * G / 16384;
  normalized.accelerometer.y = accelerometer.y * G / 16384;
  normalized.accelerometer.z = accelerometer.z * G / 16384;
}
#endif

// -------------------------------------------------
// Gyroscope
// -------------------------------------------------
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
#endif

// -------------------------------------------------
// Magnetometer
// -------------------------------------------------
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
#endif

// -------------------------------------------------
// Temperature
// -------------------------------------------------
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
#endif

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
void updateIMU() {
}