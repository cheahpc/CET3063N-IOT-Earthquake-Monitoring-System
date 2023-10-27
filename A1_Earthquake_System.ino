#include "InitNode.h"

unsigned long currentMillis = millis();
void setup() {
  // Initialize sensor, wifi, etc
  initNode();
  
}

void loop() {

  if (millis() - currentMillis > 1000) {
    getAccel();
    // getGyro();
    // getMag();
    // getTemp();

    currentMillis = millis();
  }
}
