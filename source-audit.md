# Source Audit: Cytron URC10 Sumo Robot Controller

This document summarizes the technical specifications and requirements for the Cytron URC10 Sumo Robot Controller, based on the provided datasheet, user manual, and sample code.

## 1. Product Name and Purpose
*   **Product Name:** URC10 Sumo Robot Controller (by Cytron Technologies).
*   **Purpose:** A specialized all-in-one controller for Sumo Robots. It combines an Arduino-compatible microcontroller with a high-current dual-channel motor driver and dedicated sensor ports.

## 2. Controller/Microcontroller Type
*   **Type:** Arduino-compatible (specifically standard Arduino Uno form factor/logic).
*   **Microcontroller:** Likely **ATmega328P** (Human confirmation: Manual suggests selecting "Arduino Uno" in the IDE).

## 3. Programming Platform and Language
*   **Platform:** Arduino IDE.
*   **Language:** C++/Arduino Sketch.

## 4. Required Arduino IDE Setup
*   **Board Selection:** "Arduino/Genuino Uno".
*   **Port:** Corresponding COM port after driver installation.

## 5. Required Driver Setup
*   **USB-to-UART Driver:** **CH340** driver is required for the PC to recognize the board via the Micro USB port.

## 6. Required Library
*   **Library Name:** `Cytron Motor Drivers Library` (available via Arduino Library Manager).
*   **Header:** `#include <CytronMotorDriver.h>`

## 7. Motor Driver Pins
*   The board uses a **PWM/DIR** control scheme.
*   **Motor 1 (Left):** PWM: **D5**, DIR: **D4**.
*   **Motor 2 (Right):** PWM: **D6**, DIR: **D7**.

## 8. Sensor Pins
*   **Start Button:** D13.
*   **Edge Sensors:**
    *   Left Edge: D12
    *   Right Edge: D11
*   **Opponent/ID Sensors:**
    *   Left: D3
    *   Right: D10
    *   Front Left: A2
    *   Front Center: A1
    *   Front Right: A0
*   **Ultrasonic Sensors (HC-SR04 Ports):**
    *   Sensor 1: TRIG (D9), ECHO (D8)
    *   Sensor 2: TRIG (D11), ECHO (D10) --- *Caution: Shares pins with Edge Right (D11) and Opponent Right (D10)*.

## 9. Power Requirements
*   **Input Voltage (Vin):** 8V to 25V DC.
*   **Power Terminal:** Marked VM (Positive) and GND (Negative).

## 10. Current Limits
*   **Maximum Motor Current:**
    *   **Continuous:** 10A
    *   **Peak (< 10 seconds):** 30A
*   **Logic Outputs:**
    *   +5V: 1000mA max.
    *   +3.3V: 500mA max.
    *   I/O Pin: 20mA max.

## 11. Safety Warnings
*   **Reverse Polarity:** Connecting the battery in reverse polarity will damage the board **instantaneously**.
*   **Shield Compatibility:** Avoid using Arduino shields that utilize pins D4, D5, D6, or D7, as these are internally connected to the motor driver.

## 12. What the Sample Code Does
The provided `URC10SumoRobot.ino` performs the following:
1.  **Calibration/Ready State:** While waiting for the start button, it shows edge sensor status on on-board LEDs.
2.  **Start Routine:** Upon button press, it waits 1 second, performs a 45-degree turn, moves straight for 450ms, and then scans for an opponent.
3.  **Search Logic:** If no enemy is detected, it moves in a circular motion.
4.  **Attack Logic:** If an opponent is detected by any of the 5 digital/analog sensors, the robot tracks and charges at full speed.
5.  **Edge Avoidance:** If an edge is detected by the floor sensors, it reverses, turns, and toggles the search direction to stay within the ring.
6.  **Stop:** The robot stops immediately if the button is pressed again.

## 13. Unclear or Risky Assumptions (Needs Human Review)
*   **[RISK] Sumo Rule Compliance:** Standard Sumo competitions often require a mandatory **5-second delay** after the button press. The sample code only implements a **1-second delay**.
*   **[RISK] Pin Multiplexing:** Using the secondary HC-SR04 ultrasonic port (Sensor 2) will conflict with the Right Edge and Right Opponent sensors. Needs confirmation on whether both can be used simultaneously or if they are exclusive.
*   **[ASSUMPTION] Microcontroller:** Assumed to be ATmega328P based on the IDE board selection requirement.
*   **[ASSUMPTION] Current Limit:** Peak current of 30A is assumed to be per channel, but the datasheet wording "Maximum Motor Current" could imply total for both drivers.
