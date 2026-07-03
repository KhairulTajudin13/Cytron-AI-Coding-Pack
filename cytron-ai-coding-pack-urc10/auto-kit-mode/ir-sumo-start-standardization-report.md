# IR Sumo Start Standardization Report
## Auto Kit Mode — 1KG Autonomous Sumo Robot Starter Kit using URC10

**Decision date:** 2026-06-30
**Scope:** Auto Kit Mode standard code, documentation, skill, and testing files

---

## Final Auto Kit Mode Start Method

| Property | Value |
|---|---|
| Start method | **IR Sumo Start Module** |
| Pin | **D2** (`IR_SUMO_START_PIN = 2`) |
| Pin mode | **`INPUT`** (not `INPUT_PULLUP`) |
| Module product | Cytron IR-SUMO-START |
| Product page | https://my.cytron.io/p-ir-sumo-start-module |

### Signal Logic

| D2 Level | State | Robot Action |
|---|---|---|
| **HIGH** | **RUN** | Robot is permitted to move |
| **LOW** | **READY / STOP** | Robot must stop motors immediately |

LOW is the fail-safe state. If the IR signal is lost or the module is not powered, D2 defaults LOW — the robot stays stopped.

---

## Final Auto Kit Mode Pin Map

| Pin | Assignment | Mode | Notes |
|---|---|---|---|
| D0 | LED0 (onboard) | Output | Active-low. Also TX — no Serial.begin() |
| D1 | LED1 (onboard) | Output | Active-low. Also RX — no Serial.begin() |
| **D2** | **IR Sumo Start Signal** | `INPUT` | **Auto Kit Mode standard.** HIGH=RUN, LOW=STOP |
| D3 | Maker Object — Side Left | `INPUT_PULLUP` | Active-low |
| D4 | Motor 1 DIR | RESERVED | Do not reassign |
| D5 | Motor 1 PWM | RESERVED | Do not reassign |
| D6 | Motor 2 PWM | RESERVED | Do not reassign |
| D7 | Motor 2 DIR | RESERVED | Do not reassign |
| D8 | Ultrasonic 1 ECHO | — | Not used in kit |
| D9 | Ultrasonic 1 TRIG | — | Not used in kit |
| D10 | Maker Object — Side Right | `INPUT_PULLUP` | Active-low |
| D11 | Maker Reflect — Right Edge | `INPUT_PULLUP` | Active-low |
| D12 | Maker Reflect — Left Edge | `INPUT_PULLUP` | Active-low |
| D13 | Physical button (legacy only) | — | Not used in IR Sumo Start standard |
| A0 | Maker Object — Front Right | `INPUT_PULLUP` | Active-low |
| A1 | Maker Object — Front Center | `INPUT_PULLUP` | Active-low |
| A2 | Maker Object — Front Left | `INPUT_PULLUP` | Active-low |

### Motor Driver Pins (Unchanged)

| Motor | PWM | DIR |
|---|---|---|
| Left (M1) | D5 | D4 |
| Right (M2) | D6 | D7 |

---

## D2 Pin Usage — Mode-Specific Note

D2 has different roles depending on which code is loaded:

| Mode | D2 Role | Pin Mode | Code File |
|---|---|---|---|
| **Auto Kit Mode** | IR Sumo Start signal | `INPUT` | `08-auto-kit-standard.ino` |
| **RC Mode** | RC throttle pulse input | Digital read | `06-radio-controlled-drive.ino` |
| **Hybrid Mode** | Confirm with user before generating code | — | `07-hybrid-rc-autonomous-mode.ino` |

> ⚠️ **These modes are mutually exclusive.** Never mix D2 roles. If a user is in Hybrid Mode, ask them to confirm the D2 pin assignment before generating code.

---

## Files Created

