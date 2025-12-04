# Flood Detection & Warning System (Arduino)

A multi-stage flood detection and automated warning system originally developed during high school and later **refactored for modularity, clarity, and maintainability** during university studies.

The system monitors three independent water-level sensors, classifies danger levels, and triggers LEDs, relays, LCD messages, and an audio alarm using DFPlayer Mini.  
Designed to model a real-world underpass flooding prevention system.

---

## 🚀 Features
- Multi-level water detection (SAFE → Level 1 → Level 2 → Level 3)
- LED status indicators (RGB status system)
- Relay-controlled warning actuators
- LCD message display for stage notifications
- DFPlayer Mini MP3 alarm playback
- Modular, structured, and maintainable codebase

---

## 📁 Project Structure

---

## 🧠 System Logic (State Machine)

The system uses a **clean water-level state machine**:


Each state controls:

- LED colors  
- Relay output patterns  
- LCD display  
- Speaker alarm (Level 3)
  
---

## 📸 Prototype (Images Here)



---

## 🛠️ Hardware Used
- Arduino Mega 2560
- DFPlayer Mini
- 16x2 LCD
- Relay modules
- RGB LED modules
- Analog water sensors (x3)

---

## 🏗️ Full Source Code

See `src/FloodDetection.ino`.

---

## ✨ Notes
- Originally developed in high school for K-Tech IDEA Challenge
- Updated and refactored for clarity in 2025
- Suitable for embedded systems and automation portfolio use
