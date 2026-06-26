# Pin Map — Cytron URC10 Sumo Robot Controller

This table lists all known pin assignments for the URC10 as defined in the source documents and sample code.

> **Note:** Pin assignments are fixed by the board's internal wiring. Do not reassign motor driver pins (D4–D7) in your sketch.

---

## Motor Driver Pins (Internally Reserved)

These pins are **hardwired** to the onboard dual motor driver. Do not use them for sensors, LEDs, or other peripherals.

| Pin | Function | Direction | Notes |
|---|---|---|---|
| D4 | Motor Left — DIR | Output | Direction signal for left motor |
| D5 | Motor Left — PWM | Output | Speed signal for left motor |
| D6 | Motor Right — PWM | Output | Speed signal for right motor |
| D7 | Motor Right — DIR | Output | Direction signal for right motor |

---

## Digital Sensor Pins

| Arduino Pin | Defined As | Function | Input Mode |
|---|---|---|---|
| D3 | `OPPONENT_L` | Left opponent/IR sensor | `INPUT_PULLUP` (active-low) |
| D10 | `OPPONENT_R` | Right opponent/IR sensor | `INPUT_PULLUP` (active-low) |
| D11 | `EDGE_R` | Right edge/line sensor | `INPUT_PULLUP` (active-low) |
| D12 | `EDGE_L` | Left edge/line sensor | `INPUT_PULLUP` (active-low) |
| D13 | `BUTTON` | Start button | `INPUT_PULLUP` (active-low) |

---

## Analog / Front Opponent Sensor Pins

| Arduino Pin | Defined As | Function | Input Mode |
|---|---|---|---|
| A0 | `OPPONENT_FR` | Front-right opponent/IR sensor | `INPUT_PULLUP` (active-low) |
| A1 | `OPPONENT_FC` | Front-center opponent/IR sensor | `INPUT_PULLUP` (active-low) |
| A2 | `OPPONENT_FL` | Front-left opponent/IR sensor | `INPUT_PULLUP` (active-low) |

> **Note:** These analog pins (A0–A2) are used as **digital inputs** in the sample code via `digitalRead()`.

---

## Onboard LED Pins

| Arduino Pin | Defined As | Function | Notes |
|---|---|---|---|
| D0 | `LED0` | Onboard LED 0 | **Active-low** (write HIGH = OFF, LOW = ON) |
| D1 | `LED1` | Onboard LED 1 | **Active-low** (write HIGH = OFF, LOW = ON) |

> ⚠️ **D0 and D1 are the Serial TX/RX pins.**
> - D0 (LED0) = TX (transmit)
> - D1 (LED1) = RX (receive)
>
> **Avoid controlling D0/D1 as normal `OUTPUT` pins when `Serial.begin()` is active.** Writing to them as GPIO outputs while the Serial library is running causes:
> - Garbled or missing Serial Monitor output
> - Potential signal corruption
> - Confusing debugging experience for beginners
>
> The LED mirroring code (used in `setup()` to show edge sensor state) works correctly because it runs **before** `Serial.begin()` is called in the sumo behavior sketches. In `02-sensor-test.ino`, LED output on D0/D1 is intentionally disabled because that sketch uses `Serial.begin(9600)`.

---

## Ultrasonic Sensor Ports (HC-SR04)

| Port | TRIG Pin | ECHO Pin | Conflict Warning |
|---|---|---|---|
| Ultrasonic 1 | D9 | D8 | No conflict |
| Ultrasonic 2 | D11 | D10 | ⚠️ Conflicts with EDGE_R (D11) and OPPONENT_R (D10) |

> **Important:** Ultrasonic Sensor 2 **shares pins** with the right edge sensor and right opponent sensor. Do not use both at the same time without hardware/software remap.

---

## Summary — Quick Reference

| Pin | Reserved / Used As |
|---|---|
| D0 | LED0 (active-low) — also TX Serial |
| D1 | LED1 (active-low) — also RX Serial |
| D3 | OPPONENT_L (left IR sensor) |
| D4 | Motor Left DIR (**internally reserved**) |
| D5 | Motor Left PWM (**internally reserved**) |
| D6 | Motor Right PWM (**internally reserved**) |
| D7 | Motor Right DIR (**internally reserved**) |
| D8 | Ultrasonic 1 ECHO |
| D9 | Ultrasonic 1 TRIG |
| D10 | OPPONENT_R / Ultrasonic 2 ECHO |
| D11 | EDGE_R / Ultrasonic 2 TRIG |
| D12 | EDGE_L |
| D13 | BUTTON (start) |
| A0 | OPPONENT_FR |
| A1 | OPPONENT_FC |
| A2 | OPPONENT_FL |
