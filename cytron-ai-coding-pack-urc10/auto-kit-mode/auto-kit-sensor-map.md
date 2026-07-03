# Auto-Kit Sensor Map — 1KG Autonomous Sumo Robot Starter Kit using URC10

## Overview

This file documents the pin assignments for all sensors in the 1KG Autonomous Sumo Robot Starter Kit. All pins listed are **confirmed** for this AI Coding Pack. D2 is used for the **IR Sumo Start Module** signal input — the primary start method for Auto Kit Mode.

> ℹ️ **AI Coach Rule:** For Auto Kit Mode, the default start method is the **IR Sumo Start Module on D2**. Use `INPUT` mode (not `INPUT_PULLUP`) for D2 — the module drives the output. A physical button on D2 is the legacy fallback only.

---

## IR Sumo Start Module — Signal Input: D2

The standard Auto Kit Mode start method is the **Cytron IR Sumo Start Module** connected to **D2**.
The module replaces the physical start button, enabling wireless synchronized start and stop control during competitions.

| Standard | Pin | Mode | Reason |
|---|---|---|---|
| **Auto Kit Mode standard** | **D2** | `INPUT` (not INPUT_PULLUP) | IR Sumo Start module drives the signal actively; kit tutorial references GPIO 2 |

> ✅ **Status: Confirmed — D2 (IR Sumo Start) is the Auto Kit Mode standard for this AI Coding Pack**

### Signal Logic

| Signal Level | Meaning | Robot Action |
|---|---|---|
| **HIGH** | RUN — judge sent start, match in progress | Robot may move |
| **LOW** | READY / STOP — judge sent stop, or no signal | Robot must stay stopped immediately |

**Pin mode:** Use `INPUT` (not `INPUT_PULLUP`). The IR Sumo Start module actively drives the D2 line. An internal pullup would interfere with the driven output.

### Wiring

| IR Sumo Start Terminal | URC10 Connection |
|---|---|
| + (Power) | 5V |
| − (Ground) | GND |
| S (Signal) | D2 |

All generated code for Auto Kit Mode must use:
```cpp
const uint8_t IR_SUMO_START_PIN = 2;  // IR Sumo Start module signal input
                                       // HIGH = RUN, LOW = STOP/READY
                                       // Use INPUT mode — module drives the output actively
```

### Legacy / Fallback Notes

A physical button on D2 may be used as a fallback if the IR Sumo Start module is not available.
In that case, change the pin mode to `INPUT_PULLUP` and invert the logic (pressed = LOW = start).

| Source | Pin | Notes |
|---|---|---|
| IR Sumo Start Module (current standard) | D2 | `INPUT` mode. HIGH = RUN, LOW = STOP |
| Physical button fallback | D2 | `INPUT_PULLUP` mode. LOW = pressed = start |
| Cytron original sample code | D13 | Legacy — `#define BUTTON 13`, valid if wired there |

If a user reports the IR signal does not work, the AI Coach should ask:
*"Is the IR Sumo Start module wired to D2? Is the S terminal connected to D2, not GND?"*

---

## Sensor Pin Map

### Opponent Detection (Maker Object Sensors — ×5)

The kit uses 5 Maker Object IR sensors to detect the opponent robot from multiple angles.

| Sensor Position | Pin | Status | Notes |
|---|---|---|---|
| Front Left | **A2** | ✅ Confirmed (source audit) | Analog pin used as digital input |
| Front Center | **A1** | ✅ Confirmed (source audit) | Analog pin used as digital input |
| Front Right | **A0** | ✅ Confirmed (source audit) | Analog pin used as digital input |
| Side Left | **D3** | ✅ Confirmed (source audit) | Digital input |
| Side Right | **D10** | ✅ Confirmed (source audit) | ⚠️ Shares pin with Ultrasonic Sensor 2 ECHO — do not use both simultaneously |

**Sensor logic:** Maker Object sensors output **LOW** when an object is detected (active-low). Use `INPUT_PULLUP` in code.

---

### Edge Detection (Maker Reflect Sensors — ×2)

The kit uses 2 Maker Reflect IR reflectance sensors to detect the white boundary line of the sumo ring.

| Sensor Position | Pin | Status | Notes |
|---|---|---|---|
| Left Edge | **D12** | ✅ Confirmed (source audit) | Reads floor reflection. LOW = white line (edge detected) |
| Right Edge | **D11** | ✅ Confirmed (source audit) | ⚠️ Shares pin with Ultrasonic Sensor 2 TRIG — do not use both simultaneously |

**Sensor logic:** Maker Reflect sensors output **LOW** when detecting the white edge line (high reflectance). Use `INPUT_PULLUP` in code.

> ℹ️ **Installation reminder:** Both Maker Reflect sensors must be installed on the **underside** of the chassis, facing the floor. They cannot detect the ring edge if mounted on the top or side.

