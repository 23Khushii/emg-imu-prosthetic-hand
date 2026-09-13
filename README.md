# AI-Enabled Low-Cost EMG–IMU Prosthetic Hand

An AI-enabled embedded system for gesture-based prosthetic hand control, combining surface EMG (muscle activity) and IMU (motion) data for adaptive intention detection.

Built as a Problem-Based Learning (PBL) project at MIT World Peace University, Pune.

**Team:** Khushi Sahu, Rishabh Gulecha, Pratik Gite

---

## Overview

This project focuses on developing a low-cost prosthetic hand capable of interpreting user intention from muscle activity and arm motion.

The system combines surface electromyography (sEMG) with inertial measurement unit (IMU) data to capture both physiological and motion information. Signal processing, feature extraction, sensor fusion and machine-learning techniques are used to recognize hand gestures and translate them into prosthetic hand movements.

The overall system integrates embedded hardware, real-time sensor processing and machine-learning-based intention detection.

---

## Key Features

- Surface EMG acquisition using the MyoWare muscle sensor
- IMU-based motion and orientation sensing using MPU6050
- Real-time signal acquisition and preprocessing
- EMG feature extraction using time-domain features
- EMG–IMU sensor fusion
- Machine-learning-based gesture classification
- Confidence-based rejection for uncertain predictions
- Servo-based prosthetic hand actuation
- 3D-printed mechanical hand structure
- Embedded implementation using ESP32

---

## System Architecture

The complete system follows the pipeline:

```text
       EMG Sensor + IMU
              │
              ▼
       Data Acquisition
              │
              ▼
      Signal Preprocessing
              │
              ▼
       Feature Extraction
              │
              ▼
         Sensor Fusion
              │
              ▼
     Gesture Classification
              │
              ▼
       Confidence Gate
              │
              ▼
         Servo Control
              │
              ▼
       Prosthetic Hand
