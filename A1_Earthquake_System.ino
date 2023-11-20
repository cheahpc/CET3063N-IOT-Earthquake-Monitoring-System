#include "InitNode.h"

void setup() {
  // Initialize server, wifi, firebase etc
  initNode();
}

void loop() {
#ifdef SENSOR
  // Run program for sensor
  sensorRoutine();
#endif

#ifdef PLATFORM
  // Run program for platform
  platformRoutine();
#endif
}