---

### Start Input (IR Sumo Start Module)

| Component | Pin | Mode | Status | Notes |
|---|---|---|---|---|
| IR Sumo Start Signal | **D2** | `INPUT` | ✅ **Auto Kit Mode standard** | HIGH = RUN, LOW = STOP. Module drives output actively |

**Signal logic:** `INPUT` mode (no pullup). HIGH = RUN. LOW = STOP or no signal. Motors must stop immediately on LOW.

---

### Motor Driver (Reserved — Do Not Reassign)

These pins are hardwired to the onboard motor driver. They cannot be used for sensors, LEDs, buttons, or any other purpose.

| Pin | Role | Motor |
|---|---|---|
| **D4** | DIR (direction) | Motor 1 — Left |
| **D5** | PWM (speed) | Motor 1 — Left |
| **D6** | PWM (speed) | Motor 2 — Right |
| **D7** | DIR (direction) | Motor 2 — Right |

> ⛔ **Never** connect any sensor, button, or peripheral to D4, D5, D6, or D7. These are permanently occupied by the motor driver hardware.

---

### On-Board LEDs

| Pin | Label | Notes |
|---|---|---|
| **D0** | LED0 | Active-low: LOW = ON, HIGH = OFF. Also TX — avoid using Serial if this LED is in use |
| **D1** | LED1 | Active-low: LOW = ON, HIGH = OFF. Also RX — avoid using Serial if this LED is in use |

---

### Ultrasonic Sensor Ports (Optional — Not Used in Basic Kit)

The URC10 has two HC-SR04 ports. These are not used by the standard 1KG Autonomous Kit configuration. They are listed here to avoid accidental pin conflicts.

| Sensor | Pin | Conflict |
|---|---|---|
| Ultrasonic 1 TRIG | D9 | ✅ No conflict |
| Ultrasonic 1 ECHO | D8 | ✅ No conflict |
| Ultrasonic 2 TRIG | D11 | ⚠️ Shares pin with Right Edge sensor (D11) |
| Ultrasonic 2 ECHO | D10 | ⚠️ Shares pin with Side Right opponent sensor (D10) |

---

## Summary: Pin Assignment Status

| Pin | Assignment | Status |
|---|---|---|
| D0 | LED0 (onboard) | ✅ Confirmed |
| D1 | LED1 (onboard) | ✅ Confirmed |
| D2 | IR Sumo Start Signal (`IR_SUMO_START_PIN`) | ✅ **Auto Kit Mode standard** — `INPUT` mode, HIGH=RUN LOW=STOP |
| D3 | Maker Object — Side Left | ✅ Confirmed |
| D4 | Motor 1 DIR (RESERVED) | ✅ Confirmed |
| D5 | Motor 1 PWM (RESERVED) | ✅ Confirmed |
| D6 | Motor 2 PWM (RESERVED) | ✅ Confirmed |
| D7 | Motor 2 DIR (RESERVED) | ✅ Confirmed |
| D8 | Ultrasonic 1 ECHO | ✅ Confirmed (not used in kit) |
| D9 | Ultrasonic 1 TRIG | ✅ Confirmed (not used in kit) |
| D10 | Maker Object — Side Right | ✅ Confirmed (⚠️ shared with Ultrasonic 2 ECHO) |
| D11 | Maker Reflect — Right Edge | ✅ Confirmed (⚠️ shared with Ultrasonic 2 TRIG) |
| D12 | Maker Reflect — Left Edge | ✅ Confirmed |
| D13 | Start Button | ℹ️ Legacy — old Cytron sample code; valid if physically wired there |
| A0 | Maker Object — Front Right | ✅ Confirmed |
| A1 | Maker Object — Front Center | ✅ Confirmed |
| A2 | Maker Object — Front Left | ✅ Confirmed |
| A3 | (Not assigned in kit) | — |
| A4 | (Not used in Auto Kit Mode) | — Superseded by D2 standard |
| A5 | (Not assigned in kit) | — |

---

## AI Coach Instruction

When a user asks to write or modify autonomous code for this kit:

1. **Use D2 with the IR Sumo Start module** as the default start method for Auto Kit Mode
2. **Use `INPUT` mode for D2** (not `INPUT_PULLUP`) — the module drives the output actively
3. **Use `IR_SUMO_START_PIN` constant** (not `START_BUTTON_PIN`) in all Auto Kit Mode code
4. **Signal logic:** HIGH = RUN (robot moves), LOW = STOP (motors must halt immediately)
5. **Flag pin conflicts** — if the user requests D10 or D11 with ultrasonic sensors, warn them of the conflict
6. **Never use** D4, D5, D6, D7 for anything other than motor control
7. **If the user reports the IR signal does not work**, walk through the wiring check: `+` to 5V, `-` to GND, `S` to D2
