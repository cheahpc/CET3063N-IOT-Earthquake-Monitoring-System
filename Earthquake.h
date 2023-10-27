float getEarthquakeMagnitude() {
  return sqrt(pow(getAccel(1), 2) + pow(getAccel(2), 2) + pow(getAccel(3), 2));
}

int getEarthquakeLevel() {
  float magnitude = getEarthquakeMagnitude();
  if (magnitude < 0.05) {
    return 0;  // No earthquake
  } else if (magnitude < 0.25) {
    return 1;  // Minor earthquake
  } else if (magnitude < 0.5) {
    return 2;  // Moderate earthquake
  } else if (magnitude < 0.75) {
    return 3;  // Strong earthquake
  } else if (magnitude < 1.0) {
    return 4;  // Sever earthquake
  } else {
    return 5;  // Catastrophic earthquake
  }
}
