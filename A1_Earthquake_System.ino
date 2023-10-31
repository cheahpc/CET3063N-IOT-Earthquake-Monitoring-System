#include "InitNode.h"

unsigned long prevT_Amplitude = 0;
unsigned long prevT_Magnitude = 0;
unsigned long tTres_Amplitude_SampleRate = 5;
unsigned long tTres_Magnitude_SampleRate = 500;
float currentAmplitude = 0;
float maxAmplitude = 0;
unsigned int level;

void setup() {
  // Start Everything
  initNode();
}
void loop() {

#ifdef SENSOR
  // Sample sensor value and find magnitude change
  if ((millis() - prevT_Amplitude) >= tTres_Amplitude_SampleRate) {
    // Sample amplitude
    currentAmplitude = eGetAmplitude(imu_GetAccel(3));
    // Set new maximum amplitude
    maxAmplitude = max(maxAmplitude, currentAmplitude);

    

    if ((millis() - prevT_Magnitude) >= tTres_Magnitude_SampleRate) {
      
      // Update RTDB with new magnitude
      fb_SetFloat(EARTHQUAKE_MAGNITUDE_PATH, eGetMagnitude(maxAmplitude));

      // Reset maximum amplitude
      maxAmplitude = 0;
      prevT_Magnitude = millis();
    }

    // Update RTDB with sampled current amplitude
    fb_SetFloat(EARTHQUAKE_AMPLITUDE_PATH, currentAmplitude);

    // UPDate
    getSensorJSON();
    updateNodeAsync();
    prevT_Amplitude = millis();
  }

#endif

#ifdef PLATFORM
  server.handleClient();
#endif
}
