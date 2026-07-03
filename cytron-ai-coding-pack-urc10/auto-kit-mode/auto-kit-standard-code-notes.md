# Auto Kit Standard Code — Notes

## File: `code-examples/08-auto-kit-standard.ino`

This file documents the decisions made when deriving `08-auto-kit-standard.ino`
from the original Cytron `URC10SumoRobot.ino` sample code.

---

## What Changed from the Original URC10 Sample

| Item | Original (`URC10SumoRobot.ino`) | Standard (`08-auto-kit-standard.ino`) |
|---|---|---|
| Button pin | D13 (`#define BUTTON 13`) | D2 (`#define START_BUTTON_PIN 2`) |
| Constant name | `BUTTON` | `START_BUTTON_PIN` |
| Speed values | Raw numbers (`255`, `150`, `100`) | Named constants (`ATTACK_SPEED`, `SEARCH_SPEED`, `TURN_SPEED`) |
| Timing values | Raw numbers (`180`, `450`, `200`) | Named constants (`START_DELAY_MS`, `BACKOFF_DELAY_MS`) |
| Function names | `backoff()`, `search()`, `attack()` | `handleEdge()`, `searchOpponent()`, `attackOpponent()` |
| Active-low explanation | Not explained | Documented in every relevant comment |
| Serial Monitor | Not used | Not used (D0/D1 are LED pins — see note below) |
| LED usage | Used inside `setup()` only | Used in `waitForStartButton()` for edge calibration |
| Safety warnings | None | Battery polarity, lift-wheels, first-test guidance |
| Wait function | Inline in `setup()` | Extracted to `waitForStartButton()` |
| Typo: `motorL.setSpeed(-0)` | Present in `startRoutine()` | Fixed to `0` |
| Backoff: comment typo `// Rotate..` | Present | Removed |
| Comment: `// Return to the main loop and run the attach program.` | Typo ("attach") | Removed — code is self-explanatory |

---

## Why D2 is the Standard Start Button Pin

The official **1KG Autonomous Sumo Robot Starter Kit** tutorial instructs users to:

> *"Connect the button to GPIO 2 and GND"*

**GPIO 2 = Digital Pin D2** on the URC10 board (Arduino Uno compatible).

The old Cytron sample code (`URC10SumoRobot.ino`) used `#define BUTTON 13`, which refers to **D13**. That code was written for a different wiring configuration than the kit tutorial.

For this AI Coding Pack, **D2 is the Auto Kit Mode standard** because it is what the kit tutorial tells users to wire.

### Legacy Note for D13

If you used the old Cytron sample code and already wired your button to **D13**, your button will not work with `START_BUTTON_PIN 2`. Fix this in one line:

```cpp
// Change:
#define START_BUTTON_PIN   2

// To:
#define START_BUTTON_PIN  13  // Legacy wiring — button connected to D13
```

No other code changes are needed. The button logic (`INPUT_PULLUP`, `== LOW` checks) is identical regardless of the pin.

---

## Why No Serial Monitor

The URC10 has two onboard LEDs on **D0** and **D1**:
- D0 is also the **TX** (transmit) pin for Serial.
- D1 is also the **RX** (receive) pin for Serial.

If you call `Serial.begin()` while `LED0_PIN` and `LED1_PIN` are configured as outputs, the serial communication will corrupt, and the LED behaviour will be wrong.

**Rule:** Do not use `Serial.begin()` in any code that also uses `pinMode(0, OUTPUT)` or `pinMode(1, OUTPUT)`.

For debugging with the Serial Monitor, use the dedicated `02-sensor-test.ino`, which disables LED output for this reason.

---

## How to Tune Speed Safely

All speed and timing values are defined as named constants near the top of the file:

