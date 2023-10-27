#include "InitNode.h"

int status;

void setup() {
  // Initialize Sensor, Wifi, Firebase
  initNode();
}

void loop() {
  sendAccelData();
  sendEarthquakeMagnitude(getEarthquakeMagnitude());
  setEarthquakeLevel(getEarthquakeLevel());
  delay(200);
}
