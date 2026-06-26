# Pin Map for Radio Controlled (RC) Mode — URC10

This document outlines the wiring connections and pin assignments when interfacing an RC receiver with the Cytron URC10 Sumo Robot Controller.

---

## 1. Recommended RC Receiver Mapping (Beginner)

For a basic two-channel or three-channel RC setup, we recommend the following pin assignments:

| URC10 Pin | Receiver Channel | Signal Type | Function | Notes |
|---|---|---|---|---|
| **D2** | Channel 1 (or 2) | PWM Input | **Throttle** | Controls forward and backward speed |
| **D3** | Channel 2 (or 1) | PWM Input | **Steering** | Controls left and right turning |
| **A3** | Channel 3 (or switch) | PWM/Digital Input | **Mode Switch** | Switches between RC and Autonomous mode |

> **Note on D3 Pin Conflict:**
> In autonomous sumo code, **D3** is reserved for the left opponent sensor (`OPPONENT_L`). When using D3 for RC receiver steering, you must unplug the left IR sensor or disable its usage in software.

---

## 2. Hardwired Motor Driver Pins (Strictly Reserved)

The URC10's onboard H-bridge motor driver is hardwired to the following pins. 
**Never connect receiver channel signals or any other peripherals to these pins:**

* **D4:** Motor Left (Motor 1) — Direction (DIR)
* **D5:** Motor Left (Motor 1) — Speed (PWM)
* **D6:** Motor Right (Motor 2) — Speed (PWM)
* **D7:** Motor Right (Motor 2) — Direction (DIR)

If you attempt to read RC signals from D4–D7, it will conflict with motor driver operations and could lead to uncontrolled motor rotation or microcontroller damage.

---

## 3. Serial Communication Pins (Avoided)

* **D0 (RX) and D1 (TX)** are the hardware serial pins used by the Arduino's USB-to-serial converter.
* **Avoid using D0 and D1 for RC inputs.** 
* When `Serial.begin()` is active (e.g., to print pulse values in `05-rc-receiver-test.ino`), connecting anything to D0 or D1 will interfere with USB communication. This will cause code upload failures, serial monitor corruption, and unexpected control values.

---

## 4. Summary of Available Pins for RC Extension

| Pin | Availability | Function / Conflict | Recommendation |
|---|---|---|---|
| **D0** | Avoid | Serial RX / Onboard LED1 | Do not use |
| **D1** | Avoid | Serial TX / Onboard LED0 | Do not use |
| **D2** | **Free** | None | **Recommend: Throttle Input** |
| **D3** | **Conflict** | Left Opponent IR Sensor | **Recommend: Steering Input** (Unplug IR Sensor) |
| **D4** | **Reserved** | Left Motor DIR | **DO NOT USE** |
| **D5** | **Reserved** | Left Motor PWM | **DO NOT USE** |
| **D6** | **Reserved** | Right Motor PWM | **DO NOT USE** |
| **D7** | **Reserved** | Right Motor DIR | **DO NOT USE** |
| **D8** | Available | Ultrasonic 1 ECHO | Free for sensors if needed |
| **D9** | Available | Ultrasonic 1 TRIG | Free for sensors if needed |
| **D10** | Available | Right Opponent IR Sensor | Available if right IR sensor is unplugged |
| **D11** | Available | Right Edge Sensor | Avoid if autonomous edge detection is active |
| **D12** | Available | Left Edge Sensor | Avoid if autonomous edge detection is active |
| **D13** | Available | Start/Stop Button | Avoid (has onboard pullup and button) |
| **A0** | Available | Front-Right IR Sensor | Available if front-right IR is not needed |
| **A1** | Available | Front-Center IR Sensor | Available if front-center IR is not needed |
| **A2** | Available | Front-Left IR Sensor | Available if front-left IR is not needed |
| **A3** | **Free** | None | **Recommend: Mode Switch (Digital Input)** |
| **A4** | **Free** | None | Free for general input/output |
| **A5** | **Free** | None | Free for general input/output |
