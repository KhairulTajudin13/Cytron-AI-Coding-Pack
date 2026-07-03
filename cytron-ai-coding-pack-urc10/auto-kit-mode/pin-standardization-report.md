# Pin Standardization Report — 1KG Autonomous Sumo Robot Starter Kit using URC10

## Summary

This report documents the decision to standardize the Start Button pin for Autonomous Kit Mode to **A4**, and all files changed as part of that decision.

**Decision date:** 2026-06-30
**Decision owner:** AI Coding Pack maintainer
**Scope:** Autonomous Kit Mode only — Basic URC10 and RC Mode files are not affected

---

## Decision

**Start Button pin for Autonomous Kit Mode: A4**

| Property | Value |
|---|---|
| Standard pin | **A4** |
| Constant name | `START_BUTTON_PIN` |
| Kit reference | 1KG Autonomous Sumo Robot Starter Kit assembly and wiring guide |
| Reason | The kit assembly wiring guide specifies A4 as the button connection point |

### Reason for Choosing A4

The 1KG Autonomous Sumo Robot Starter Kit assembly guide instructs users to wire the Start Button to **A4**. Since this AI Coding Pack is designed specifically to support kit users following the kit assembly guide, A4 is the most appropriate default.

D13 (from the legacy Cytron sample code `URC10SumoRobot.ino`) and D2 (from some tutorial assembly step references) are documented as legacy alternatives, not as the standard.

---

## Final Standardized Pin Map

| Pin | Assignment | Status | Notes |
|---|---|---|---|
| D0 | LED0 (onboard) | ✅ Confirmed | Active-low |
| D1 | LED1 (onboard) | ✅ Confirmed | Active-low |
| D2 | Start Button | ℹ️ Legacy | Some tutorial versions reference D2. Valid if physically wired there |
| D3 | OPPONENT_L — Side Left Maker Object | ✅ Confirmed | Active-low, INPUT_PULLUP |
| D4 | Motor 1 DIR | ⛔ RESERVED | Motor driver — do not reassign |
| D5 | Motor 1 PWM | ⛔ RESERVED | Motor driver — do not reassign |
| D6 | Motor 2 PWM | ⛔ RESERVED | Motor driver — do not reassign |
| D7 | Motor 2 DIR | ⛔ RESERVED | Motor driver — do not reassign |
| D8 | Ultrasonic 1 ECHO | ✅ Confirmed | Not used in kit |
| D9 | Ultrasonic 1 TRIG | ✅ Confirmed | Not used in kit |
| D10 | OPPONENT_R — Side Right Maker Object | ✅ Confirmed | ⚠️ Shared with Ultrasonic 2 ECHO |
| D11 | EDGE_R — Right Maker Reflect | ✅ Confirmed | ⚠️ Shared with Ultrasonic 2 TRIG |
| D12 | EDGE_L — Left Maker Reflect | ✅ Confirmed | Active-low |
| D13 | Start Button | ℹ️ Legacy | Original Cytron sample code pin. Valid if physically wired there |
| A0 | OPPONENT_FR — Front Right Maker Object | ✅ Confirmed | Active-low |
| A1 | OPPONENT_FC — Front Center Maker Object | ✅ Confirmed | Active-low |
| A2 | OPPONENT_FL — Front Left Maker Object | ✅ Confirmed | Active-low |
| A3 | (Unassigned) | — | Available for custom use |
| **A4** | **START_BUTTON_PIN — Start Button** | ✅ **AI Coding Pack standard** | **Active-low, INPUT_PULLUP. Kit wiring guide standard** |
| A5 | (Unassigned) | — | Available for custom use |

### Motor Driver Pins (unchanged)

| Motor | PWM Pin | DIR Pin |
|---|---|---|
| Motor 1 (Left) | D5 | D4 |
| Motor 2 (Right) | D6 | D7 |

---

## Standard Code Constant

All code in this AI Coding Pack must use this definition for the Start Button:

```cpp
#define START_BUTTON_PIN  A4  // Matches the 1KG Autonomous Sumo Robot Starter Kit wiring guide
                              // Legacy note: older sample code used D13; some tutorials reference D2
                              // If your button is wired to D13 or D2, change A4 to match
```

Do **not** use:
```cpp
#define BUTTON  13  // ❌ Legacy — do not use in new code for this kit
```

---

## Legacy / Variant Notes

These pins are documented as alternatives. They are **not** the AI Coding Pack standard but are valid if the user's hardware is physically wired to them.

| Pin | Source | Note |
|---|---|---|
| **D13** | Cytron official sample code (`URC10SumoRobot.ino`) | Original sample code uses `#define BUTTON 13`. If a user followed the original Cytron code and wired the button to D13, this still works — they only need to change `START_BUTTON_PIN A4` to `START_BUTTON_PIN 13` |
| **D2** | Some tutorial assembly versions | Some versions of the Cytron tutorial assembly guide reference "GPIO 2" for the button connection. Valid if wired this way |

### How to Support Legacy Users

If a user reports the Start Button does not work, ask:
> *"Is your button physically wired to A4, D13, or D2? Please check the wire from the button connector to the URC10 board."*

