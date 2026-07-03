# Auto-Kit Troubleshooting — 1KG Autonomous Sumo Robot Starter Kit using URC10

## How to Use This Guide

Find the symptom that matches your problem and follow the steps. Always start with the simplest check — most problems are caused by wiring, not code.

> ⚠️ **Safety first:** Always lift the robot wheels off the ground before uploading new code and testing. See `auto-kit-safety-rules.md`.

---

## Problem 1 — Motors Not Moving

**Symptom:** The robot is powered on, the code uploads successfully, the start button is pressed, but no wheels spin.

### Checklist

**Step 1 — Check the power connection**
- Is the LiPo battery connected?
- Is the Dean T connector fully seated into the battery extension wire?
- Is the battery charged? A fully discharged LiPo will not provide enough voltage to run the motors.

**Step 2 — Check the power switch**
- Is the URC10 power switch in the ON position?

**Step 3 — Check the motor terminal wiring**
- Are both motor wires connected to the M1 and M2 terminals on the URC10?
- Are the screws on the terminal block tightened? Loose screws = no connection.

**Step 4 — Check the code**
- Does the code reach the motor command? Add a Serial print or LED blink to confirm the start button was detected.
- Is `setSpeed()` called with a non-zero value?

**Step 5 — Check the motor driver library**
- Is `CytronMotorDriver.h` installed and selected in Arduino IDE?
- Is the motor object declared globally with the correct pins?
  ```cpp
  CytronMD motorL(PWM_DIR, 5, 4);  // Left motor: PWM=D5, DIR=D4
  CytronMD motorR(PWM_DIR, 6, 7);  // Right motor: PWM=D6, DIR=D7
  ```
- Are you using `setSpeed()` and not `analogWrite()` or `digitalWrite()` directly?

**Step 6 — Board selection**
- In Arduino IDE: Tools → Board → confirm "Arduino Uno" is selected, NOT another board.

---

## Problem 2 — Robot Moves in the Opposite Direction

**Symptom:** The robot drives backward when it should drive forward, or turns in the wrong direction.

### Cause
Motor direction depends on **how the motor wires are connected to the terminal**, not just the code. The code cannot know which way is "forward" — that is determined by wiring.

### Fix — Swap the Motor Wires
1. Power off the robot completely (disconnect battery)
2. Locate the motor wire terminals (M1 and M2 on the URC10)
3. For the motor that spins in the wrong direction, **swap its two wires** on the terminal (exchange the + and – wires)
4. Reconnect battery and test again

> **Do not** try to fix this by negating the speed value in code. Swapping the physical wires is the correct solution.

### If Both Motors Spin in the Wrong Direction
Swap both sets of motor wires. This is common if the motors were installed in a mirrored orientation compared to the default tutorial setup.

---

## Problem 3 — Robot Drives Out of the Ring

**Symptom:** The robot reaches the edge of the ring and continues driving off instead of backing away.

### Possible Causes and Fixes

**Cause A — Maker Reflect sensors not detecting the white line**
- Are the sensors installed on the **underside** of the chassis, facing the floor? (not top-mounted)
- Is the sensor close enough to the floor? Ideal mounting height: 5–15mm from the ring surface
- Is the sensor sensitivity adjusted? Use a screwdriver to turn the potentiometer on the sensor until it reliably detects the white/dark boundary

**Cause B — Sensor wired to wrong pin**
- Check that the Maker Reflect sensors are connected to D12 (left) and D11 (right)
- Confirm GVS pin order: G = GND, V = 5V, S = Signal

**Cause C — Edge detection not running every loop**
- Your `loop()` function must check edge sensors every iteration — not just after specific events
- If the edge check is inside an `if` block that only runs sometimes, the robot may miss the trigger

**Cause D — Backoff delay too short**
- The robot backs up but not far enough before turning
- Increase `BACKOFF_DELAY` in the `#define` constants (see `auto-kit-tuning-guide.md`)

