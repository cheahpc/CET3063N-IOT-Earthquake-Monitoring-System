#include "InitNode.h"

void setup() {
  // Start Everything
  initNode();
}
void loop() {

#ifdef SENSOR
  // Run program for sensor
  sensorRoutine();
#endif

#ifdef PLATFORM
  // Run program for platform]
  platformRoutine();
#endif
}
