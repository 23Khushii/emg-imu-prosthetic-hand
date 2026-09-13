/*
 * EMG-Controlled Fist Actuation
 * ------------------------------
 * Reads smoothed EMG signal from a single sensor channel and drives a
 * servo motor to open/close a prosthetic fist based on a calibrated
 * activation threshold.
 *
 * Hardware: Arduino-compatible board, EMG sensor on A0, servo on pin 9.
 */

#include <Servo.h>

Servo myHand;
const int emgPin = A0;
const int servoPin = 9;

// Calibrated values (adjust for your sensor / user)
int threshold = 550;
int openAngle = 0;
int closedAngle = 180;

// Smoothing (moving average over last N readings)
const int numReadings = 5;
int readings[numReadings];
int readIndex = 0;
int total = 0;
int smoothedValue = 0;

int emgValue = 0;
bool fistClosed = false;
unsigned long lastAction = 0;

void setup() {
  Serial.begin(9600);
  myHand.attach(servoPin);
  myHand.write(openAngle);

  for (int i = 0; i < numReadings; i++) {
    readings[i] = 0;
  }
}

void loop() {
  emgValue = analogRead(emgPin);

  // Apply moving-average smoothing to reduce noise-driven false triggers
  total = total - readings[readIndex];
  readings[readIndex] = emgValue;
  total = total + readings[readIndex];
  readIndex = (readIndex + 1) % numReadings;
  smoothedValue = total / numReadings;

  Serial.print("Raw: ");
  Serial.print(emgValue);
  Serial.print(" | Smoothed: ");
  Serial.println(smoothedValue);

  // Debounce: only allow a state change every 300ms
  if (millis() - lastAction > 300) {

    if (smoothedValue > threshold && !fistClosed) {
      myHand.write(closedAngle);
      fistClosed = true;
      lastAction = millis();
      Serial.println("FIST CLOSED");
    }

    else if (smoothedValue < threshold && fistClosed) {
      myHand.write(openAngle);
      fistClosed = false;
      lastAction = millis();
      Serial.println("HAND OPEN");
    }
  }

  delay(20);
}
