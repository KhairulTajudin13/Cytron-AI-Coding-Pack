# Project Ideas — URC10 Sumo Robot Extensions

Once you have completed the default sumo robot tutorial, try one of these projects to take your URC10 further.

---

## 1. 🏆 Competition-Ready Sumo (Beginner)

**Goal:** Make your sumo robot fully compliant with standard competition rules.

**What to change:**
- Update the start delay from **1 second to 5 seconds** (most competitions require this).
- Add a **3-blink LED countdown** before the robot moves.
- Add an **emergency stop** that triggers on the second button press.

**Files to modify:** `03-basic-sumo-behavior.ino`

**AI Prompt to use:** `modify-code-prompt.md`

---

## 2. 📏 Smarter Search Strategy (Intermediate)

**Goal:** Improve how the robot searches for its opponent when none is detected.

**Ideas to try:**
- Spiral outward from the centre instead of circular motion.
- Alternate between two different search speeds based on time elapsed.
- Detect the ring boundary and use it to stay near the centre.

**Files to modify:** `03-basic-sumo-behavior.ino` → `search()` function

**AI Prompt to use:** `modify-code-prompt.md`

---

## 3. 🚧 Obstacle Avoider (Beginner)

**Goal:** Reprogram the URC10 as an obstacle-avoidance robot that roams freely and steers away from objects.

**Sensors to use:**
- Front opponent sensors: `OPPONENT_FC` (A1), `OPPONENT_FL` (A2), `OPPONENT_FR` (A0)

**How it works:**
- Drive forward normally.
- If the front-center sensor detects an object, reverse and turn.
- If front-left detects, turn right. If front-right detects, turn left.

**Files to use:** `04-application-extension.ino`

**AI Prompt to use:** `build-application-prompt.md`

---

## 4. ➡️ Line Follower (Beginner–Intermediate)

**Goal:** Reprogram the URC10 to follow a black line on a white surface using the two edge sensors.

**Sensors to use:**
- `EDGE_L` (D12) and `EDGE_R` (D11)

**How it works:**
- If both sensors see white (no line), go straight.
- If the left sensor sees black (line), turn left.
- If the right sensor sees black (line), turn right.
- If both sensors see black, stop (end of line).

> **Note:** The edge sensors must be the type that outputs LOW on black and HIGH on white (or vice versa — test with `02-sensor-test.ino` first to confirm your sensor output).

**Files to use:** `04-application-extension.ino`

**AI Prompt to use:** `build-application-prompt.md`

---

## 5. 💡 LED Reaction Game (Beginner)

**Goal:** Build a simple reaction-time game using the two onboard LEDs and the start button.

**What it does:**
- Both LEDs turn on after a random delay (2–5 seconds).
- The player must press the button as fast as possible.
- The robot "scores" by blinking LEDs fast (quick reaction) or slow (slow reaction).

**Components needed:** No extra hardware — button, LEDs, and motors only.

**Files to use:** `04-application-extension.ino`

**AI Prompt to use:** `build-application-prompt.md`

---

## 6. 🔊 Ultrasonic Distance Sensor (Intermediate)

**Goal:** Add an HC-SR04 ultrasonic sensor to detect opponent distance more accurately than IR sensors.

**Sensor port to use:** Ultrasonic Sensor 1 — TRIG: D9, ECHO: D8 (no pin conflicts).

**How it works:**
- Send a pulse on the TRIG pin.
- Measure the pulse length on the ECHO pin using `pulseIn()`.
- Calculate distance: `distance = duration * 0.034 / 2` (in cm).
- If distance is less than a threshold (e.g., 30 cm), attack.

> ⚠️ Do **not** use Ultrasonic Sensor 2 (TRIG: D11, ECHO: D10) — these pins conflict with EDGE_R and OPPONENT_R.

**AI Prompt to use:** `build-application-prompt.md`

---

## 7. 📶 Radio Controlled (RC) Extensions (Beginner–Intermediate)

**Goal:** Modify the URC10 to accept controls from an RC transmitter/receiver.

### Ideas to try:
- **Custom Failsafe Tuning:** Modify the failsafe in `06-radio-controlled-drive.ino` to sound the onboard buzzer or flash the LEDs in a specific pattern if signal is lost, instead of just stopping.
- **Sensitivity Adjustments:** Implement dual-rates in software to scale down the speed (e.g. max 50% speed) when a switch on the transmitter is toggled, making the robot easier for beginners to drive.
- **Hybrid Sumo Mode:** Extend `07-hybrid-rc-autonomous-mode.ino` so that when autonomous mode is active, the robot performs actual sumo opponent-chasing logic, but can be instantly overridden by manual RC commands if you toggle the switch.

**Files to use:** 
- `rc-mode/code-examples/05-rc-receiver-test.ino`
- `rc-mode/code-examples/06-radio-controlled-drive.ino`
- `rc-mode/code-examples/07-hybrid-rc-autonomous-mode.ino`

---

## Note on Side Sensors — Beginner to Intermediate Progression

The beginner sumo sketch (`03-basic-sumo-behavior.ino`) intentionally omits the two side opponent sensors:
- `OPPONENT_L` — D3 (left side IR sensor)
- `OPPONENT_R` — D10 (right side IR sensor)

This is deliberate — the simplified front-sensor-only logic is easier to understand for a first project.

When you are ready to expand:
1. See the original `source-docs/URC10SumoRobot.ino` for a full 5-sensor implementation including side-sensor tracking.
2. Use **Idea 2 — Smarter Search Strategy** below as a starting point.
3. Use `build-application-prompt.md` to ask your AI assistant to help add side sensors to the beginner sketch step by step.

---

## Tips for All Projects

- Always use `02-sensor-test.ino` first to confirm your sensors are wired correctly.
- Test motor direction with `01-motor-test.ino` before using motors in new code.
- Keep wheels lifted during initial code tests.
- Refer to `safety-rules.md` before every test session.
