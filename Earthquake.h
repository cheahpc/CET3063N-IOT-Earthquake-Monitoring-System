// -------------------------------------------------
// Formula option
// -------------------------------------------------
// #define FORMULA_A
#define FORMULA_B

// Define the threshold values for each earthquake level
const float earthquakeThresholds[] = {
  10.0,  // No earthquake
  15.0,  // Minor earthquake
  20.0,  // Moderate earthquake
  25.0,  // Strong earthquake
  30.0,  // Severe earthquake
};
float result;

// Calculate the magnitude of the acceleration
float e_GetRitcherMagnitude(float val1, float val2, float val3) {
  // Ritcher formula A = log(A0) - log(A1 * d)
  // Ritcher formula B = log(A1/A0)
  // A0 = constant ~ 10.5 Idle magnitude
  // A1 = sensor magnitude
  // d  = hardcoded constant 20m for example
  //  A0_______________________A1
  //    <----------d----------> the distance between A0 and A1
  const float A0 = 10.5;
  const int d = 20;
  const float A1 = sqrt(pow(val1, 2) + pow(val2, 2) + pow(val3, 2));
  #ifdef FORMULA_A
  result = log10(A0) - log10(A1*d);
  #endif 
  #ifdef FORMULA_B
  result = log10(A1/A0);
  #endif
  return result;
}
// Get the earthquake level
int e_GetLevel() {

  // Determine the earthquake level based on the magnitude
  for (int i = 0; i < sizeof(earthquakeThresholds); i++) {
    if (result >= earthquakeThresholds[i]) {
      return i;
    }
  }
  return -1;
}
