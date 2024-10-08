#include <Firebase_ESP_Client.h>
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

// -------------------------------------------------
// Firebase Option
// -------------------------------------------------
// #define ANONYMOUS
// #define FIREBASE_VERBOSE
#define DELAY_TIME 250

// #define DEBUG_JSON
#define FB_SET_METHOD_1  // JSON set
// #define FB_SET_METHOD_2  // Individual set

// -------------------------------------------------
// Firebase Value
// -------------------------------------------------
#ifndef ANONYMOUS
#define USER_EMAIL "estupido404@gmail.com"
#define USER_PASSWORD "Stupido@404"
#endif
#define API_KEY "AIzaSyCTZj09mjxN2LfGO_O2gbCziAixP8GOl4M"
#define DB_URL "https://earthquake-6db21-default-rtdb.asia-southeast1.firebasedatabase.app/"

#define SENSOR_NODE_ACCEL_X_PATH "Sensor/1/Accelerometer/X"
#define SENSOR_NODE_ACCEL_Y_PATH "Sensor/1/Accelerometer/Y"
#define SENSOR_NODE_ACCEL_Z_PATH "Sensor/1/Accelerometer/Z"
#define SENSOR_NODE_GYRO_X_PATH "Sensor/1/Gyroscope/X"
#define SENSOR_NODE_GYRO_Y_PATH "Sensor/1/Gyroscope/Y"
#define SENSOR_NODE_GYRO_Z_PATH "Sensor/1/Gyroscope/Z"
#define SENSOR_NODE_MAG_X_PATH "Sensor/1/Magnetometer/X"
#define SENSOR_NODE_MAG_Y_PATH "Sensor/1/Magnetometer/Y"
#define SENSOR_NODE_MAG_Z_PATH "Sensor/1/Magnetometer/Z"
#define SENSOR_NODE_TEMP_PATH "Sensor/1/Temperature/"

#define SENSOR_NODE_WIFI_HOSTNAME_PATH "Connection/Sensor 1/Hostname"
#define SENSOR_NODE_WIFI_LOCAL_IP_PATH "Connection/Sensor 1/Local IP"
#define SENSOR_NODE_WIFI_SIGNAL_STRENGTH_PATH "Connection/Sensor 1/Signal Strength"

#define ALARM_NODE_WIFI_HOSTNAME_PATH "Connection/Platform/Hostname"
#define ALARM_NODE_WIFI_LOCAL_IP_PATH "Connection/Platform/Local IP"
#define ALARM_NODE_WIFI_SIGNAL_STRENGTH_PATH "Connection/Platform/Signal Strength"

#define EARTHQUAKE_MAGNITUDE_PATH "Earthquake/Sensor 1/Magnitude"
#define EARTHQUAKE_LEVEL_PATH "Earthquake/Sensor 1/Level"

// -------------------------------------------------
// Usage - Function
// -------------------------------------------------

FirebaseJson fbjson;
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig fbconfig;

// Initialize Firebase
void initFirebase() {
#ifndef ANONYMOUS
  // Firebase sign-in
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;
#endif
  // Firebase config
  fbconfig.api_key = API_KEY;
  fbconfig.database_url = DB_URL;

// Anonymous sign-up (optional)
#ifdef ANONYMOUS
  if (Firebase.signUp(&fbconfig, &auth, "", "")) {
    Serial.print("New user signed up!");
  } else {
    Serial.printf("%s\n", fbconfig.signer.signupError.message.c_str());
  }
#endif
  // Token status callback
  fbconfig.token_status_callback = tokenStatusCallback;

  // Reconnect Wi-Fi
  Firebase.reconnectWiFi(true);

  // Set SSL buffer size
  fbdo.setBSSLBufferSize(4096, 1024);

  // Set response size
  fbdo.setResponseSize(4096);

  // Firebase begin
  Firebase.begin(&fbconfig, &auth);
}

// -------------------------------------------------
// Push JSON
// -------------------------------------------------
void updateNode() {
  if (Firebase.ready()) {
    if (Firebase.RTDB.updateNode(&fbdo, "/", &fbjson)) {
#ifdef FIREBASE_VERBOSE
      Serial.println("JSON Sent to RTDB: ");
#endif
    } else {
      Serial.println(fbdo.errorReason());
    }
  } else {
    Serial.println("FAILED: " + fbdo.errorReason());
  }
}

