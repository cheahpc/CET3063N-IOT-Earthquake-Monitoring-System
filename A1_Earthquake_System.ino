#include "InitNode.h"

void setup() {
  // Initialize sensor, wifi, etc
  initNode();
}

void loop() {
  unsigned long currentMillis = millis();

  if (isImuReady()) {
    readRawAccel();
    //normalize(gyroscope);
    normalize(accelerometer);
    //normalize(temperature);
  }

  // if (isMagnetometerReady()) {
  //   readRawMagnetometer();
  //   normalize(magnetometer);
  // }

  if (currentMillis - lastPrintMillis > INTERVAL_MS_PRINT) {
    // Serial.print("TEMP:\t");
    // Serial.print(normalized.temperature, 2);
    // Serial.print("\xC2\xB0"); //Print degree symbol
    // Serial.print("C");
    // Serial.println();

    // Serial.print("GYR (");
    // Serial.print("\xC2\xB0"); //Print degree symbol
    // Serial.print("/s):\t");
    // Serial.print(normalized.gyroscope.x, 1);
    // Serial.print("\t\t");
    // Serial.print(normalized.gyroscope.y, 1);
    // Serial.print("\t\t");
    // Serial.print(normalized.gyroscope.z, 1);
    // Serial.println();

    Serial.print("Accel (m/s^2):\t");
    Serial.print("X:");
    Serial.print(normalized.accelerometer.x, 1);
    Serial.print("\t");
    Serial.print("Y:");
    Serial.print(normalized.accelerometer.y, 1);
    Serial.print("\t");
    Serial.print("Z:");
    Serial.print(normalized.accelerometer.z, 1);
    Serial.println();

    // Serial.print("MAG (");
    // Serial.print("\xce\xbc"); //Print micro symbol
    // Serial.print("T):\t");
    // Serial.print(normalized.magnetometer.x, 1);
    // Serial.print("\t\t");
    // Serial.print(normalized.magnetometer.y, 1);
    // Serial.print("\t\t");
    // Serial.print(normalized.magnetometer.z, 1);
    // Serial.println();

    lastPrintMillis = currentMillis;
  }
}
