# Code Standardization Report — 1KG Autonomous Sumo Robot Starter Kit

## Summary

This report documents the creation of the Auto Kit Mode standard code
(`08-auto-kit-standard.ino`) derived from the original Cytron `URC10SumoRobot.ino`
sample, and all file changes made to align the AI Coding Pack with the D2 standard
Start Button pin.

**Decision date:** 2026-06-30
**Decision owner:** AI Coding Pack maintainer
**Scope:** Auto Kit Mode — standard code file, documentation, skill, and tester files

---

## Decision: Start Button Standard Pin = D2

| Property | Value |
|---|---|
| Standard pin | **D2** |
| Constant name | `START_BUTTON_PIN` |
| Kit reference | Official 1KG Autonomous Sumo Robot Starter Kit tutorial |
| Tutorial instruction | *"Connect the button to GPIO 2 and GND"* |
| GPIO 2 = | Digital Pin D2 on Arduino Uno / URC10 |

### Why D2

The official kit tutorial explicitly instructs users to connect the Start Button to **GPIO 2 and GND**. GPIO 2 is Digital Pin D2 on the URC10 (Arduino Uno compatible). This is the most direct and authoritative source for how the physical kit is wired.

---

## Final Standardized Pin Map

| Pin | Assignment | Status | Constant Name |
|---|---|---|---|
| D0 | LED0 (onboard) | ✅ Confirmed | `LED0_PIN` |
| D1 | LED1 (onboard) | ✅ Confirmed | `LED1_PIN` |
| **D2** | **Start Button** | ✅ **Auto Kit Mode standard** | **`START_BUTTON_PIN`** |
| D3 | Maker Object — Side Left | ✅ Confirmed | `OPPONENT_SIDE_LEFT_PIN` |
| D4 | Motor 1 DIR | ⛔ RESERVED | (motor driver) |
| D5 | Motor 1 PWM | ⛔ RESERVED | (motor driver) |
| D6 | Motor 2 PWM | ⛔ RESERVED | (motor driver) |
| D7 | Motor 2 DIR | ⛔ RESERVED | (motor driver) |
| D8 | Ultrasonic 1 ECHO | ✅ Confirmed (not used) | — |
| D9 | Ultrasonic 1 TRIG | ✅ Confirmed (not used) | — |
| D10 | Maker Object — Side Right | ✅ Confirmed | `OPPONENT_SIDE_RIGHT_PIN` |
| D11 | Maker Reflect — Right Edge | ✅ Confirmed | `EDGE_RIGHT_PIN` |
| D12 | Maker Reflect — Left Edge | ✅ Confirmed | `EDGE_LEFT_PIN` |
| D13 | Start Button | ℹ️ Legacy | (see Legacy Notes below) |
| A0 | Maker Object — Front Right | ✅ Confirmed | `OPPONENT_FRONT_RIGHT_PIN` |
| A1 | Maker Object — Front Center | ✅ Confirmed | `OPPONENT_FRONT_CENTER_PIN` |
| A2 | Maker Object — Front Left | ✅ Confirmed | `OPPONENT_FRONT_LEFT_PIN` |
| A3 | (Unassigned) | — | — |
| A4 | (Not used in Auto Kit Mode) | — | Superseded by D2 |
| A5 | (Unassigned) | — | — |

### Motor Driver Pins (unchanged)

| Motor | PWM Pin | DIR Pin |
|---|---|---|
| Motor 1 (Left) | D5 | D4 |
| Motor 2 (Right) | D6 | D7 |

---

## Standard Code Definition

All Auto Kit Mode code must use:

```cpp
#define START_BUTTON_PIN   2  // Auto Kit Mode standard — kit tutorial says GPIO 2 (D2)
                              // Legacy note: older Cytron sample code used D13
                              // If your button is wired to D13, change 2 to 13
```

Do **not** use:
```cpp
#define BUTTON  13  // ❌ Legacy — from old Cytron sample code (URC10SumoRobot.ino)
```

---

## Legacy / Variant Notes

### D13 — Old Cytron Sample Code

The original Cytron `URC10SumoRobot.ino` sample uses `#define BUTTON 13`.

**This is NOT the Auto Kit Mode standard**, because the kit tutorial tells users to wire the button to GPIO 2 (D2), not D13.

However, if a user already wired their button to D13 following the old sample code, their hardware is still valid. They only need to change one line:

```cpp
// Change:
#define START_BUTTON_PIN   2

// To:
#define START_BUTTON_PIN  13
```

No other code changes are needed. All button reads use `START_BUTTON_PIN`.

### A4 — Superseded

A4 was used as the standard in a previous AI Coding Pack session. It has been superseded by D2, which is directly cited in the official kit tutorial. A4 is no longer a recognized standard for Auto Kit Mode.

---

## What Changed in the Standard Code (from Original URC10SumoRobot.ino)

| Item | Original | Standard (`08-auto-kit-standard.ino`) |
|---|---|---|
| Button pin | D13 (`#define BUTTON 13`) | D2 (`#define START_BUTTON_PIN 2`) |
| Constant name | `BUTTON` | `START_BUTTON_PIN` |
| Speed values | Raw numbers (`255`, `150`, `100`) | Named constants (`ATTACK_SPEED`, etc.) |
| Timing values | Raw numbers (`200`, `450`, `180`) | Named constants (`START_DELAY_MS`, etc.) |
| Function: wait for button | Inline in `setup()` | `waitForStartButton()` |
| Function: start sequence | `startRoutine()` | `startRoutine()` (cleaned) |
| Function: edge recovery | `backoff(dir)` | `handleEdge(dir)` |
| Function: search | `search()` | `searchOpponent()` |
| Function: attack | `attack()` | `attackOpponent()` |
| Stop motors | Inline `setSpeed(0)` | `stopMotors()` helper |
| Active-low comments | None | Every sensor and button documented |
| Safety warnings | None | Battery polarity, lift wheels, first test |
| Serial Monitor | Not used | Not used (same — D0/D1 conflict noted) |
| LED calibration | In setup() loop | In `waitForStartButton()` |
| Typo: `-0` speed | `motorL.setSpeed(-0)` | Fixed to `0` |
| Default speed | 255 (full speed) | Beginner-safe defaults (200 attack, 90 search) |
| Beginner tip | None | Included in comments and notes file |

