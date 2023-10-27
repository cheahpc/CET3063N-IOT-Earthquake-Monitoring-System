#include <Firebase_ESP_Client.h>
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

// -------------------------------------------------
// Firebase
// -------------------------------------------------
#define USER_EMAIL "estupido404@gmail.com"
#define USER_PASSWORD "Stupido@404"
#define API_KEY "AIzaSyCTZj09mjxN2LfGO_O2gbCziAixP8GOl4M"
#define DB_URL "https://earthquake-6db21-default-rtdb.asia-southeast1.firebasedatabase.app/"
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig fbconfig;
bool signupOK = false;

void initFirebase() {
  // Firebase signin
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;
  fbconfig.api_key = API_KEY;
  fbconfig.database_url = DB_URL;

#ifdef ANONYMOUS
  // Anonymous Signup
  if (Firebase.signUp(&fbconfig, &auth, "", "")) {
    Serial.print("signUP OK");
    signupOK = true;
  } else {
    Serial.printf("%s\n", fbconfig.signer.signupError.message.c_str());
  };
#endif
  fbconfig.token_status_callback = tokenStatusCallback;
  Firebase.reconnectWiFi(true);
  fbdo.setBSSLBufferSize(4096, 1024);
  fbdo.setResponseSize(4096);
  Firebase.begin(&fbconfig, &auth);
}

void sendAccelData() {
  // check if the server is established
  if (Firebase.ready()) {
    String dataPath = "";
    for (size_t i = 1; i <= 3; i++) {
      // Change data path for XYZ
      switch (i) {
        case 1:
          dataPath = "Sensor/Accelerometer X";
          break;

        case 2:
          dataPath = "Sensor/Accelerometer Y";
          break;

        case 3:
          dataPath = "Sensor/Accelerometer Z";
          break;

        default:
          dataPath = "";
          break;
      }
      // Store data to respective datapath
      if (Firebase.RTDB.setFloat(&fbdo, dataPath, getAccel(i))) {
        Serial.println();
        Serial.print(getAccel(1));
        Serial.print(" - successfully saved to: " + fbdo.dataPath());
        Serial.println(" (" + fbdo.dataType() + ")");
      } else {
        Serial.println("FAILED: " + fbdo.errorReason());
      };
    }
  }
}
void sendEarthquakeMagnitude(float magnitude) {
  // check if the server is established
  if (Firebase.ready()) {
    // Store data to respective datapath
    if (Firebase.RTDB.setFloat(&fbdo, "Earthquake/Magnitude", magnitude)) {
      Serial.println();
      Serial.print(magnitude);
      Serial.print(" - successfully saved to: " + fbdo.dataPath());
      Serial.println(" (" + fbdo.dataType() + ")");
    } else {
      Serial.println("FAILED: " + fbdo.errorReason());
    };
  }
}

void setEarthquakeLevel(int level) {
  // check if the server is established
  if (Firebase.ready()) {
    // Store data to respective datapath
    if (Firebase.RTDB.setFloat(&fbdo, "Earthquake/Level", level)) {
      Serial.println();
      Serial.print(level);
      Serial.print(" - successfully saved to: " + fbdo.dataPath());
      Serial.println(" (" + fbdo.dataType() + ")");
    } else {
      Serial.println("FAILED: " + fbdo.errorReason());
    };
  }
}
