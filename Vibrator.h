#define vibratorPin D4

void initVibrator(){
  pinMode(vibratorPin, OUTPUT);
}
void aWriteVibrator(int amplitude) {
  analogWrite(D4,amplitude);
  // TODO import to initNode
  // TODO write pwm to motor
  // TODO map vibration to earthquake level
}