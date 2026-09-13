# AI-Enabled EMG-IMU Prosthetic Hand

### Multimodal intention detection using surface EMG, inertial sensing, machine learning, and embedded servo control.

This project explores an intelligent, low-cost prosthetic hand architecture that combines **surface electromyography (sEMG)** and **inertial measurement unit (IMU)** data to infer hand and wrist movement.

The system follows an end-to-end pipeline:

**Muscle Activity → Signal Acquisition → Filtering → Feature Extraction → Gesture Classification → Embedded Control → Servo Actuation**

The central idea is to use EMG to capture **physiological muscle activation** while the IMU provides **motion and positional context**, helping distinguish movements that may produce similar EMG patterns.

---

## Project Highlights

| Component | Implementation |
|---|---|
| EMG sensing | MyoWare surface EMG |
| IMU sensing | MPU6050 accelerometer + gyroscope |
| Embedded platform | Arduino-based controller |
| Actuation | MG996R servo motors |
| EMG preprocessing | 20–500 Hz band-pass + 50 Hz notch |
| Feature extraction | RMS, MAV, Waveform Length |
| ML baseline | Random Forest |
| Dataset | NinaPro DB5 |
| Gesture classes | 6-class evaluation |
| Baseline accuracy | **~88.7%** |
| Control | EMG / gesture-driven servo actuation |

---

## System Architecture

![System Architecture](media/System_Architecture.jpeg)

The system is divided into four major stages:

### 1. Multimodal Sensor Acquisition

Two complementary sources of information are collected:

**EMG — MyoWare**

Captures electrical activity produced by muscle contractions and provides information about the user's intended movement.

**IMU — MPU6050**

Provides accelerometer and gyroscope measurements that describe movement and orientation.

Combining these signals provides both **physiological** and **kinematic** information.

---

### 2. Signal Processing

Raw EMG signals are susceptible to motion artifacts, baseline noise, and power-line interference.

The preprocessing pipeline includes:

```text
Raw EMG
   │
   ▼
Band-pass Filtering
20–500 Hz
   │
   ▼
50 Hz Notch Filtering
   │
   ▼
Windowing
200 ms windows
50% overlap
   │
   ▼
Feature Extraction
RMS / MAV / WL
