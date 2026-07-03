# Auto-Kit Behavior Guide — 1KG Autonomous Sumo Robot Starter Kit using URC10

## Overview

This guide explains how an autonomous sumo robot behaves from the moment it starts to the moment the match ends. Understanding the logic helps you tune, debug, and improve your robot's performance.

The robot does not use remote control. Once the match begins, it makes all decisions using sensor data only.

---

## The 6 Core Behavior States

An autonomous sumo robot typically cycles through these states:

```
[WAIT] → [START] → [SEARCH] → [ATTACK] ←→ [EDGE DETECT] → [BACKOFF/TURN]
                    ↑____________________________|
```

---

## State 1 — Wait / Ready State

### What Happens
The robot is powered on but not yet moving. It waits for the operator to press the Start Button.

During this waiting period, the URC10 may use its onboard LEDs (D0, D1) to show the status of the edge sensors — this helps you verify the sensors are working before the match begins.

### When Does It End?
When the Start Button is pressed (reads `LOW` with `INPUT_PULLUP`).

### Code Concept
```cpp
// Wait for start button press
while (digitalRead(BUTTON_PIN) == HIGH) {
  // Show edge sensor status on LEDs
  digitalWrite(LED_PIN, digitalRead(EDGE_LEFT));
}
```

### Beginner Tip
This is a great time to wave your hand in front of the opponent sensors or place the robot over a white piece of paper to verify the edge sensors respond correctly before the match.

---

## State 2 — Start / Launch Sequence

### What Happens
After the button is pressed, the robot performs a fixed startup routine:

1. **Wait for mandatory delay** — Competition rules typically require a 5-second delay after button press before movement. The sample code uses only 1 second, which may violate competition rules. Confirm your event rules.
2. **Perform an initial turn** — The robot often performs a quick 45-degree turn to disorient or position against a likely opponent location
3. **Drive forward briefly** — The robot drives straight for a short time (~450ms) to move toward the center of the ring
4. **Enter Search mode**

### Why the Delay?
Sumo competitions require that both robots start simultaneously. The 5-second delay allows the human operators to step back from the ring and both robots to begin at the same time. Missing this delay can result in disqualification.

### Code Concept
```cpp
// After button press
delay(5000);          // Mandatory wait (confirm your competition rules)
turn45degrees();      // Initial orientation turn
driveForward(450);    // Move toward center
// Enter SEARCH state
```

---

## State 3 — Search Behavior

### What Happens
The robot moves in a pattern designed to find the opponent. If no opponent is detected by any sensor, the robot continues searching.

The typical search pattern is a **slow circular motion** — one motor runs faster than the other, causing the robot to rotate and sweep its front sensors across the ring.

### When Does It Change?
- If any opponent sensor detects something → transition to **Attack**
- If any edge sensor triggers → transition to **Edge Detection / Backoff**

### Sensor Check (All 5 Opponent Sensors)
The robot checks all five Maker Object sensors every loop:
- Front Left (A2)
- Front Center (A1)
- Front Right (A0)
- Side Left (D3)
- Side Right (D10)

If any of these reads `LOW` (object detected), the robot switches to Attack mode immediately.

### Code Concept
```cpp
// Search: slow circular spin
motorL.setSpeed(SEARCH_SPEED);
motorR.setSpeed(-SEARCH_SPEED / 2);

// Check for opponent every loop iteration
if (opponentDetected()) {
  enterAttackMode();
}
```

---

## State 4 — Opponent Detection

### What Happens
This is not a movement state — it is the detection event that triggers Attack mode.

Each Maker Object sensor outputs `LOW` when it detects an object within range.

### Detection Priority
- **Front sensors** (A0, A1, A2) detected → robot drives straight forward at attack speed
- **Side left sensor** (D3) detected only → robot steers left to face the opponent
- **Side right sensor** (D10) detected only → robot steers right to face the opponent
- **Multiple sensors** → the combination determines steering

### Beginner Tip
The Maker Object sensor has a limited detection range (typically 10–30cm depending on conditions). The robot will not "see" an opponent across the full ring — it needs to be relatively close. This is why Search mode is important to bring the robot near the opponent.

---

## State 5 — Attack Behavior

### What Happens
When an opponent is detected, the robot charges at the opponent at full speed, trying to push it out of the ring.

- Both motors run at **ATTACK_SPEED** (maximum speed, typically 255)
- The robot steers based on which sensors are triggered:
  - Front sensor only → drive straight
  - Front-left → steer left slightly while attacking
  - Front-right → steer right slightly while attacking
  - Side only → turn sharply to face and then charge

