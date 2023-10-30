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
  server.handleClient();
}