#include "InitNode.h"

int status;

void setup() {
  // Initialize sensor, wifi, etc
  initNode();
}

void loop() {
  // check if the server is established
  if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 1000 || sendDataPrevMillis == 0)) {
    sendDataPrevMillis = millis();

    if (Firebase.RTDB.setFloat(&fbdo, "Sensor/accel", getAccel(1))) {
      Serial.println();
      Serial.println(getAccel(1));
      Serial.print(" - successfully saved to: " + fbdo.dataPath());
      Serial.println(" (" + fbdo.dataType() + ")");

    } else {
      Serial.println("FAILED: " + fbdo.errorReason());
    };
  }
}
