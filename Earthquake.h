

// Define the threshold values for each earthquake level
const float earthquakeThresholds[] = {
  10.0,  // No earthquake
  15.0,  // Minor earthquake
  20.0,  // Moderate earthquake
  25.0,  // Strong earthquake
  30.0,  // Severe earthquake
};
float amplitude, magnitude, x, y, z;

void eSetVal(float val1, float val2, float val3) {
  x = val1;
  y = val2;
  z = val3;

  // Ritcher formula A = log(A0) - log(A1 * d)
  // Ritcher formula B = log(A1/A0)
  // A0 = constant ~ 10.5 Idle magnitude
  // A1 = sensor magnitude
  // d  = hardcoded constant 20m for example
  //  A0_______________________A1
  //    <----------d----------> the distance between A0 and A1
  const float A0 = 10.5;
  const int d = 100;
  const float A1 = sqrt(pow(val1, 2) + pow(val2, 2) + pow(val3, 2));
  amplitude = A1;
#ifdef FORMULA_A
  magnitude = log10(A0) - log10(A1 * d);
#endif
#ifdef FORMULA_B
  magnitude = log10(A1 / A0);
#endif
}
// Getter
float eGetMagnitude() {
  return magnitude;
}
float eGetAmplitude() {
  return amplitude;
}