| File | Description |
|---|---|
| `auto-kit-mode/code-examples/08-auto-kit-standard.ino` | Standard Auto Kit match code. Refactored with `setupPins()`, `checkIRStopSignal()`, `edgeLeftDetected()`, `edgeRightDetected()`, `anyOpponentDetected()`, `waitForIRStartSignal()` (calls `stopMotors()` first), and `irRunSignalActive()`. Priority-0 STOP check at top of `loop()`. |
| `auto-kit-mode/code-examples/09-ir-sumo-start-test.ino` | Safe IR Sumo Start signal test. No motor commands. D13 LED = ON when RUN (HIGH), OFF when STOP (LOW). Test before running match code. |
| `auto-kit-mode/ir-sumo-start-integration.md` | Full integration guide: what the module is, why it replaces the button, wiring, signal logic, code explanation, mounting, test procedure, fallback instructions, quick troubleshooting reference. |
| `auto-kit-mode/ir-sumo-start-validation-checklist.md` | 14-section validation checklist covering code, documentation, and non-regression checks. |
| `auto-kit-mode/ir-sumo-start-standardization-report.md` | This report. |

---

## Files Updated

| File | Change Summary |
|---|---|
| `auto-kit-mode/auto-kit-sensor-map.md` | D2 section rewritten for IR Sumo Start. Signal logic table, wiring table, INPUT mode requirement, fallback notes. AI Coach rules updated to use IR Sumo Start by default. |
| `auto-kit-mode/auto-kit-assembly-notes.md` | Step 12 rewritten: IR Sumo Start wiring (+ − S), signal logic table, INPUT mode note. New Step 12b: mounting guidance, line-of-sight requirement. |
| `auto-kit-mode/auto-kit-safety-rules.md` | Rule 8 added: IR Sumo Start safety, wireless stop, synchronized start, STOP check must not be bypassed, mounting requirement. Checklist updated. |
| `auto-kit-mode/auto-kit-troubleshooting.md` | Problems 7–10 added: robot never starts; starts then immediately stops; LED changes but robot doesn't move; robot ignores STOP. Quick Diagnosis Flow expanded. |
| `.agents/skills/cytron-ai-coding-coach/SKILL.md` | Instruction 15 rewritten: IR Sumo Start is the default, `irRunSignalActive()` and `checkIRStopSignal()` templates, physical button as legacy, wiring snippet, troubleshooting walk-through. |
| `TESTER-GUIDE.md` | B4/B5/B6 updated for IR Sumo Start. New Section F added (5 IR Sumo Start test cases). Critical tests and checklist updated. |
| `FEEDBACK-FORM.md` | Part 3 rewritten with 7 IR Sumo Start questions (Q7–Q13): module recognition, D2 usage, HIGH=RUN, LOW=STOP, INPUT mode, STOP behavior, RC Mode separation. |

---

## Files NOT Changed

| File | Reason |
|---|---|
| `source-docs/URC10SumoRobot.ino` | Preserved as legacy reference |
| `rc-mode/` (all files) | RC Mode is independent — D2 role is separate |
| `code-examples/01–05-*.ino` | Not Auto Kit Mode match code — separate purpose |
| All motor driver pins (D4, D5, D6, D7) | Unchanged by design |
| All sensor pins (D3, D10, D11, D12, A0, A1, A2) | Unchanged by design |

---

## Legacy Physical Button Note

The physical start button (previously wired to D2 or D13) is now **legacy / optional fallback only**.

If a user does not have an IR Sumo Start module and needs to test bench logic:

```cpp
// FALLBACK: Physical button on D2 — bench testing only
// Change pin mode:
pinMode(IR_SUMO_START_PIN, INPUT_PULLUP);  // Button: not pressed = HIGH, pressed = LOW

// Invert irRunSignalActive():
bool irRunSignalActive() {
  return digitalRead(IR_SUMO_START_PIN) == LOW;  // LOW = pressed = RUN
}
```

> ⚠️ Do not use a physical button in competition. The competition standard requires the IR Sumo Start module.

---

## Code Structure Summary (`08-auto-kit-standard.ino`)