**Cause E — Sensor is faulty or has a damaged connector**
- Test the sensor independently: hold it over white paper vs. dark surface and check the LED indicator on the Maker Reflect PCB. It should light up over white and go off over dark (or vice versa, depending on sensitivity).

---

## Problem 4 — Robot Cannot Detect Opponent

**Symptom:** The robot enters search mode but never reacts to the opponent being nearby.

### Possible Causes and Fixes

**Cause A — Maker Object sensor sensitivity too low**
- Each Maker Object sensor has a potentiometer screw on the PCB
- Adjust the sensitivity so it detects an object at the expected competition range (approximately 10–25cm)
- Test: wave your hand in front of the sensor at 15cm — the sensor LED should change state

**Cause B — Sensor wired to wrong pin**
- Check your sensor pin assignments in `auto-kit-sensor-map.md`
- Confirmed pins: A0 (front right), A1 (front center), A2 (front left), D3 (side left), D10 (side right)
- Use `Serial.println(digitalRead(A1))` to verify the sensor pin is reading correctly

**Cause C — GVS connector incorrectly oriented**
- If the GVS connector is flipped (G and V swapped), the sensor receives no power and reads nothing
- Unplug and recheck that: pin 1 = G (Ground), pin 2 = V (5V), pin 3 = S (Signal)

**Cause D — Opponent is behind the robot**
- The sensors only cover a front and side arc. If the opponent approaches from directly behind, no sensor will detect it during a search sweep.
- Ensure the search pattern fully rotates the robot to scan all directions

**Cause E — Search speed too high**
- If the robot rotates too fast, the sensor may only briefly point at the opponent between readings and miss the detection
- Reduce `SEARCH_SPEED` (see `auto-kit-tuning-guide.md`)

---

## Problem 5 — Robot Constantly Thinks It Is at the Edge (False Edge Detection)

**Symptom:** The robot backs up and turns constantly, even when it is in the center of the ring.

### Possible Causes and Fixes

**Cause A — Maker Reflect sensor sensitivity too high**
- The sensor is triggering on slight colour variations in the ring surface, or on ambient light reflections
- Turn the potentiometer on the Maker Reflect PCB to reduce sensitivity until it only triggers on the actual white boundary line

**Cause B — Sensor mounted too high**
- If the sensor is mounted too far from the floor, it may receive diffuse reflections that appear as white
- Move the sensor closer to the ring surface (ideal: 5–15mm)

**Cause C — Ambient light interference**
- Strong overhead lighting, sunlight, or spotlights can saturate the IR sensor and cause false readings
- Shield the sensor from direct overhead light if possible, or adjust its sensitivity to compensate

**Cause D — Sensor is reading the wrong floor color**
- Test: slide the robot over the ring surface (dark area) and then over the white line. Does the sensor state change correctly?
- If the sensor reads LOW on the dark ring and HIGH on the white line (opposite of expected), the sensor logic in code may need to be inverted

**Cause E — Wiring short or noise**
- A loose or partially connected GVS cable can cause intermittent LOW readings
- Check all connections are firm

---

## Problem 6 — Button Does Not Start the Robot

**Symptom:** Pressing the start button does nothing — the robot never begins its startup sequence.

### Possible Causes and Fixes

**Cause A — Wrong button pin in code (most common)**

For this AI Coding Pack, the standard Start Button pin is **D2** — the kit tutorial says GPIO 2 (= D2).
All code in this pack uses:
```cpp
#define START_BUTTON_PIN  2
```

If your code still has the old `#define BUTTON 13` from the legacy sample code, the button will not work
because the physical button is wired to A4, not D13.

**Fix:** Replace the button pin definition:
```cpp
// OLD (legacy sample code) — remove this:
#define BUTTON  13

// NEW (Auto Kit Mode standard) — use this:
#define START_BUTTON_PIN   2  // Kit tutorial standard (GPIO 2 = D2)
                              // Change to 13 if your button is physically wired to D13
```