Then change the constant to match:
```cpp
// If wired to D13:
#define START_BUTTON_PIN  13  // Legacy — wired to D13 instead of kit standard A4

// If wired to D2:
#define START_BUTTON_PIN  2   // Legacy — wired to D2 instead of kit standard A4
```

---

## Files Changed

### New File Created
| File | Change |
|---|---|
| `auto-kit-mode/05-autonomous-kit-standard.ino` | **New** — Canonical autonomous kit code using `START_BUTTON_PIN A4`, all 5 opponent sensors, and full kit pin layout |

### Code Examples Updated
| File | Change |
|---|---|
| `code-examples/01-motor-test.ino` | `#define BUTTON 13` → `#define START_BUTTON_PIN A4`. All uses updated |
| `code-examples/02-sensor-test.ino` | `#define BUTTON 13` → `#define START_BUTTON_PIN A4`. Serial label updated |
| `code-examples/03-basic-sumo-behavior.ino` | `#define BUTTON 13` → `#define START_BUTTON_PIN A4`. All uses updated |
| `code-examples/04-application-extension.ino` | `#define BUTTON 13` → `#define START_BUTTON_PIN A4`. All uses updated |

### Auto-Kit Documentation Updated
| File | Change |
|---|---|
| `auto-kit-mode/auto-kit-sensor-map.md` | Removed "Needs verification". A4 is now ✅ Confirmed standard. D13 and D2 moved to Legacy notes |
| `auto-kit-mode/auto-kit-context.md` | Conflict section replaced with "Resolved: A4 standard" section |
| `auto-kit-mode/auto-kit-assembly-notes.md` | Step 10 note updated. Step 12 rewritten: A4 is the standard, D13/D2 are legacy notes |
| `auto-kit-mode/auto-kit-troubleshooting.md` | Problem 6 Cause A rewritten: A4 is the fix, D13 is the legacy code to replace |

### Skill and Testing Files Updated
| File | Change |
|---|---|
| `.agents/skills/cytron-ai-coding-coach/SKILL.md` | Instruction 15 rewritten: A4 is the standard, no longer requires asking user before generating code. Pin reference table updated with A4 |
| `TESTER-GUIDE.md` | B4, B5, B6 tests rewritten: B4 checks A4 is used by default; B5 tests legacy remap scenario; B6 tests standard vs legacy explanation |
| `FEEDBACK-FORM.md` | Q7, Q8, Q9 rewritten: Q7 checks A4 used by default; Q8 checks variant note comment; Q9 checks legacy remap help |

### Files NOT Changed (as required)
| File | Reason |
|---|---|
| `rc-mode/` (all files) | RC Mode does not use a Start Button pin — not affected |
| `source-docs/URC10SumoRobot.ino` | Original Cytron sample code — preserved as legacy reference, not modified |
| `pin-map.md` (root) | General URC10 board reference — not specific to kit mode |
| `safety-rules.md` (root) | General board safety — not specific to kit mode |

---

## Validation Checklist

Use this checklist to verify the standardization is complete:

### Code Files
- [ ] `01-motor-test.ino` uses `START_BUTTON_PIN A4` (not `BUTTON 13`)
- [ ] `02-sensor-test.ino` uses `START_BUTTON_PIN A4` and Serial label shows `(A4)`
- [ ] `03-basic-sumo-behavior.ino` uses `START_BUTTON_PIN A4` in all 4 locations
- [ ] `04-application-extension.ino` uses `START_BUTTON_PIN A4` in all 5 locations
- [ ] `05-autonomous-kit-standard.ino` exists and uses `START_BUTTON_PIN A4`
- [ ] All 4 code examples include the 3-line variant note comment on `START_BUTTON_PIN`
- [ ] No code file uses `#define BUTTON 13` (without the legacy note)

### Documentation Files
- [ ] `auto-kit-sensor-map.md`: A4 row is ✅ Confirmed; D13 and D2 rows are ℹ️ Legacy
- [ ] `auto-kit-sensor-map.md`: No pin is marked "Needs verification"
- [ ] `auto-kit-context.md`: No conflict warning — resolved section present
- [ ] `auto-kit-assembly-notes.md`: Step 12 shows A4 as standard; D13/D2 as legacy
- [ ] `auto-kit-troubleshooting.md`: Problem 6 instructs user to use A4 / replace D13

### Skill and Testing Files
- [ ] `SKILL.md` Instruction 15: A4 is default — no requirement to ask user before generating code
- [ ] `SKILL.md` pin table: D13 labeled "Legacy", A4 row added as "Autonomous Kit Mode standard"
- [ ] `TESTER-GUIDE.md` B4: Test checks A4 used by default (not D13)
- [ ] `TESTER-GUIDE.md` B5: Test checks legacy remap help (D13 → accepted as valid)
- [ ] `FEEDBACK-FORM.md` Q7: Asks whether A4 was used by default
- [ ] `FEEDBACK-FORM.md` Q8: Asks whether legacy variant note comment was included
- [ ] `FEEDBACK-FORM.md` Q9: Asks whether legacy remap help was provided

### Non-Regression
- [ ] RC Mode files are unchanged
- [ ] Root `pin-map.md` is unchanged
- [ ] Motor driver pins (D4, D5, D6, D7) are unchanged in all files
- [ ] Sensor pins (D3, D10, D11, D12, A0, A1, A2) are unchanged in all files
