# IR Sumo Start Integration Guide
## 1KG Autonomous Sumo Robot Starter Kit using URC10

---

## What is the IR Sumo Start Module?

The **Cytron IR Sumo Start Module** (model: IR-SUMO-START) is a compact infrared receiver module designed for sumo robot competitions.

It allows a competition judge to:
- **Start** all robots simultaneously by pressing a button on an IR remote
- **Stop** all robots immediately by pressing the stop button on the IR remote

The module receives the judge's IR signal and converts it into a simple digital output that the robot's controller (URC10) can read on a digital pin.

**Product page:** https://my.cytron.io/p-ir-sumo-start-module

---

## Why It Replaces the Physical Button

| Feature | Physical Button | IR Sumo Start Module |
|---|---|---|
| Start trigger | Manual press on robot | IR signal from judge's remote |
| Stop trigger | Manual press on robot | IR signal from judge's remote |
| Synchronized start | ❌ Not possible | ✅ All robots start at the same time |
| Wireless stop | ❌ Must touch the robot | ✅ Stop from a distance |
| Competition standard | ❌ Not accepted at most competitions | ✅ Required at Cytron competitions |
| Safety | ⚠️ Must approach moving robot to stop it | ✅ Stop immediately without touching robot |

In competition, you **cannot** use a physical button because:
1. You cannot touch the robot after it is placed on the ring
2. All robots must start at the exact same moment
3. The judge must be able to stop all robots immediately if something goes wrong

---

## Signal Logic

| D2 Signal Level | IR Module State | Robot Behaviour |
|---|---|---|
| **HIGH** | **RUN** — judge sent start, match in progress | ✅ Robot moves normally |
| **LOW** | **READY / STOP** — judge sent stop, or no signal received | 🛑 Robot stops immediately and stays stopped |

> ⚠️ **STOP is the default state.** When there is no signal (or signal is lost), the output goes LOW and the robot stops. This is a fail-safe: the robot cannot accidentally run without a confirmed START.

---

## Wiring to URC10

Connect the three terminals of the IR Sumo Start module to the URC10 board:

| IR Sumo Start Terminal | URC10 Pin | Notes |
|---|---|---|
| **+** (Power) | **5V** | Do not use 3.3V — module requires 5V |
| **−** (Ground) | **GND** | Connect to any GND pin on URC10 |
| **S** (Signal) | **D2** | Digital pin 2 — standard Auto Kit Mode pin |

**Wiring diagram:**
```
IR Sumo Start Module        URC10 Board
┌─────────────────┐        ┌──────────┐
│    +  ──────────┼────────┤ 5V       │
│    −  ──────────┼────────┤ GND      │
│    S  ──────────┼────────┤ D2       │
└─────────────────┘        └──────────┘
```

> ⚠️ **Do not swap + and − terminals.** Check the module labeling carefully before connecting power.

---

## Pin Mode — Why INPUT, Not INPUT_PULLUP

The IR Sumo Start module outputs a **driven digital signal** on its S terminal:
- It actively drives S to **HIGH** when RUN
- It actively drives S to **LOW** when STOP

Because the module drives the line actively, the Arduino does **not** need to add an internal pullup resistor.

If you use `INPUT_PULLUP`:
- The internal pullup holds D2 HIGH even when the module tries to pull it LOW
- This may prevent the STOP signal from being detected correctly

**Correct:**
```cpp
pinMode(IR_SUMO_START_PIN, INPUT);   // ✅ Module drives D2
```

**Incorrect:**
```cpp
pinMode(IR_SUMO_START_PIN, INPUT_PULLUP);  // ❌ Fights against module output
```

---

## Code Behaviour in `08-auto-kit-standard.ino`

### Pin Declaration
```cpp
const uint8_t IR_SUMO_START_PIN = 2;
// HIGH = RUN  → robot may move
// LOW  = STOP → motors must stop immediately
```

### Setup
```cpp
void setup() {
  pinMode(IR_SUMO_START_PIN, INPUT);  // No pullup — module drives D2
  // ... other pin setup ...
  stopMotors();
  waitForIRStartSignal();   // Block until RUN signal received
  startRoutine();           // Run opening sequence
}
```