Then replace all uses of `BUTTON` in the code with `START_BUTTON_PIN`.

**Legacy note:** If you physically wired your button to D13 (using the old Cytron sample code) or D2 (following a tutorial that said "GPIO 2"), change A4 to match your wiring — the hardware is correct, only the constant needs to change.

**Cause B — `INPUT_PULLUP` not set**
The button requires `INPUT_PULLUP` to work. Without it, the pin floats and reads random values.
```cpp
pinMode(START_BUTTON_PIN, INPUT_PULLUP);
```

**Cause C — Button wiring incorrect**
The button should connect between the signal pin (A4) and GND. With `INPUT_PULLUP`, pressing the button pulls the pin LOW.
- Verify one terminal of the button goes to A4
- Verify the other terminal goes to GND

**Cause D — Button connector not seated**
Check that the button's connector is fully plugged into the A4 port on the board.

**Cause E — Code is waiting on a different condition**
Add this debug block before the button wait loop to confirm code reaches that point:
```cpp
Serial.begin(9600);
Serial.println("Waiting for button on A4...");
while (digitalRead(START_BUTTON_PIN) == HIGH) {}
Serial.println("Button pressed!");
```

---

## Quick Diagnosis Flow

```
Robot not working as expected
  │
  ├── No movement at all?               → Problem 1 (Motors Not Moving)
  │
  ├── Moves wrong direction?             → Problem 2 (Opposite Direction)
  │
  ├── Drives off the ring?               → Problem 3 (Drives Out of Ring)
  │
  ├── Never finds opponent?              → Problem 4 (Cannot Detect Opponent)
  │
  ├── Always thinks at edge?             → Problem 5 (False Edge Detection)
  │
  ├── Button / IR signal does nothing?   → Problem 6 (Signal Not Working)
  │
  ├── IR: robot never starts?            → Problem 7 (Robot Never Starts on IR)
  │
  ├── IR: starts then stops instantly?   → Problem 8 (Robot Stops Immediately)
  │
  ├── IR: LED changes but no movement?   → Problem 9 (LED Works, Robot Doesn't)
  │
  └── IR: won't stop on STOP signal?     → Problem 10 (Robot Ignores STOP)
```

---

## Still Stuck?

If none of the above solves your problem:
1. Ask the AI Coach — describe exactly what the robot does (or does not do)
2. Check `auto-kit-sensor-map.md` to verify all pin assignments
3. Read `auto-kit-safety-rules.md` to ensure safe testing conditions
4. Read `ir-sumo-start-integration.md` for detailed IR Sumo Start troubleshooting
5. Try the official Cytron tutorial sample code as a baseline to confirm hardware is functional

---

## Problem 7 — Robot Never Starts (IR Sumo Start)

**Symptom:** Power is on, code is uploaded, IR Sumo Start module is connected, but the robot never moves even after sending the RUN signal.

### Possible Causes and Fixes

**Cause A — S wire not connected to D2**
Verify the IR Sumo Start `S` terminal is wired to **D2** on the URC10 board, not to GND or 5V.
- Check the three connections: + to 5V, − to GND, **S to D2**
- A loose or wrong connection on S means D2 will never go HIGH

**Cause B — Module not receiving IR signal**
Check if the IR Sumo Start module's LED changes state when you:
- Press the module's onboard test button (if present), or
- Point the IR transmitter at the module from close range
If the LED does not change, the module is not receiving the signal.

**Cause C — IR receiver blocked**
Ensure the IR receiver window on the module has a **clear, unobstructed view** to the judge's transmitter. Rotate or reposition the module if necessary.

**Cause D — Wrong pin mode in code**
Confirm the code uses `INPUT` (not `INPUT_PULLUP`) for `IR_SUMO_START_PIN`:
```cpp
pinMode(IR_SUMO_START_PIN, INPUT);  // Correct — module drives D2
```
Using `INPUT_PULLUP` adds a pullup that can hold D2 HIGH regardless of the module, preventing a valid STOP signal.

