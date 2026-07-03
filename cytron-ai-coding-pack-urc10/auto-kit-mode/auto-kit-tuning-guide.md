# Auto-Kit Tuning Guide — 1KG Autonomous Sumo Robot Starter Kit using URC10

## Overview

Tuning is the process of adjusting your robot's speed, timing, and sensor response values so it performs better in the ring. This guide is written for beginners — you do not need to understand everything at once. Start with the basics and adjust one value at a time.

> ⚠️ **Safety First:** Always test with the robot's wheels lifted off the ground before placing it in the ring. See `auto-kit-safety-rules.md` before any power-on testing.

---

## How Tuning Works

The robot's behavior is controlled by a set of **named constants** defined at the top of the Arduino sketch using `#define`. Changing these values changes how the robot moves and responds — without needing to change the logic of your code.

Example constants you will find in the code:
```cpp
#define SEARCH_SPEED   80    // Speed during search rotation
#define ATTACK_SPEED   255   // Speed during opponent attack
#define BACKOFF_SPEED  150   // Speed when reversing from edge
#define BACKOFF_DELAY  300   // Time (ms) to reverse after edge detection
#define TURN_DELAY     400   // Time (ms) to turn after backing off
```

**Golden rule:** Change only ONE constant at a time. Test, observe the result, then decide if you need to change it further or move on to the next constant.

---

## Beginner Speed Tuning Overview

The motor speed range in the `CytronMotorDriver` library is:
- **0** = stopped
- **255** = full forward
- **-255** = full reverse

For competition, you want the right speed for each situation — too slow in attack means you get pushed out; too fast in search means you miss the opponent or overshoot the ring edge.

---

## 1. Search Speed Tuning

### What It Controls
How fast the robot rotates while searching for the opponent. During search, one motor is faster than the other, causing a circular scanning motion.

### Recommended Starting Value
```cpp
#define SEARCH_SPEED   80   // Beginner starting point
```

### How to Tune
| Value | Effect |
|---|---|
| Too low (< 40) | Robot rotates very slowly — may not complete a full scan before time runs out |
| Good range (60–120) | Robot rotates at a comfortable speed, scanning the ring steadily |
| Too high (> 180) | Robot rotates so fast it may miss detecting the opponent between sensor readings |

### Tuning Test
1. Lift the robot wheels off the ground
2. Upload code and press start
3. Observe how quickly the robot rotates
4. Adjust until it rotates at a steady, controlled speed

---

## 2. Attack Speed Tuning

### What It Controls
How fast the robot drives when it has detected an opponent. This is the pushing speed — higher means more force.

### Recommended Starting Value
```cpp
#define ATTACK_SPEED   255   // Full speed attack (recommended for competition)
```

### How to Tune
| Value | Effect |
|---|---|
| 150–200 | Moderate attack — safer for first tests, less pushing force |
| 200–255 | High attack speed — more pushing force, harder to stop |
| 255 | Maximum — full motor power |

### Beginner Advice
For your first few tests, start at `180` to confirm the robot charges in the correct direction before going to full speed. Once you confirm direction and behavior, increase to `255` for competition.

> ⚠️ **Lift the robot for first test.** Running at full attack speed on the floor before verifying direction can cause the robot to charge off the table or into walls. Always test with wheels off the ground first.

---

## 3. Backoff Speed Tuning

### What It Controls
How fast the robot reverses when it detects the ring edge. This should be fast enough to move away from the edge quickly, but not so fast that the robot bounces off the ring wall.

### Recommended Starting Value
```cpp
#define BACKOFF_SPEED  150   // Moderate reverse speed
```

### How to Tune
| Value | Effect |
|---|---|
| Too low (< 80) | Robot reverses slowly — might cross the line before it escapes |
| Good range (120–200) | Robot reverses firmly and cleanly |
| Too high (> 220) | Robot reverses so fast it might trigger the opposite edge sensor on a small ring |

---

## 4. Backoff Delay Tuning

### What It Controls
How long the robot reverses after edge detection, measured in milliseconds. This determines how far the robot travels backward before turning.

### Recommended Starting Value
```cpp
#define BACKOFF_DELAY  300   // 300 milliseconds = 0.3 seconds
```

