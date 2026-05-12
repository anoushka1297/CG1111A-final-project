# CG1111A-final-project- Autonomous mBot Maze Solver
Autonomous maze-solving mBot with wall following, line detection, and custom-built RGB colour sensing system. Developed for NUS CG1111A.
*This repository was uploaded after project completion for documentation and archival purposes*

## Overview

This project was built using the Makeblock mBot platform and Arduino.

The robot is capable of:

* Following maze walls using **ultrasonic** and **custom IR proximity sensing**
* Detecting black maze lines using the inbuilt line follower
* Identifying coloured tiles using a **custom RGB + LDR colour sensor**
* Executing different movement behaviours depending on detected colour
* Playing a melody upon reaching the goal tile

The system integrates both software and hardware design, including custom sensor circuits, proportional wall-following control, colour classification logic, and physical light shielding for reliable sensing.

---

## Photos

### LEFT (Ultrasonic sensor)
<img width="425" height="387" alt="Screenshot 2026-05-11 at 10 29 26 PM" src="https://github.com/user-attachments/assets/61839192-f962-4bec-ae14-cddfa0c4ab43" />

### RIGHT (Custom IR sensor)
<img width="427" height="358" alt="Screenshot 2026-05-11 at 10 30 05 PM" src="https://github.com/user-attachments/assets/c01109c6-4450-4170-93f1-b0f03a9c26ee" />

### BOTTOM (LDR + RGB colour sensor)
<img width="454" height="397" alt="Screenshot 2026-05-11 at 10 31 13 PM" src="https://github.com/user-attachments/assets/57ba86ea-d703-4373-8ad2-348b1633b52b" />


## Features

* Dual-wall proportional correction using:

  * Ultrasonic sensor (left wall)
  * Custom IR emitter/receiver pair (right wall)

* Custom colour sensing system using:

  * RGB LEDs
  * LDR
  * 2-to-4 decoder logic

* Autonomous maze navigation

* Modular Arduino code structure

* Ambient light reduction enclosure for stable colour sensing

* Rickroll victory melody

---

## Hardware Components

| Component              | Purpose                        |
| ---------------------- | ------------------------------ |
| mBot / mCore           | Main controller                |
| Ultrasonic Sensor      | Left wall distance measurement |
| Line Follower          | Maze line detection            |
| Custom IR Sensor       | Right wall proximity sensing   |
| RGB LEDs + LDR         | Colour detection               |
| 2-to-4 Decoder Circuit | LED/IR emitter control         |
| DC Motors              | Robot movement                 |
| Buzzer                 | Audio feedback                 |

---

## System Architecture

### Wall Following

The robot combines:

* ultrasonic distance readings from the left wall
* infrared reflection intensity from the right wall

Both values are converted into proportional correction terms and merged into a single steering correction.

This keeps the robot approximately centered between the maze walls while maintaining smooth motion.

---

### Colour Detection

The colour sensor is built using:

* Red, Green, and Blue LEDs
* An LDR
* Shared decoder outputs

Each LED is enabled sequentially while the LDR measures reflected light intensity from the floor tile.

The averaged RGB readings are then compared against experimentally calibrated thresholds to identify:

* Red
* Orange
* Green
* Pink
* Light Blue
* White (goal tile)

To improve reliability, the sensor assembly was enclosed using black paper and tape to reduce ambient light interference.

---

## Colour Actions

| Tile Colour | Robot Action                  |
| ----------- | ----------------------------- |
| Red         | Left turn                     |
| Orange      | Reverse                       |
| Green       | Right turn                    |
| Pink        | Double left turn              |
| Light Blue  | Double right turn             |
| White       | Play melody / maze completion |

---

## Code Structure

```text
.
├── final_main.ino
├── a_Sensors.ino
├── b_ColourDetect.ino
├── c_LineDetect_WallFollowing.ino
└── d_Melody.ino
```

### `main.ino`

Top-level controller:

* robot enable/disable
* main loop
* system coordination

### `a_Sensors.ino`

Sensor handling:

* ultrasonic distance
* IR reflection sensing
* LDR averaging

### `b_ColourDetect.ino`

Colour classification and colour-triggered movement actions.

### `c_LineDetect_WallFollowing.ino`

* line detection
* proportional wall following
* motor correction logic

### `d_Melody.ino`

Goal melody playback using the onboard buzzer.

---

## Navigation Logic

1. Robot moves forward while following walls
2. Line sensor continuously checks for black lines
3. When a line is detected:

   * robot stops
   * LEDs are reset
   * colour detection sequence begins
4. Detected colour determines the next movement action
5. Process repeats until the goal tile is reached

---




## Technologies Used

* Arduino IDE
* C++
* Makeblock mBot / mCore
* Embedded systems programming
* Analog sensor interfacing

---

## Team Members

* Tran Hoang Khang
* Truong Phi Hung
* Tripathi Anoushka

---

## Notes


The Arduino project consists of multiple `.ino` files which must be opened together inside the same Arduino IDE project folder, as Arduino automatically merges all `.ino` files during compilation.

---