**Cause E — Module not powered**
Confirm the `+` terminal is connected to 5V (not 3.3V) and the `−` terminal is connected to GND.
Check the module's power LED if it has one.

---

## Problem 8 — Robot Starts Then Immediately Stops

**Symptom:** After receiving the RUN signal, the robot starts but stops after a fraction of a second (or never even completes the start delay).

### Possible Causes and Fixes

**Cause A — IR signal is unstable or intermittent**
The module may be losing the RUN signal almost immediately after sending it.
- Test with the module's onboard button held down continuously
- If the robot keeps running while the button is held but stops when released, the remote/transmitter is not holding the signal
- Ensure the IR transmitter is pointed at the module and within range during the entire match

**Cause B — Electrical noise on D2**
A floating or noisy D2 line can read as LOW unexpectedly. Verify:
- S wire is securely connected to D2
- The wire is not routed near motor wires (motor current can cause interference)
- The module's GND is connected to the same GND as the URC10

**Cause C — `irRunSignalActive()` check at top of loop runs before movement**
This is by design. If the IR signal is not continuously HIGH, the robot will stop every loop cycle.
The IR Sumo Start module must output a sustained HIGH during the match, not a brief pulse.

---

## Problem 9 — IR Sumo Start LED Changes but Robot Does Not Run

**Symptom:** You can see the IR Sumo Start module LED change state (indicating it received the IR signal), but the robot does not start.

### Possible Causes and Fixes

**Cause A — S wire not connected to URC10**
The module LED responds to the IR signal regardless of whether the S wire is connected.
A disconnected S wire means D2 on the URC10 never sees the HIGH signal.
- Verify the S wire goes from the module to D2 on the URC10
- Check both ends: the module-side connector and the D2 pin on the board

**Cause B — S wire connected to the wrong pin**
If the S wire is connected to any pin other than D2, the code will never detect the RUN signal.
Check the code constant:
```cpp
const uint8_t IR_SUMO_START_PIN = 2;  // Must match your physical wiring
```

**Cause C — Code is using `digitalRead()` wrong**
Confirm `irRunSignalActive()` checks for HIGH:
```cpp
bool irRunSignalActive() {
  return digitalRead(IR_SUMO_START_PIN) == HIGH;
}
```
If the comparison is `== LOW` by mistake, the logic is inverted.

---

## Problem 10 — Robot Does Not Stop on STOP Signal

**Symptom:** The judge sends a STOP signal and the IR Sumo Start LED changes, but the robot continues moving.

### Possible Causes and Fixes

**Cause A — IR STOP check removed or bypassed from code**
The `08-auto-kit-standard.ino` code checks for STOP at the top of every loop:
```cpp
if (!irRunSignalActive()) {
  stopMotors();
  while (1);
}
```
If this block was deleted or commented out, the robot will not respond to STOP.
Restore the check at the top of `loop()`.

**Cause B — Long delay in a sub-function blocking the loop check**
If the robot is in the middle of a long `delay()` inside `handleEdge()` or `startRoutine()`, the STOP check in `loop()` will not run until that delay finishes.
This is a known limitation of `delay()`-based code. For critical applications, replace `delay()` with non-blocking timing using `millis()`.

**Cause C — S wire partially disconnected**
A partially disconnected S wire may read HIGH (floating) even after the module outputs LOW.
Push the S wire connector firmly into the D2 pin header.

**Cause D — Code uses `INPUT_PULLUP` instead of `INPUT`**
With `INPUT_PULLUP`, D2 is pulled HIGH internally. Even if the module sends LOW, the internal pullup may overpower the signal.
Change to `INPUT`:
```cpp
pinMode(IR_SUMO_START_PIN, INPUT);  // Correct for IR Sumo Start module
```