### How to Tune
| Value | Effect |
|---|---|
| Too short (< 150ms) | Robot barely moves back before turning — may still be near the edge |
| Good range (250–400ms) | Robot backs up a safe distance before turning |
| Too long (> 600ms) | Robot reverses too far — may hit the opposite edge or give the opponent too much time |

### Tuning Test
Place the robot near the edge of a ring (or mark a boundary on the floor). Let it detect the edge. Observe how far it reverses. Adjust the delay until it reliably clears the boundary line.

---

## 5. Turn Delay Tuning

### What It Controls
How long the robot turns after backing off from the edge. This determines how much the robot rotates before resuming the search pattern.

### Recommended Starting Value
```cpp
#define TURN_DELAY     400   // 400 milliseconds = 0.4 seconds
```

### How to Tune
| Value | Effect |
|---|---|
| Too short (< 150ms) | Robot barely turns — may face the same edge again immediately |
| Good range (300–500ms) | Robot rotates enough to face a different direction |
| Too long (> 700ms) | Robot spends too long turning — gives the opponent time to push it |

### Tuning Test
After a backoff+turn sequence, the robot should face roughly 90–180 degrees away from where the edge was. Adjust until the turn reliably points the robot back toward the ring center.

---

## 6. Sensor Threshold / Timing Tuning

### Maker Object Sensor (Opponent Detection)
The Maker Object sensor is a digital sensor with a built-in potentiometer for sensitivity adjustment. It outputs `LOW` when an object is within range.

**Physical tuning (hardware):**
- Each Maker Object sensor has a small blue potentiometer screw on the PCB
- Turning the screw clockwise typically increases detection range, counter-clockwise decreases it
- Set the sensitivity so the sensor reliably detects a robot at 15–20cm range without false triggers from the ring floor

**Software timing (debounce):**
If the sensor gives false or flickering readings, you can add a short delay or debounce:
```cpp
// Simple debounce: only react if sensor reads LOW for 2 consecutive checks
if (digitalRead(OPPONENT_FC) == LOW && digitalRead(OPPONENT_FC) == LOW) {
  // Attack
}
```
This is not always necessary but helps with electrically noisy environments.

---

### Maker Reflect Sensor (Edge Detection)
The Maker Reflect sensor is also a digital sensor with a sensitivity potentiometer.

**Physical tuning (hardware):**
- Adjust the sensitivity so the sensor reliably detects the white boundary line on the ring
- Test by sliding the sensor over a white/black boundary — it should clearly switch between states
- Do not set sensitivity too high or it will trigger on slight floor colour variations (false edge detection)

**Mounting height:**
The Maker Reflect sensor must be mounted close to the floor — ideally within 5–15mm of the ring surface. Too high and it will not reliably detect the white line.

---

## Full Tuning Checklist

Use this checklist before competition:

- [ ] Search speed gives controlled, steady circular rotation
- [ ] Attack speed confirmed in direction (forward = charges toward opponent)
- [ ] Backoff distance sufficient to clear the ring boundary line
- [ ] Turn angle sufficient to avoid re-detecting the same edge immediately
- [ ] Maker Object sensor sensitivity tested — detects opponent at appropriate range
- [ ] Maker Reflect sensor sensitivity tested — detects white line reliably
- [ ] Maker Reflect sensor mounting height verified (close to floor)
- [ ] All tests performed first with robot lifted off ground before ring testing
- [ ] Start button confirmed working with correct pin (see sensor map)
- [ ] 5-second start delay confirmed for competition rules

---

## Quick Reference: Default Tuning Values

| Constant | Starting Value | Range |
|---|---|---|
| `SEARCH_SPEED` | 80 | 40 – 150 |
| `ATTACK_SPEED` | 255 | 150 – 255 |
| `BACKOFF_SPEED` | 150 | 80 – 220 |
| `BACKOFF_DELAY` | 300ms | 150 – 600ms |
| `TURN_DELAY` | 400ms | 150 – 700ms |

Adjust these in the `#define` section at the top of your sketch. Never use raw numbers directly in the motor speed calls — always use named constants.
