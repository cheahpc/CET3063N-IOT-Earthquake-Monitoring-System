#include "InitNode.h"

void setup() {
  // Start Everything
  initNode();
}

void loop() {
// aWriteVibrator(200);
// delay(5000);
// aWriteVibrator(255);
// delay(5000);
#ifdef SENSOR
  getSensorJSON();
  updateRTDB();
  delay(DELAY_TIME);
#endif

#ifdef PLATFORM
  server.handleClient();
#endif
}
