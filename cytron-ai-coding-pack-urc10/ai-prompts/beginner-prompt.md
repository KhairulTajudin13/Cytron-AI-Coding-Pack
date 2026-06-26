# Beginner Prompt — Understanding My URC10 Sumo Robot Code

**Who this is for:** You have completed the official URC10 tutorial. Your robot uploads and runs. Now you want to understand what the code actually does.

---

## How to Use This Prompt

1. Copy the full prompt block below.
2. Paste it into your AI coding assistant (e.g. Antigravity).
3. Then paste your code (or the original `URC10SumoRobot.ino`) below it.
4. Ask follow-up questions as needed.

---

## Prompt

```
You are helping me learn Arduino programming using the Cytron URC10 Sumo Robot Controller.

Before answering, please read the following files from my Cytron AI Coding Pack:
- product-context.md    (what the URC10 is and who it is for)
- pin-map.md            (which pins are assigned to which sensors and motors)
- library-reference.md  (how the Cytron Motor Drivers Library works)
- safety-rules.md       (electrical and testing safety)

My hardware:
- Board: Cytron URC10 (Arduino Uno compatible, ATmega328P)
- Language: Arduino C/C++
- Motor Library: Cytron Motor Drivers Library
- Motor Left:  CytronMD motorL(PWM_DIR, 5, 4);
- Motor Right: CytronMD motorR(PWM_DIR, 6, 7);
- All sensors use INPUT_PULLUP and are active-low (triggered = LOW)

I have just completed the official URC10 getting-started tutorial. I can upload code and
my robot runs. Now I want to understand the code I uploaded.

Please help me by:
1. Explaining the overall structure of the code — what are the main sections?
2. Describing what happens from the moment I press the Start button to when the robot moves.
3. Explaining each function one at a time, in plain beginner language.
4. Defining any Arduino concepts that a beginner might not know (e.g. INPUT_PULLUP, active-low,
   setSpeed, digitalRead, delay).

Rules for your answers:
- Explain first, change code later (only if I ask you to change something).
- Do not invent pin numbers. Only use pins confirmed in pin-map.md.
- Do not invent library functions. Only use setSpeed() as shown in library-reference.md.
- If anything is unclear or uncertain, say so rather than guessing.
- Include a note at the end about safe testing practices from safety-rules.md.

Here is the code I want you to explain:
[PASTE YOUR CODE HERE]
```

---

## Suggested Follow-Up Questions

After the AI explains the code, try asking:

- *"What does `!digitalRead(EDGE_L)` mean? Why the exclamation mark?"*
- *"What is the difference between `setup()` and `loop()`?"*
- *"Why does the robot wait for the button to be released before starting?"*
- *"What would happen if I removed the `delay(1000)` in the start routine?"*
- *"Can you draw the logic of the main loop as a simple text flowchart?"*