| Constant | Default | Purpose |
|---|---|---|
| `SEARCH_SPEED` | 90 | Circular arc speed during opponent search |
| `ATTACK_SPEED` | 200 | Speed when charging at opponent |
| `TURN_SPEED` | 140 | Speed when spinning to face side-detected opponent |
| `BACKOFF_SPEED` | 180 | Reverse speed when escaping ring edge |
| `START_DELAY_MS` | 1000 | Delay after button press before match begins |
| `BACKOFF_DELAY_MS` | 200 | Duration of reverse after edge detection |

### Safe tuning procedure

1. **Lift wheels off the ground** before any speed change.
2. Start at the lowest speed that gives you useful movement (80–120 for search, 150 for attack).
3. Upload and observe with wheels lifted. Confirm direction and stopping behaviour.
4. Lower the robot onto a test surface — not the competition ring yet.
5. Only increase speed once the robot behaves correctly at the lower setting.

> ⚠️ Never jump from 0 to 255 for your first test. Motors at full speed can throw the robot across the table.

### Competition tuning advice

- `ATTACK_SPEED 200–255` — increase only after confirming basic ring behaviour
- `START_DELAY_MS 5000` — change to 5 seconds for any competition with a mandatory start delay

---

## Step-by-Step Testing Guide

### Step 1 — Bench test before the ring

1. Connect the URC10 to your PC via Micro USB.
2. Check battery polarity before connecting the LiPo. Reversed polarity destroys the board.
3. Upload `01-motor-test.ino` and confirm both wheels spin forward and backward correctly.
4. Upload `02-sensor-test.ino` and confirm every sensor shows TRIGGERED when activated.

### Step 2 — First run with wheels lifted

1. Upload `08-auto-kit-standard.ino`.
2. Power the robot. Do **not** place it on the ring yet.
3. Hold the robot with wheels off the ground.
4. Press the Start button (D2). Release it.
5. The LEDs will turn on and the start delay will count down.
6. After the delay, motors will spin. Verify:
   - Both wheels spin forward for the opening surge.
   - The robot sweeps left (right wheel slightly faster) during search.
   - Waving your hand at the front sensors causes a charge.
   - Covering an edge sensor causes a reversal.

### Step 3 — Test on the ring

1. Place the robot on the sumo ring with wheels touching the ring surface.
2. Press Start. Release. Step back.
3. Observe: the robot should stay within the ring, scan, and attack when it detects your hand.
4. Press the button again to emergency-stop.

---

## What to Change if the Robot Turns the Wrong Way

If the robot reverses instead of going forward, or turns the wrong direction:

**Option A — Swap motor wires** (hardware fix, recommended)
Swap the two wires for that motor on the screw terminal on the URC10. This flips the direction for that motor permanently without changing the code.

**Option B — Negate the speed in code** (software fix)
If `motorL.setSpeed(ATTACK_SPEED)` drives backward instead of forward, change it to `motorL.setSpeed(-ATTACK_SPEED)` in the relevant function.

Be consistent: if you negate for one function, you must negate in all functions that control that motor in the same direction.

---

## What to Change if Button Was Wired to D13

The original Cytron sample code used D13. If you followed that wiring:

```cpp
// In 08-auto-kit-standard.ino, find this line:
#define START_BUTTON_PIN   2

// Change the 2 to 13:
#define START_BUTTON_PIN  13
```

That is the only change needed. All button reads in the code use `START_BUTTON_PIN`, so this one edit updates the entire sketch.

---

## Related Files

| File | Purpose |
|---|---|
| `auto-kit-mode/code-examples/08-auto-kit-standard.ino` | The code this document describes |
| `auto-kit-mode/auto-kit-sensor-map.md` | Full pin table for the kit |
| `auto-kit-mode/auto-kit-tuning-guide.md` | Detailed tuning advice for all constants |
| `auto-kit-mode/auto-kit-troubleshooting.md` | Common problems and fixes |
| `auto-kit-mode/auto-kit-safety-rules.md` | Battery, blade, and motor safety |
| `code-examples/01-motor-test.ino` | Motor direction test (run first) |
| `code-examples/02-sensor-test.ino` | Sensor verification with Serial Monitor |