void updateNodeAsync() {
  if (Firebase.ready()) {
    if (Firebase.RTDB.updateNodeAsync(&fbdo, "/", &fbjson)) {
#ifdef FIREBASE_VERBOSE
      Serial.println("JSON Sent to RTDB: ");
#endif
    } else {
      Serial.println(fbdo.errorReason());
    }
  } else {
    Serial.println("FAILED: " + fbdo.errorReason());
  }
}

// -------------------------------------------------
// Custom Int Float
// -------------------------------------------------
void fb_SetInt(String dataPath, int value) {
  // Verify Firebase connection
  if (Firebase.ready()) {
    // Store data to respective datapath
    if (Firebase.RTDB.setInt(&fbdo, dataPath, value)) {
#ifdef FIREBASE_VERBOSE
      Serial.println();
      Serial.print(value);
      Serial.print(" - successfully saved to: " + fbdo.dataPath());
      Serial.println(" (" + fbdo.dataType() + ")");
#endif
    } else {
      Serial.println("FAILED: " + fbdo.errorReason());
    };
  }
}
void fb_SetFloat(String dataPath, float value) {
  // Verify Firebase connection
  if (Firebase.ready()) {
    // Store data to respective datapath
    if (Firebase.RTDB.setFloat(&fbdo, dataPath, value)) {
#ifdef FIREBASE_VERBOSE
      Serial.println();
      Serial.print(value);
      Serial.print(" - successfully saved to: " + fbdo.dataPath());
      Serial.println(" (" + fbdo.dataType() + ")");
#endif
    } else {
      Serial.println("FAILED: " + fbdo.errorReason());
    };
  }
}

// -------------------------------------------------
// Set String
// -------------------------------------------------
void fb_SetString(String dataPath, String value) {
  // Verify Firebase connection
  if (Firebase.ready()) {
    // Store data to respective datapath
    if (Firebase.RTDB.setString(&fbdo, dataPath, value)) {
#ifdef FIREBASE_VERBOSE
      Serial.println();
      Serial.print(value);
      Serial.print(" - successfully saved to: " + fbdo.dataPath());
      Serial.println(" (" + fbdo.dataType() + ")");
#endif
    } else {
      Serial.println("FAILED: " + fbdo.errorReason());
    };
  } else {
    Serial.println("Error: Firebase not ready.");
  }
}

// -------------------------------------------------
// Get String
// -------------------------------------------------

String fb_Get(String dataPath) {
  // Verify Firebase connection
  if (Firebase.ready()) {
    // Store data to respective datapath
    if (Firebase.RTDB.get(&fbdo, dataPath)) {
#ifdef FIREBASE_VERBOSE
      Serial.println("Successful READ from " + fbdo.dataPath() + ": " + fbdo.stringData() + " (" + fbdo.dataType() + ")");
#endif
      return fbdo.to<String>();
    } else {
      Serial.println("FAILED: " + fbdo.errorReason());
    };
  } else {
    Serial.println("Error: Firebase not ready.");
  }
  return "";
}


// -------------------------------------------------
// Custom Boolean
// -------------------------------------------------
void fb_SetBool(String dataPath, bool value) {
  // Verify Firebase connection
  if (Firebase.ready()) {
    // Store data to respective datapath
    if (Firebase.RTDB.setBool(&fbdo, dataPath, value)) {
#ifdef FIREBASE_VERBOSE
      Serial.println();
      Serial.print(value ? "true" : "false");
      Serial.print(" - successfully saved to: " + fbdo.dataPath());
      Serial.println(" (" + fbdo.dataType() + ")");
#endif
    } else {
      Serial.println("FAILED: " + fbdo.errorReason());
    };
  } else {
    Serial.println("Error: Firebase not ready.");
  }
}

bool fb_GetBool(String dataPath) {
  // Verify Firebase connection
  if (Firebase.ready()) {
    // Store data to respective datapath
    if (Firebase.RTDB.getBool(&fbdo, dataPath)) {
      if (fbdo.dataType() == "boolean") {
#ifdef FIREBASE_VERBOSE
        Serial.println("Successful READ from " + fbdo.dataPath() + ": " + fbdo.boolData() + " (" + fbdo.dataType() + ")");
#endif
        return fbdo.boolData();
      }
    } else {
      Serial.println("FAILED: " + fbdo.errorReason());
    };
  } else {
    Serial.println("Error: Firebase not ready.");
  }
  return false;
}
