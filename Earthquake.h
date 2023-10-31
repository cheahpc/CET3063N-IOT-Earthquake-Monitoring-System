// -------------------------------------------------
// Eartquake option
// -------------------------------------------------
// #define FORMULA_A
#define FORMULA_B
#define Z_AXIS_CONSTANT 9.2
#define D 10000  // 10km
#define A0 9.2

// Define the threshold values for each earthquake level
const float earthquakeThresholds[] = {
  10.0,  // No earthquake
  15.0,  // Minor earthquake
  20.0,  // Moderate earthquake
  25.0,  // Strong earthquake
  30.0,  // Severe earthquake
};
float amplitude, magnitude;
// Getter
float eGetMagnitude(float maxAmplitude) {
  // Ritcher formula A = log(A0) - log(A1 * d)
  // Ritcher formula B = log(A1/A0)
  // A0 = reference constant
  // A1 = sensor amplitude
  // d  = constant
  //  A0_______________________A1
  //    <----------d----------> the distance between A0 and A1

#ifdef FORMULA_A
  magnitude = log10(A0) - log10(maxAmplitude * D); 
  // magnitude = log10(maxAmplitude) - log10(A0 * D);
#endif
#ifdef FORMULA_B
  magnitude = log10(maxAmplitude / A0);
  magnitude = magnitude*100; // Scale up for easier classification
#endif

  return magnitude;
}

float eGetAmplitude(float val = 0.0, float constant = Z_AXIS_CONSTANT) {
  // If parameter is passed in, calculate new amplitude
  if (val != 0.0) {
    amplitude = abs(val);
    amplitude = (amplitude > constant) ? amplitude : constant + ( constant- amplitude);
  }
  // Otherwise, get the previous amplitude
  return amplitude;
}