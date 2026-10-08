# Automotive Capacitive Telemetry & IoT System

## Overview
An embedded hardware and networking system designed to simulate a real-time "hands-on-wheel" proximity detection array for Advanced Driver Assistance Systems (ADAS). The project utilizes solid-state capacitive sensing and high-frequency IoT network protocols to ensure zero-latency driver monitoring.

## Core Architecture
* **Hardware:** ESP32 Microcontroller
* **Firmware:** Embedded C
* **Network Protocol:** MQTT over TCP/IP

## Technical Implementations
1. **Solid-State Capacitive Sensing:** Engineered a proximity detection array utilizing the ESP32's capacitive touch capabilities, eliminating the need for mechanical switches and reducing physical hardware degradation.
2. **Threshold-Based Noise Filtering:** Developed lightweight C firmware to continuously poll physical sensor data. Implemented a strict high-pass threshold filter to mitigate ambient environmental interference and prevent false-positive trigger events.
3. **High-Frequency MQTT Telemetry:** Architected a real-time IoT data pipeline transmitting time-series sensor payloads at 10Hz to a remote monitoring dashboard.
4. **Bandwidth Optimization:** Completely bypassed standard HTTP overhead by utilizing MQTT (Publish/Subscribe) over TCP/IP, ensuring continuous, low-latency telemetry streaming without flooding internal vehicle network layers.

## Project Structure
Contains the Embedded C firmware source code, network configuration parameters for the MQTT broker, and sensor polling logic.
