# Adafruit-Fingerprint-Sensor-Library [![Build Status](https://github.com/adafruit/Adafruit-Fingerprint-Sensor-Library/workflows/Arduino%20Library%20CI/badge.svg)](https://github.com/adafruit/Adafruit-Fingerprint-Sensor-Library/actions)[![Documentation](https://github.com/adafruit/ci-arduino/blob/master/assets/doxygen_badge.svg)](http://adafruit.github.io/Adafruit-Fingerprint-Sensor-Library/html/index.html)

<img src="https://cdn-shop.adafruit.com/970x728/751-03.jpg" height="300"/>
<img src="https://cdn-shop.adafruit.com/1200x900/4651-00.jpg" height="300"/>

# 🔐 Fingerprint-Based Solenoid Lock System

This project is a **biometric security system** that uses a fingerprint sensor to control a **solenoid lock**, developed using an **Arduino Uno**. It allows only authorized fingerprints to unlock the mechanism, making it ideal for lockers, cabinets, and basic access control systems.

![Project Demo](demo.gif) <!-- Optional: replace with actual image/GIF path -->

---

## 📌 Features

- Fingerprint-based authentication
- Solenoid lock control using relay
- Visual feedback using LEDs (Access Granted/Denied)
- Easy enrollment of new users via serial input
- Arduino-powered embedded design

---

## 🛠️ Components Used

| Component              | Quantity |
|------------------------|----------|
| Arduino Uno            | 1        |
| R305 / GT511C3 Fingerprint Sensor | 1        |
| Solenoid Lock          | 1        |
| Relay Module (5V)      | 1        |
| Power Supply (9–12V)   | 1        |
| LED (Red & Green)      | 2        |
| Resistors (220Ω)       | 2        |
| Breadboard + Jump Wires| —        |

---

## 🔌 Circuit Connections

| Arduino Pin | Component |
|-------------|-----------|
| D2          | Fingerprint TX |
| D3          | Fingerprint RX |
| D8          | Relay IN |
| D10         | Green LED |
| D11         | Red LED |
| GND / 5V    | Power Lines |

> Note: Use SoftwareSerial library for fingerprint UART communication.

---

## 🧠 How It Works

1. On boot, the system checks for enrolled fingerprints.
2. A user places their finger on the scanner.
3. If matched:
   - The green LED lights up.
   - Relay triggers the solenoid lock to open.
4. If unmatched:
   - The red LED lights up.
   - Lock remains engaged.
5. Admin can enroll new fingerprints via Serial Monitor input.

---

## 💻 Arduino Code Overview

- `Adafruit_Fingerprint.h` used for R305 sensor
- `SoftwareSerial` used for UART communication
- Relay and LED controlled with digital I/O pins
- Timeout + feedback system integrated for security

---

## 🚀 Getting Started

### 1. Clone this repo:
```bash
git clone https://github.com/Kritzr/fingerprint-lock-system.git
