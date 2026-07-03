# IR Sumo Start Integration — Validation Checklist
## 1KG Autonomous Sumo Robot Starter Kit using URC10

Use this checklist to verify that the IR Sumo Start integration in `08-auto-kit-standard.ino`
and all related documentation is complete and correct.

---

## Section 1 — Code: Pin Declaration

- [ ] **D2 is used as `IR_SUMO_START_PIN`**
  - Code contains: `const uint8_t IR_SUMO_START_PIN = 2;`
  - No use of old `START_BUTTON_PIN` constant in Auto Kit Mode code

- [ ] **Declared as `const uint8_t`**, not `#define`
  - Follows the standardized declaration style for this AI Coding Pack

- [ ] **Comment explains signal logic on the same definition:**
  ```cpp
  // HIGH = RUN  → robot may move
  // LOW  = STOP → motors must stop immediately
  ```

---

## Section 2 — Code: Pin Mode

- [ ] **`INPUT` mode used, NOT `INPUT_PULLUP`**
  - Code contains: `pinMode(IR_SUMO_START_PIN, INPUT);`
  - `INPUT_PULLUP` is **not** present for `IR_SUMO_START_PIN`

- [ ] **Comment explains why INPUT is used:**
  - Module drives D2 actively — no internal pullup needed

- [ ] **All sensor pins still use `INPUT_PULLUP` correctly:**
  - `EDGE_LEFT_PIN`, `EDGE_RIGHT_PIN`
  - `OPPONENT_SIDE_LEFT_PIN`, `OPPONENT_SIDE_RIGHT_PIN`
  - `OPPONENT_FRONT_LEFT_PIN`, `OPPONENT_FRONT_CENTER_PIN`, `OPPONENT_FRONT_RIGHT_PIN`

---

## Section 3 — Code: Signal Logic

- [ ] **RUN = HIGH is correctly implemented:**
  - `irRunSignalActive()` returns `true` when `digitalRead(IR_SUMO_START_PIN) == HIGH`

- [ ] **STOP / READY = LOW is correctly handled:**
  - When `!irRunSignalActive()`, motors are stopped and execution halts

- [ ] **`irRunSignalActive()` helper function exists:**
  ```cpp
  bool irRunSignalActive() {
    return digitalRead(IR_SUMO_START_PIN) == HIGH;
  }
  ```

---

## Section 4 — Code: Wait Function

- [ ] **`waitForIRStartSignal()` replaces old `waitForStartButton()`**
  - No call to `waitForStartButton()` in this code version
  - `waitForIRStartSignal()` is called in `setup()`

- [ ] **While waiting, LEDs mirror edge sensors** (calibration display):
  - `LED1_PIN` mirrors `EDGE_LEFT_PIN`
  - `LED0_PIN` mirrors `EDGE_RIGHT_PIN`

- [ ] **No `INPUT_PULLUP` logic in `waitForIRStartSignal()`:**
  - Wait condition is `!irRunSignalActive()` (i.e., `digitalRead(...) != HIGH`)
  - No "wait for release" step (IR module is level-triggered, not edge-triggered like a button)

---

## Section 5 — Code: STOP Check in `loop()`

- [ ] **STOP check is at the TOP of `loop()` — before edge detection and opponent logic:**
  ```cpp
  if (!irRunSignalActive()) {
    stopMotors();
    while (1);
  }
  ```

- [ ] **`stopMotors()` is called immediately on STOP** — no delay before halting

- [ ] **`while(1)` keeps robot stopped until reset** — does not resume automatically

- [ ] **LEDs turned off on STOP** (optional but present in standard code):
  ```cpp
  digitalWrite(LED0_PIN, HIGH);  // OFF
  digitalWrite(LED1_PIN, HIGH);  // OFF
  ```

---

## Section 6 — Code: Motor Pins (Unchanged)

- [ ] **Left Motor: PWM = D5, DIR = D4** — unchanged from previous version
- [ ] **Right Motor: PWM = D6, DIR = D7** — unchanged from previous version
- [ ] **`CytronMD motorL(PWM_DIR, 5, 4);`** — correct
- [ ] **`CytronMD motorR(PWM_DIR, 6, 7);`** — correct

---

## Section 7 — Code: Sensor Pins (Unchanged)

- [ ] `EDGE_LEFT_PIN`            = 12  (D12)
- [ ] `EDGE_RIGHT_PIN`           = 11  (D11)
- [ ] `OPPONENT_SIDE_LEFT_PIN`   =  3  (D3)
- [ ] `OPPONENT_SIDE_RIGHT_PIN`  = 10  (D10)
- [ ] `OPPONENT_FRONT_RIGHT_PIN` = A0
- [ ] `OPPONENT_FRONT_CENTER_PIN`= A1
- [ ] `OPPONENT_FRONT_LEFT_PIN`  = A2

