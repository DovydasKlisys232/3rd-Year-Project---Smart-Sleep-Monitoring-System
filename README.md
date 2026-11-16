# 3rd-Year-Project---Smart-Sleep-Monitoring-System
## Overview

The Smart Sleep Monitoring System is a third-year Computer Engineering project that investigates the use of embedded systems and IoT technologies for sleep monitoring.

The system was developed using an ESP32-based FireBeetle microcontroller and integrates audio sensing, local storage, wireless communication, and environmental monitoring components. Various hardware and software configurations were explored throughout development before being integrated into the final system.

---

## Repository Structure

```text
3rd-Year-Project---Smart-Sleep-Monitoring-System
│
├── Arduino Code/
│   ├── Audio_code/
│   ├── firebeetle/
│   ├── bluetooth_speaker_test/
│   ├── INMP441_practicecode/
│   ├── noSD/
│   └── Test_LittleFS/
│
├── 3d Print/
│
├── Images/
│
├── Report/
│
├── LICENSE
└── README.md
```

---

## Arduino Code Directory

The `Arduino Code` directory contains all firmware developed throughout the project.

### Final Project Code

#### Audio_code

Contains the final audio processing implementation used within the Smart Sleep Monitoring System.

Features explored include:

- Audio acquisition
- Signal processing
- Sleep-related audio monitoring
- Sensor integration

#### firebeetle

Contains the primary firmware running on the FireBeetle ESP32 microcontroller.

This folder represents the main integrated system and combines functionality developed throughout the project.

---

## Development and Testing Folders

The remaining folders contain experimental and testing code created during development.

### bluetooth_speaker_test

Used to evaluate Bluetooth speaker connectivity and audio output functionality.

### INMP441_practicecode

Contains code used during experimentation with the INMP441 MEMS microphone.

Used to:

- Verify microphone operation
- Capture audio samples
- Test audio quality and acquisition methods

### noSD

Development version of the project without SD card functionality enabled.

Used to isolate and test core system features before introducing local storage.

### Test_LittleFS

Contains experiments using the ESP32 LittleFS file system.

Used to:

- Test onboard storage
- Evaluate file read/write performance
- Explore alternatives to SD card storage

---

## Additional Project Resources

### 3d Print

Contains 3D printing files used to manufacture components and housing for the project.

### Images

Contains project photographs, diagrams, screenshots, and supporting visuals.

### Report

Contains the final project report and supporting documentation, including:

- System design
- Hardware architecture
- Software implementation
- Testing methodology
- Results and evaluation

---

## Hardware Used

The project incorporates the following hardware:

- FireBeetle ESP32
- INMP441 MEMS Microphone
- MicroSD Storage
- Bluetooth Audio Components
- Custom 3D Printed Enclosure

---

## Project Objectives

The project aimed to:

- Investigate embedded sleep monitoring technologies
- Capture and process audio data
- Explore IoT-enabled monitoring systems
- Evaluate local and onboard storage solutions
- Develop a complete working prototype using ESP32 hardware

---

## Author

**Dovydas Klisys**

Bachelor of Engineering (Computer Engineering)

Technological University Dublin

---
