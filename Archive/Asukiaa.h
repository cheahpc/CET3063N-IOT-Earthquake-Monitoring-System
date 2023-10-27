#include <MPU9250_asukiaaa.h>

#ifdef _ESP32_HAL_I2C_H_
#define SDA_PIN 21
#define SCL_PIN 22
#endif

MPU9250_asukiaaa mySensor;
float aX, aY, aZ, aSqrt, gX, gY, gZ, mDirection, mX, mY, mZ;

void setup() {
  Serial.begin(115200);
  while (!Serial)
    ;
  Serial.println("started");

#ifdef _ESP32_HAL_I2C_H_  // For ESP32
  Wire.begin(SDA_PIN, SCL_PIN);
  mySensor.setWire(&Wire);
#endif

  mySensor.beginAccel();
  mySensor.beginGyro();
  mySensor.beginMag();

  // You can set your own offset for mag values
  // mySensor.magXOffset = -50;
  // mySensor.magYOffset = -55;
  // mySensor.magZOffset = -10;
}

void loop() {
  uint8_t sensorId;
  int result;

  result = mySensor.accelUpdate();
  if (result == 0) {
    aX = mySensor.accelX();
    aY = mySensor.accelY();
    aZ = mySensor.accelZ();
    aSqrt = mySensor.accelSqrt();
    Serial.print(aX, 1);
    Serial.print("\t\t");
    Serial.print(aY, 1);
    Serial.print("\t\t");
    Serial.print(aZ, 1);
    Serial.print("\t\t");
    Serial.println(aSqrt,1);
  } else {
    Serial.println("Cannod read accel values " + String(result));
  }

  // result = mySensor.gyroUpdate();
  // if (result == 0) {
  //   gX = mySensor.gyroX();
  //   gY = mySensor.gyroY();
  //   gZ = mySensor.gyroZ();
  //   Serial.println("gyroX: " + String(gX));
  //   Serial.println("gyroY: " + String(gY));
  //   Serial.println("gyroZ: " + String(gZ));
  // } else {
  //   Serial.println("Cannot read gyro values " + String(result));
  // }

}