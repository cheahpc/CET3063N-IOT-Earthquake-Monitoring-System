// Define the threshold values for each earthquake level
const float earthquakeThresholds[] = {
  10.0,  // No earthquake
  15.0,  // Minor earthquake
  20.0,  // Moderate earthquake
  25.0,  // Strong earthquake
  30.0,  // Severe earthquake
};

// Calculate the magnitude of the acceleration
float getEarthquakeMagnitude() {
  return sqrt(pow(getAccel(1), 2) + pow(getAccel(2), 2) + pow(getAccel(3), 2));
}

// Get the earthquake level
int getEarthquakeLevel() {
  float magnitude = getEarthquakeMagnitude();
  // Determine the earthquake level based on the magnitude
  for (int i = 0; i < sizeof(earthquakeThresholds) / sizeof(float); i++) {
    if (magnitude >= earthquakeThresholds[i]) {
      return i;
      break;
    }
  }
}
