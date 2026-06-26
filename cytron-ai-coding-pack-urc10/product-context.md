# Product Context — Cytron URC10 Sumo Robot Controller

## Product Purpose

The **URC10 Sumo Robot Controller** is an all-in-one board designed specifically for building **autonomous sumo robots** for robotics competitions and learning. It integrates an Arduino-compatible microcontroller with a high-current dual motor driver, making it compact and competition-ready out of the box.

---

## Target Users

- Students participating in **sumo robot competitions**
- Robotics hobbyists and makers learning **Arduino-based motor control**
- Educators running **STEM workshops** involving robot competitions
- Anyone who wants to build a compact autonomous robot with minimal external components

---

## Supported Applications

The URC10 is optimized for **sumo robotics**, but its combination of motor control, digital/analog I/O, and sensor ports makes it suitable for other applications too:

| Application | Notes |
|---|---|
| Autonomous sumo robot | Primary use case — factory sample code included |
| Line-following robot | Can use edge sensors as line sensors |
| Obstacle-avoidance robot | Uses ultrasonic or IR sensors |
| Remote-control robot | Requires adding an RF/Bluetooth receiver |
| Mini battle robot | High current motor driver suitable |

---

## Controller Type

| Property | Detail |
|---|---|
| Microcontroller | ATmega328P — the same microcontroller family used on Arduino Uno |
| Arduino Compatibility | Arduino Uno |
| Programming Language | Arduino C/C++ |
| Programming Interface | Micro USB (via CH340 USB-to-UART chip) |

---

## Major Board Features

| Feature | Detail |
|---|---|
| Motor Driver | Dual-channel, high-current (10A continuous, 30A peak **per channel**) |
| Motor Control Mode | PWM + DIR (via Cytron Motor Drivers Library) |
| Input Voltage | 8V – 25V DC |
| Logic Outputs | 5V (1000mA max), 3.3V (500mA max) |
| Onboard LEDs | 2x LEDs (active-low, D0 and D1) |
| Start Button | 1x push button (D13) |
| Sensor Ports | Front (3x), Side (2x), Edge (2x), Ultrasonic (2x HC-SR04 ports) |
| Form Factor | Arduino Uno shield compatible footprint |

> 💡 **Beginner safety note:** Even though the board supports high current (10A continuous, 30A peak per channel), beginners should always test with wheels lifted and start at low speed first. High current only flows when the motors are under load — but it is still important to test safely.

---

## Important Hardware Notes

- Motor driver pins D4, D5, D6, D7 are **internally reserved** — do not connect Arduino shields that use these pins.
- Reverse polarity on the power terminals will **permanently damage the board**.
- Always verify polarity before connecting the battery.

---

*Reference: URC10 Datasheet and User's Manual by Cytron Technologies | www.cytron.io*