### Helper Function
```cpp
bool irRunSignalActive() {
  return digitalRead(IR_SUMO_START_PIN) == HIGH;
}
```

### Wait for Start
```cpp
void waitForIRStartSignal() {
  // Block here until IR module sends HIGH (RUN)
  while (!irRunSignalActive()) {
    // Mirror edge sensors on LEDs while waiting
    digitalWrite(LED1_PIN, digitalRead(EDGE_LEFT_PIN));
    digitalWrite(LED0_PIN, digitalRead(EDGE_RIGHT_PIN));
  }
}
```

### Loop Priority 0 — STOP Check
```cpp
void loop() {
  // Check IR signal first — highest priority
  if (!irRunSignalActive()) {
    stopMotors();
    digitalWrite(LED0_PIN, HIGH);
    digitalWrite(LED1_PIN, HIGH);
    while (1);  // Stay stopped until reset
  }
  // ... edge detection, opponent logic below ...
}
```

> ⚠️ **Never remove the STOP check from `loop()`.** It is a safety and competition requirement.

---

## Mounting the Module

The IR receiver must have a **clear, unobstructed view** toward the judge's IR transmitter.

**Good mounting positions:**
- Top of the robot chassis, receiver facing upward or forward
- Front of the robot, receiver facing toward the judge's position
- Side of the robot, if the judge is positioned to the side

**Avoid:**
- Mounting inside the chassis body (signal will not reach)
- Mounting behind the front blade (blocked)
- Mounting under the chassis (pointing down)

**Securing the module:**
- Use double-sided foam tape on the module body
- Use a small cable tie if the chassis has a suitable anchor point
- Route the three wires neatly away from the front blade and wheel shafts

---

## Test Procedure

### Step 1 — Bench test without battery
1. Connect USB to PC
2. Upload `08-auto-kit-standard.ino`
3. Connect IR Sumo Start module to 5V, GND, D2

### Step 2 — Confirm READY state
1. Power on with IR module connected
2. The robot should stay still (D2 = LOW = READY)
3. LEDs should mirror edge sensor state (for calibration)

### Step 3 — Test RUN signal
1. Press the IR transmitter's START button, pointing at the module
2. The module LED should change
3. The robot should start its match sequence (with wheels lifted!)
4. Verify the robot moves during RUN state

### Step 4 — Test STOP signal
1. While robot is running (wheels lifted), press STOP on the transmitter
2. The robot should stop immediately
3. The robot should not resume without a reset
4. ✅ If stop works: the STOP check in `loop()` is functioning correctly

### Step 5 — Test at competition distance
1. Move the transmitter to the distance the judge will use (usually 1–3 metres)
2. Test START and STOP from that distance
3. Adjust module mounting angle if signal is weak at distance

---

## Fallback: Physical Button for Bench Testing

If you do not have an IR Sumo Start module and need to test the robot logic:

Change in `08-auto-kit-standard.ino`:

```cpp
// FALLBACK — Physical button on D2 for bench testing only
// ⚠️ Do not use in competition — competitions require IR Sumo Start

// 1. Change pin mode in setup():
pinMode(IR_SUMO_START_PIN, INPUT_PULLUP);  // Button: not pressed = HIGH, pressed = LOW

// 2. Invert irRunSignalActive():
bool irRunSignalActive() {
  return digitalRead(IR_SUMO_START_PIN) == LOW;  // LOW = button pressed = RUN
}
```

> This button fallback reverses the logic: pressing the button = RUN, releasing = STOP.
> This is intentional — the physical button is active-low with INPUT_PULLUP.

---

## Troubleshooting Quick Reference

| Symptom | Most Likely Cause | Fix |
|---|---|---|
| Robot never starts | S wire not connected, or module not receiving IR | Check S→D2 wiring, aim transmitter at module |
| Starts then stops immediately | IR signal is unstable or intermittent | Hold transmitter closer, check GND connection |
| LED changes but robot doesn't move | S wire disconnected from URC10 | Check S wire at D2 pin end |
| Robot won't stop on STOP signal | STOP check removed from code, or `INPUT_PULLUP` used | Restore `if (!irRunSignalActive())` in `loop()`, use `INPUT` mode |

For detailed steps, see `auto-kit-troubleshooting.md`, Problems 7–10.