---

## Section 8 — Code: Safety Comments

- [ ] **Battery polarity warning** in file header
- [ ] **Lift wheels warning** in file header
- [ ] **IR Sumo Start replaces physical button** explained in file header
- [ ] **RUN = HIGH / STOP = LOW** explained in file header or at pin declaration
- [ ] **STOP must stop motors immediately** explained at STOP check in `loop()`
- [ ] **D4, D5, D6, D7 RESERVED** comment present

---

## Section 9 — Documentation: `auto-kit-sensor-map.md`

- [ ] **D2 row describes IR Sumo Start module** (not physical button)
- [ ] **Signal logic table present:** HIGH=RUN, LOW=STOP
- [ ] **Wiring table present:** +→5V, −→GND, S→D2
- [ ] **`INPUT` mode requirement stated** (not `INPUT_PULLUP`)
- [ ] **AI Coach Rule updated** to use IR Sumo Start on D2 by default

---

## Section 10 — Documentation: `auto-kit-assembly-notes.md`

- [ ] **Step 12 describes IR Sumo Start wiring** (not physical button)
- [ ] **Wiring table:** +→5V, −→GND, S→D2
- [ ] **`INPUT` mode requirement stated** in Step 12
- [ ] **Step 12b (mounting step) present:** receiver faces outward, clear line of sight
- [ ] **Fallback button note present** for bench testing only

---

## Section 11 — Documentation: `auto-kit-safety-rules.md`

- [ ] **Rule 8 (IR Sumo Start Safety) present**
- [ ] **Why IR improves safety** explained (wireless stop, synchronized start, no physical contact)
- [ ] **Never bypass STOP check** warning present
- [ ] **Mounting requirement** stated (clear line of sight)
- [ ] **Pre-power-on checklist** includes IR Sumo Start checks:
  - Module connected (+/−/S)
  - Module has clear line of sight
  - STOP signal test before placing on ring

---

## Section 12 — Documentation: `auto-kit-troubleshooting.md`

- [ ] **Problem 7 present:** Robot never starts (IR Sumo Start)
  - Causes: S wire not connected, module not receiving IR, receiver blocked, wrong pin mode, not powered
- [ ] **Problem 8 present:** Robot starts then immediately stops
  - Causes: Unstable IR signal, electrical noise on D2, pulse vs. level output
- [ ] **Problem 9 present:** LED changes but robot doesn't run
  - Causes: S wire not at URC10, wrong pin, inverted logic
- [ ] **Problem 10 present:** Robot doesn't stop on STOP signal
  - Causes: STOP check removed, long delay blocking loop, partial disconnect, `INPUT_PULLUP` used
- [ ] **Quick Diagnosis Flow updated** with IR-specific symptoms (Problems 7–10)

---

## Section 13 — SKILL.md Update

- [ ] **Instruction 15 describes IR Sumo Start as the default start method**
- [ ] **`irRunSignalActive()` code template included**
- [ ] **STOP check template included for `loop()`**
- [ ] **Physical button documented as legacy/fallback only**
- [ ] **Wiring snippet present** (+→5V, −→GND, S→D2)
- [ ] **Troubleshooting walk-through present** (4-point wiring check)

---

## Section 14 — Non-Regression Check

- [ ] `rc-mode/` files are unchanged
- [ ] `source-docs/URC10SumoRobot.ino` is unchanged (preserved as legacy reference)
- [ ] All motor driver pins (D4, D5, D6, D7) are unchanged in code
- [ ] All sensor pins (D3, D10, D11, D12, A0, A1, A2) are unchanged in code
- [ ] Other Auto Kit Mode code examples (01–05) are not modified by this update

---

## Validation Sign-off

| Item | Status |
|---|---|
| `08-auto-kit-standard.ino` updated with IR Sumo Start | ☐ Verified |
| `IR_SUMO_START_PIN = 2`, `INPUT` mode | ☐ Verified |
| `irRunSignalActive()` helper present | ☐ Verified |
| `waitForIRStartSignal()` replaces button wait | ☐ Verified |
| STOP check at top of `loop()` | ☐ Verified |
| Sensor map D2 row updated | ☐ Verified |
| Assembly notes Step 12 updated | ☐ Verified |
| Safety rules Rule 8 added | ☐ Verified |
| Troubleshooting Problems 7–10 added | ☐ Verified |
| SKILL.md Instruction 15 updated | ☐ Verified |
| Integration guide created | ☐ Verified |
| Motor and sensor pins unchanged | ☐ Verified |
