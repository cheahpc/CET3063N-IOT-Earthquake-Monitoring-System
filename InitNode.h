// Define which node to initialize
#define SENSOR
// #define ALARM

// Initialize all necessary library and values
// #include <WiFi.h>
#include <ESP8266WiFi.h>
#include <Firebase_ESP_Client.h>
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

#ifdef SENSOR
#include "Wire.h"
#include "I2C.h"
#include "MPU9250.h"
#endif

// -------------------------------------------------
// Wifi Value
// -------------------------------------------------
#define SSID "PasswordIsPassword"
#define PASSWORD "password"
#define API_KEY "AIzaSyDIW_bDNu-CQN1ZQFZNeGt3XXdZSYAjIzg"
#define DB_URL "https://earthquake-7ad7f-default-rtdb.asia-southeast1.firebasedatabase.app/"

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig fbconfig;

unsigned long sendDataPrevMillis = 0;
bool signupOK = false;

// -------------------------------------------------
// Init Node
// -------------------------------------------------
#pragma region setup_init
void initNode() {
  // Begin serial
  Serial.begin(115200);

#ifdef SENSOR
  // Initialize Sensor node
  // Begin Wire
  Wire.begin();
// MPU9250 Init
#ifdef ENABLE_ACCEL
  I2CwriteByte(0x68, 28, ACC_FULL_SCALE_2G);  // Configure accelerometer range
#endif

#ifdef ENABLE_GYRO
  I2CwriteByte(0x68, 27, GYRO_FULL_SCALE_1000_DPS);  // Configure gyroscope range
#endif

#ifdef ENABLE_MAGNETO
  I2CwriteByte(0x68, 55, 0x02);  // Set by pass mode for the magnetometers
  initMagnetometer();
  I2CwriteByte(0x68, 56, 0x01);  // Enable interrupt pin for raw data
#endif

#endif

#ifdef ALARM
  // Initialize Alarm node

#endif
  // Wifi Init
  WiFi.begin(SSID, PASSWORD);
  Serial.println("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }

  Serial.println("");
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  fbconfig.api_key = API_KEY;
  fbconfig.database_url = DB_URL;
  if (Firebase.signUp(&fbconfig, &auth, "", "")) {
    Serial.print("signUP OK");
    signupOK = true;
  } else {
    Serial.printf("%s\n", fbconfig.signer.signupError.message.c_str());
  };

  fbconfig.token_status_callback = tokenStatusCallback;
  Firebase.begin(&fbconfig, &auth);
  Firebase.reconnectWiFi(true);

  // Connect to wifi
}
#pragma endregion setup_init