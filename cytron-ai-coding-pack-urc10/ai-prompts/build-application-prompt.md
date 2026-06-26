# Build Application Prompt — Advanced Sumo Robot Behaviour

**Who this is for:** Your basic sumo robot works. Now you want to build a smarter, more capable sumo robot — with better attack logic, smarter searching, side sensor tracking, timed strategies, or competition-ready features.

---

## How to Use This Prompt

1. Copy the full prompt block below.
2. Fill in the `[DESCRIBE YOUR GOAL]` section with what you want to build.
3. Paste it into your AI coding assistant.
4. Review the explanation before accepting any generated code.

---

## Prompt

```
You are helping me build a more advanced sumo robot behaviour for the Cytron URC10 Sumo Robot Controller.

Before writing any code, please read the following files from my Cytron AI Coding Pack:
- product-context.md    (URC10 hardware purpose and capabilities)
- pin-map.md            (all confirmed sensor and motor pin assignments)
- library-reference.md  (only setSpeed() is confirmed — do not use invented functions)
- safety-rules.md       (all generated code must comply with these safety rules)

My hardware:
- Board: Cytron URC10 (Arduino Uno compatible, ATmega328P)
- Language: Arduino C/C++
- Motor Library: Cytron Motor Drivers Library
- Motor Left:  CytronMD motorL(PWM_DIR, 5, 4);
- Motor Right: CytronMD motorR(PWM_DIR, 6, 7);
- D4, D5, D6, D7 are RESERVED for the motor driver — do not assign them to anything else

Available sensors (all INPUT_PULLUP, active-low — triggered = LOW):
- EDGE_L      (D12): Left edge/floor sensor
- EDGE_R      (D11): Right edge/floor sensor
- OPPONENT_L  (D3) : Side opponent sensor — left
- OPPONENT_R  (D10): Side opponent sensor — right
- OPPONENT_FL (A2) : Front-left opponent sensor
- OPPONENT_FC (A1) : Front-center opponent sensor
- OPPONENT_FR (A0) : Front-right opponent sensor
- BUTTON      (D13): Start/stop button
- LED0        (D0) : Onboard LED (active-low)
- LED1        (D1) : Onboard LED (active-low)

My goal:
[DESCRIBE WHAT YOU WANT TO BUILD — see examples below]

Please respond as follows:
1. EXPLAIN the approach you will take before writing any code.
   Describe how the logic will work in plain language.
2. List any assumptions you are making about hardware or sensors.
3. Write the complete Arduino sketch with:
   - Clear comments on every function and key logic block
   - Named constants for all speed and timing values (not magic numbers)
   - Testing steps as comments at the top of the file
   - A safety reminder comment block at the top
4. After the code, provide:
   - Step-by-step testing instructions (start with wheels lifted)
   - Two or three things that might go wrong and how to fix them

Rules:
- Do not invent pin numbers. Only use pins listed above.
- Do not invent library functions. Only use setSpeed() with values -255 to 255.
- Do not use D4, D5, D6, or D7 for sensors or any other purpose.
- If a feature requires hardware not on the URC10, say so clearly — do not fake it in code.
- Explain before you generate. Never generate code without first explaining the plan.
```

---

## Example Goals — Copy One Into the Prompt

### Smarter Attack Logic
> *"My current code only drives straight when it sees the opponent. I want the robot to track the opponent using all 5 opponent sensors — steering left or right to keep the opponent in front-center before charging."*

### Side Sensor Pursuit
> *"Currently I only use the 3 front sensors. I want to add logic that uses the two side sensors (D3 and D10) to continue tracking the opponent if it moves to the side, then re-center before attacking."*

### Competition-Ready with LED Countdown
> *"I want a 5-second countdown before the robot starts. During the countdown, flash LED0 and LED1 alternately once per second, then turn both on when the robot starts moving."*

### Alternating Search Strategy
> *"My robot searches in only one direction. I want it to alternate search direction after every edge event — search left after backing off the right edge, and search right after backing off the left edge."*

### Aggressive Start Routine
> *"I want a smarter start routine. Instead of just turning and going straight, I want the robot to spin a full 360 degrees slowly while scanning for the opponent, then attack immediately if found."*

---

## After Getting the Code

- Always read the explanation section before uploading.
- Test all motor movements with **wheels lifted** first.
- Use `02-sensor-test.ino` to confirm any sensors that are new to your code.
- Refer to `troubleshooting.md` if something behaves unexpectedly.
- Refer to `safety-rules.md` — especially the competition 5-second delay rule.
