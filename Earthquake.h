// Define the threshold values for each earthquake level
const float earthquakeThresholds[] = {
  10.0,  // No earthquake
  15.0,  // Minor earthquake
  20.0,  // Moderate earthquake
  25.0,  // Strong earthquake
  30.0,  // Severe earthquake
};

// Calculate the magnitude of the acceleration
float e_GetEarthquakeMagnitude(float val1, float val2, float val3) {
  return sqrt(pow(val1, 2) + pow(val2, 2) + pow(val3, 2));
}
// Get the earthquake level
int e_GetEarthquakeLevel(float val1, float val2, float val3) {
  float magnitude = e_GetEarthquakeMagnitude(val1, val2, val3);
  // Determine the earthquake level based on the magnitude
  for (int i = 0; i < sizeof(earthquakeThresholds) / sizeof(float); i++) {
    if (magnitude >= earthquakeThresholds[i]) {
      return i;
    }
  }
  return -1;
}
