// -------------------------------------------------
// Copyright (c) 2022 HiBit <https://www.hibit.dev>
// -------------------------------------------------

#include "Arduino.h"
#include "Wire.h"

#ifndef I2C_h
#define I2C_h

// This function read n bytes (bytes) from I2C device at address (address).
// Put read bytes starting at register (register) in an array (data).
void I2Cread(uint8_t address, uint8_t reg, uint8_t bytes, uint8_t* data);

// Write a byte (data) in device (address) at register (reg)
void I2CwriteByte(uint8_t address, uint8_t reg, uint8_t data);

#endif


void I2Cread(uint8_t address, uint8_t reg, uint8_t bytes, uint8_t* data) {
  Wire.beginTransmission(address);  // Set register address
  Wire.write(reg);
  Wire.endTransmission();

  Wire.requestFrom(address, bytes);  //Read bytes amount

  uint8_t index = 0;
  while (Wire.available()) {
    data[index++] = Wire.read();
  }
}

void I2CwriteByte(uint8_t address, uint8_t reg, uint8_t data) {
  Wire.beginTransmission(address);  //Set register address
  Wire.write(reg);
  Wire.write(data);
  Wire.endTransmission();
}
