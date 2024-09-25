# The Pythons RoboCupJunior Open Weight Soccer 2024

Welcome to the repository for **The Pythons** team's project for RoboCupJunior Open Weight Soccer 2024!

This repository contains the mechanical, electrical, and software designs of our soccer-playing robot. Our team, hailing from **Sidi Gaber Language School for Boys, Alexandria, Egypt**, developed this robot to compete at the **RoboCupJunior 2024** in Germany. After securing second place in the national competition, we are committed to refining our robot and achieving success in the international stage.

## Team Members

- **Ahmed Wael** (Software Developer)
- **Ahmad Zaki** (Software Developer)
- **Abdullah Ayman** (Electrical Engineer)
- **Adam Mohamed** (Mechanical Engineer)

**Mentors:** Adham Amr, Amr El Shabacy, Youssef Attia

## Project Overview

Our project involves building a robot equipped with advanced control systems and vision algorithms to autonomously play soccer. This robot is designed using a multi-layer PCB for better stability and a more elegant design. It features improvements in ball control, motion handling, and line detection.

### Key Features:

- **Mechanical Design**: 3-layer chassis with CNC-cut base and 3D-printed dribbler system for ball control.
- **Electrical Design**: Raspberry Pi Pico as the master controller, with two Arduino Nano boards managing sensors and motor control.
- **Software Design**: Modular architecture for easier debugging and quick updates, with holonomic motion equations and advanced vision processing using OpenMV cameras and a hyperbolic mirror.

### Major Hardware Components:

- **Raspberry Pi Pico** (Main controller)
- **Arduino Nano** (Sensor controllers)
- **OpenMV H7 Camera** (Vision system)
- **Hyperbolic Mirror** (Omnidirectional vision)
- **Metal Gear Motors** (Motion system)
- **Brushless Motor** (Dribbler system)

### Vision System

The robot uses a hyperbolic mirror paired with the OpenMV camera for a 360° view of the field. The software processes color blobs to detect the ball, calculates its position, and adjusts the robot’s motion to align with the ball.

## Software Modules

- **Movement Control**: Holonomic motion allowing the robot to move in any direction instantly.
- **Vision System**: Detects and tracks the ball’s position and calculates angles for optimized movement.
- **IMU Calibration**: Integrates data from gyroscope and magnetometer for precise heading control.
- **Line Sensor Calibration**: Detects the field boundaries and keeps the robot within bounds during the match.

## Testing and Performance

We thoroughly test both the hardware and software systems before each match. Hardware tests ensure all subsystems are working properly, and software tests focus on validating sensor readings and autonomous movement.

## References

- [Our Website](https://www.the-pythons.com/)
- [GitHub Repository](https://github.com/Ahmad-Zaki05/The-Pythons-Open-Weight-Soccer)

For any inquiries, contact us at [info@the-pythons.com](mailto:info@the-pythons.com).
