// -------------------------------------------------
// Signal Value
// -------------------------------------------------
#define SIGNAL_PIN D0
unsigned long prevT_blink, blinkInterval;
bool blink = false;
bool signal = false;
void initSignal() {
  pinMode(SIGNAL_PIN, OUTPUT);
}
void handleSignal_0() {
  // Off the LED
  blink = false;
}
void handleSignal_1() {
  blink = true;
  blinkInterval = 2000;
}
void handleSignal_2() {
  blink = true;
  // Set blink interval
  blinkInterval = 1750;
}
void handleSignal_3() {
  blink = true;
  // Set blink interval
  blinkInterval = 1500;
}
void handleSignal_4() {
  blink = true;
  // Set blink interval
  blinkInterval = 1250;
}
void handleSignal_5() {
  blink = true;
  // Set blink interval
  blinkInterval = 1000;
}
void handleSignal_6() {
  blink = true;
  // Set blink interval
  blinkInterval = 500;
}
void handleSignal_7() {
  blink = true;
  // Set blink interval
  blinkInterval = 250;
}
void loopSignal() {
  // If blinking is required
  if (blink) {
    if (millis() - prevT_blink > blinkInterval) {
      signal != signal;                  // Toggle signal
      digitalWrite(SIGNAL_PIN, signal);  // Write to signal pin
    }
  }
}