### When Does It Change?
- If opponent sensors all read `HIGH` (opponent lost) → return to **Search**
- If any edge sensor triggers → **immediately** transition to **Edge Detection / Backoff**

> ⚠️ **Important:** Edge detection must always take priority over attack. If the robot detects the ring edge while attacking, it must stop and back away immediately — even if it was about to win a push.

### Code Concept
```cpp
// Attack: both motors at full speed
motorL.setSpeed(ATTACK_SPEED);
motorR.setSpeed(ATTACK_SPEED);

// Check edge sensors every iteration — edge detection takes priority
if (edgeDetected()) {
  enterBackoffMode();
}
```

---

## State 6 — Edge Detection

### What Happens
One or both Maker Reflect sensors reads `LOW`, indicating the robot has reached or is near the white boundary line of the ring.

This triggers an immediate transition to Backoff/Turn — the robot must stop moving forward and retreat before it drives off the ring.

### Which Sensor Triggered?

| Sensor | Pin | Meaning |
|---|---|---|
| Left edge (D12) | `LOW` | Left side of robot is near the edge |
| Right edge (D11) | `LOW` | Right side of robot is near the edge |
| Both sensors | `LOW` | Robot is heading straight for the edge |

### Why Is This Critical?
If the robot crosses the white boundary line and falls or drives off the ring, it loses the match. Edge detection must run every loop and must always override other behaviors.

---

## State 7 — Backoff / Turn Behavior

### What Happens
After edge detection, the robot performs a recovery sequence:

1. **Stop** — immediately halt motor movement
2. **Reverse** — back away from the edge for a short duration (`BACKOFF_DELAY` milliseconds)
3. **Turn** — rotate away from the direction the edge was detected
4. **Resume search** — re-enter Search mode and continue looking for the opponent

### Turn Direction Logic
The turn direction after backoff alternates or is based on which edge sensor triggered:

| Edge Detected | Turn Direction |
|---|---|
| Left edge (D12) | Turn right |
| Right edge (D11) | Turn left |
| Both edges | Turn in alternating direction |

The sample code toggles the turn direction each time an edge is detected, so the robot does not keep retreating in the same direction repeatedly.

### Timing Parameters (Tunable — See Tuning Guide)
- `BACKOFF_DELAY` — how long to reverse after edge detection (e.g., 300ms)
- `TURN_DELAY` — how long to turn before resuming search (e.g., 400ms)

### Code Concept
```cpp
// Backoff sequence after edge detection
motorL.setSpeed(-BACKOFF_SPEED);    // Reverse
motorR.setSpeed(-BACKOFF_SPEED);
delay(BACKOFF_DELAY);

// Turn away from edge
if (edgeLeft) {
  motorL.setSpeed(TURN_SPEED);      // Turn right
  motorR.setSpeed(-TURN_SPEED);
} else {
  motorL.setSpeed(-TURN_SPEED);     // Turn left
  motorR.setSpeed(TURN_SPEED);
}
delay(TURN_DELAY);

// Resume search
```

---

## Full Behavior Flow Summary

```
Power on
  └─► WAIT (button not pressed)
         │
         ▼ (button pressed)
      START SEQUENCE
         │  - 5-second delay (competition rule)
         │  - 45° initial turn
         │  - drive forward 450ms
         ▼
      SEARCH (circular rotation)
         │  ← → no opponent → keep rotating
         │
         ▼ (opponent sensor LOW)
      ATTACK (full speed charge + steer)
         │  ← → opponent lost → back to SEARCH
         │
         ▼ (edge sensor LOW) — takes priority!
      BACKOFF (reverse + turn + resume search)
         │
         └─────────────────────────────────► back to SEARCH
```

---

## Important Beginner Notes

1. **Edge detection takes priority over everything.** Your robot must check edge sensors every single loop iteration, even while attacking.
2. **Sensor logic is active-low.** Both Maker Object and Maker Reflect sensors output `LOW` when triggered. A reading of `HIGH` means nothing detected. This is the opposite of what beginners often expect.
3. **The start delay is a competition requirement.** Do not reduce it below 5 seconds for actual matches.
4. **Motor direction depends on wiring.** If your robot drives backward when it should go forward, swap the motor wires on the terminal — do not try to fix it by changing code sign.
5. **The button pin must be confirmed before running.** See `auto-kit-sensor-map.md` for the known conflict.