| Function | Purpose |
|---|---|
| `setupPins()` | Configures all pin modes — called once in `setup()` |
| `irRunSignalActive()` | Returns `true` when D2 is HIGH (RUN signal active) |
| `checkIRStopSignal()` | Stops motors and halts if D2 is LOW — called at top of `loop()` |
| `waitForIRStartSignal()` | Calls `stopMotors()`, then blocks until D2 goes HIGH |
| `startRoutine()` | Opening match sequence after RUN signal received |
| `edgeLeftDetected()` | Returns `true` when left edge sensor is triggered |
| `edgeRightDetected()` | Returns `true` when right edge sensor is triggered |
| `anyOpponentDetected()` | Returns `true` when any opponent sensor is triggered |
| `searchOpponent()` | Slow circular arc to scan for opponent |
| `attackOpponent()` | Charge at detected opponent based on sensor priority |
| `handleEdge(dir)` | Back off from edge, turn, optionally surge |
| `stopMotors()` | Immediately set both motors to speed 0 |

### `setup()` structure
```cpp
void setup() {
  setupPins();
  stopMotors();
  waitForIRStartSignal();
  startRoutine();
}
```

### `loop()` structure
```cpp
void loop() {
  checkIRStopSignal();         // Priority 0: STOP if signal is LOW

  if (edgeLeftDetected()) {
    handleEdge(SEARCH_RIGHT);
  }
  else if (edgeRightDetected()) {
    handleEdge(SEARCH_LEFT);
  }
  else if (anyOpponentDetected()) {
    attackOpponent();
  }
  else {
    searchOpponent();
  }
}
```

---

## Validation Checklist Summary

- [ ] `08-auto-kit-standard.ino` has `IR_SUMO_START_PIN = 2` with `INPUT` mode
- [ ] `irRunSignalActive()` returns `digitalRead(...) == HIGH`
- [ ] `waitForIRStartSignal()` calls `stopMotors()` first
- [ ] `checkIRStopSignal()` called at the top of `loop()` before edge/opponent logic
- [ ] `setupPins()` function exists and configures all pins
- [ ] `edgeLeftDetected()`, `edgeRightDetected()`, `anyOpponentDetected()` helpers exist
- [ ] Motor pins D4/D5/D6/D7 unchanged
- [ ] Sensor pins D3/D10/D11/D12/A0/A1/A2 unchanged
- [ ] RC Mode D2 usage is NOT overwritten
- [ ] `09-ir-sumo-start-test.ino` does NOT move motors
- [ ] `09-ir-sumo-start-test.ino` uses `INPUT` mode for D2
- [ ] All documentation files updated
- [ ] SKILL.md Instruction 15 updated
- [ ] TESTER-GUIDE.md Section F added
- [ ] FEEDBACK-FORM.md Q7–Q13 updated

---

## Recommended Next Testing Steps

1. **Signal test first:** Upload `09-ir-sumo-start-test.ino`. Confirm D13 LED turns ON on RUN and OFF on STOP before proceeding.

2. **Motor pin test (wheels lifted):** Upload `01-motor-test.ino`. Confirm motor directions. Swap motor terminal wires if needed — do not fix direction in code.

3. **Sensor test:** Upload `02-sensor-test.ino`. Cover each sensor manually and confirm correct readings.

4. **Full match test (wheels lifted):** Upload `08-auto-kit-standard.ino`. Send RUN — confirm start routine runs. Send STOP — confirm robot halts immediately.

5. **Ring boundary test:** Place robot on ring edge. Confirm edge detection triggers backoff before placing robot in full competition position.

6. **Competition delay:** Change `START_DELAY_MS` to `5000` before competition use.

---

## Human Review Items

| Item | Status |
|---|---|
| `09-ir-sumo-start-test.ino` tested on real hardware | ⬜ Pending |
| `08-auto-kit-standard.ino` STOP signal tested at competition distance | ⬜ Pending |
| IR Sumo Start module mounting position confirmed for kit chassis | ⬜ Pending |
| Competition 5-second delay rule confirmed for target event | ⬜ Pending |
| Hybrid Mode D2 conflict resolution documented | ⬜ Pending — ask user to confirm D2 use if both modes active |
