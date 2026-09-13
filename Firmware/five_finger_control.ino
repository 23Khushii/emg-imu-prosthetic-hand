/*
 * 5-Finger Proportional EMG Control
 * ----------------------------------
 * Reads smoothed EMG signal and maps contraction intensity proportionally
 * to servo angle, driving all 5 finger servos simultaneously for a
 * graded (non-binary) grasp response.
 *
 * Hardware: Arduino-compatible board, EMG sensor on A0,
 * 5x servo motors on pins 9-13.
 */

#include <Servo.h>

// EMG sensor pin
const int emgPin = A0;

// Create 5 servo objects
Servo finger1;
Servo finger2;
Servo finger3;
Servo finger4;
Servo finger5;

// Digital pins the servos are connected to
const int servoPins[] = {9, 10, 11, 12, 13};

// Calibration values (set from per-user calibration routine)
int restingValue = 47;      // EMG value when relaxed
int flexedValue = 700;      // EMG value at max contraction

// Servo angle limits (adjust for mechanical setup)
const int openAngle = 0;      // Finger open position
const int closedAngle = 180;  // Finger closed position

// Smoothing (moving average over last N readings)
const int numReadings = 10;
int readings[numReadings];
int readIndex = 0;
int total = 0;
int smoothedValue = 0;

void setup() {
  Serial.begin(9600);

  // Attach all 5 servos to their pins
  finger1.attach(servoPins[0]);
  finger2.attach(servoPins[1]);
  finger3.attach(servoPins[2]);
  finger4.attach(servoPins[3]);
  finger5.attach(servoPins[4]);

  // Initialize all fingers to open position
  finger1.write(openAngle);
  finger2.write(openAngle);
  finger3.write(openAngle);
  finger4.write(openAngle);
  finger5.write(openAngle);

  // Initialize smoothing array
  for (int i = 0; i < numReadings; i++) {
    readings[i] = 0;
  }

  Serial.println("5-Finger EMG Control Ready");
  Serial.print("Resting value: ");
  Serial.println(restingValue);
  Serial.print("Flexed value target: ");
  Serial.println(flexedValue);
  delay(1000);
}

void loop() {
  // 1. Read EMG value
  int rawValue = analogRead(emgPin);

  // 2. Apply moving average smoothing
  total = total - readings[readIndex];
  readings[readIndex] = rawValue;
  total = total + readings[readIndex];
  readIndex = (readIndex + 1) % numReadings;
  smoothedValue = total / numReadings;

  // 3. Map EMG intensity to a proportional servo angle
  int targetAngle = map(smoothedValue, restingValue, flexedValue, openAngle, closedAngle);
  targetAngle = constrain(targetAngle, openAngle, closedAngle);

  // 4. Drive all 5 fingers to the same proportional angle
  finger1.write(targetAngle);
  finger2.write(targetAngle);
  finger3.write(targetAngle);
  finger4.write(targetAngle);
  finger5.write(targetAngle);

  // 5. Debug output
  Serial.print("EMG: ");
  Serial.print(smoothedValue);
  Serial.print(" -> Angle: ");
  Serial.print(targetAngle);
  Serial.print(" deg");

  if (targetAngle > 150) {
    Serial.print(" [FULL CONTRACTION]");
  } else if (targetAngle > 100) {
    Serial.print(" [Strong]");
  } else if (targetAngle > 50) {
    Serial.print(" [Medium]");
  } else if (targetAngle > 10) {
    Serial.print(" [Light]");
  } else {
    Serial.print(" [Relaxed]");
  }
  Serial.println();

  delay(20);
}
