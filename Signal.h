void initSignal() {
  pinMode(signalPin, OUTPUT);
}
void handleSignal_0() {
  // Off the LED
  digitalWrite(signalPin, 0);
  Serial.println("Detected Level 0");
}
void handleSignal_1() {
  // TODO to implement all signal str
}
void handleSignal_2() {
}
void handleSignal_3() {
}
void handleSignal_4() {
}
void handleSignal_5() {
}
void handleSignal_6() {
}