---

## Files Created

| File | Description |
|---|---|
| `auto-kit-mode/code-examples/08-auto-kit-standard.ino` | New canonical Auto Kit Mode code |
| `auto-kit-mode/auto-kit-standard-code-notes.md` | Companion notes: changes, D2 reasoning, tuning, testing, motor direction fix, D13 migration |
| `auto-kit-mode/code-standardization-report.md` | This report |

---

## Files Updated

| File | Change |
|---|---|
| `auto-kit-mode/auto-kit-sensor-map.md` | D2 = ✅ Auto Kit Mode standard. D13 = ℹ️ Legacy. A4 = superseded |
| `.agents/skills/cytron-ai-coding-coach/SKILL.md` | Instruction 15: D2 is standard. Pin table: D2 added, D13 = legacy, A4 removed |
| `TESTER-GUIDE.md` | B4: check D2 used by default. B5: D13 remap help. B6: D2 vs D13 explanation |
| `FEEDBACK-FORM.md` | Q7: D2 used by default. Q8: D13 legacy note present. Q9: D13 remap help correct |

---

## Files NOT Changed

| File | Reason |
|---|---|
| `source-docs/URC10SumoRobot.ino` | Original Cytron sample — preserved as legacy reference, not modified |
| `code-examples/01-motor-test.ino` | Uses `START_BUTTON_PIN A4` from previous session — separate from Auto Kit Mode code examples |
| `code-examples/02-sensor-test.ino` | Same as above |
| `code-examples/03-basic-sumo-behavior.ino` | Same as above |
| `code-examples/04-application-extension.ino` | Same as above |
| `rc-mode/` (all files) | RC Mode is not affected |
| Motor driver pins (D4, D5, D6, D7) | Unchanged |
| Sensor pins (D3, D10, D11, D12, A0, A1, A2) | Unchanged |

---

## Validation Checklist

### New Code File
- [ ] `08-auto-kit-standard.ino` exists in `auto-kit-mode/code-examples/`
- [ ] Uses `#define START_BUTTON_PIN 2` (not `BUTTON 13`, not `A4`)
- [ ] Includes 3-line legacy variant comment on `START_BUTTON_PIN`
- [ ] Uses named constants for all speeds and timings
- [ ] Functions named: `waitForStartButton`, `startRoutine`, `searchOpponent`, `attackOpponent`, `handleEdge`, `stopMotors`
- [ ] `INPUT_PULLUP` on all sensor and button pins
- [ ] Active-low comments on every sensor and button
- [ ] Safety warnings: battery polarity + lift wheels
- [ ] No `Serial.begin()` — D0/D1 LED conflict noted in comments
- [ ] Motor pins: Left = D5/D4, Right = D6/D7 (unchanged)

### Sensor Pin Constants
- [ ] `START_BUTTON_PIN` = 2 (D2)
- [ ] `EDGE_LEFT_PIN` = 12
- [ ] `EDGE_RIGHT_PIN` = 11
- [ ] `OPPONENT_SIDE_LEFT_PIN` = 3
- [ ] `OPPONENT_SIDE_RIGHT_PIN` = 10
- [ ] `OPPONENT_FRONT_RIGHT_PIN` = A0
- [ ] `OPPONENT_FRONT_CENTER_PIN` = A1
- [ ] `OPPONENT_FRONT_LEFT_PIN` = A2

### Tuning Constants
- [ ] `SEARCH_SPEED` defined
- [ ] `ATTACK_SPEED` defined (beginner-safe value, not 255)
- [ ] `TURN_SPEED` defined
- [ ] `BACKOFF_SPEED` defined
- [ ] `START_DELAY_MS` defined
- [ ] `BACKOFF_DELAY_MS` defined

### Documentation Files
- [ ] `auto-kit-sensor-map.md`: D2 row = ✅ Auto Kit Mode standard
- [ ] `auto-kit-sensor-map.md`: D13 row = ℹ️ Legacy
- [ ] `auto-kit-sensor-map.md`: A4 row = superseded

### Skill and Testing Files
- [ ] `SKILL.md` Instruction 15: D2 is the standard, D13 is legacy
- [ ] `SKILL.md` pin table: D2 row present, A4 row removed
- [ ] `TESTER-GUIDE.md` B4: checks D2 used by default
- [ ] `TESTER-GUIDE.md` B5: checks D13 remap help
- [ ] `FEEDBACK-FORM.md` Q7: asks whether D2 was used by default
- [ ] `FEEDBACK-FORM.md` Q8: asks whether D13 legacy note comment was present
- [ ] `FEEDBACK-FORM.md` Q9: asks whether D13 remap help was correct

### Non-Regression
- [ ] `rc-mode/` files are unchanged
- [ ] `source-docs/URC10SumoRobot.ino` is unchanged
- [ ] Motor driver pins (D4, D5, D6, D7) are unchanged in all code files
- [ ] Sensor pins (D3, D10, D11, D12, A0, A1, A2) are unchanged in all code files
