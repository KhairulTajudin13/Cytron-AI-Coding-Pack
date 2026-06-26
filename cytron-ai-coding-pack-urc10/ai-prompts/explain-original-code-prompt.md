# Explain Original Code Prompt — Section-by-Section Walkthrough

**Who this is for:** You have the original `URC10SumoRobot.ino` sample code and want the AI to walk through it with you, section by section, so you understand every part before modifying anything.

---

## How to Use This Prompt

1. Open `source-docs/URC10SumoRobot.ino` in this pack (or in Arduino IDE).
2. Select all the code and copy it.
3. Copy the prompt block below.
4. Paste the prompt into your AI coding assistant.
5. Paste the copied code into the `[PASTE CODE HERE]` section at the bottom.
6. Send the message and read through the explanation carefully.

---

## Prompt

```
You are helping me understand the original URC10 sample code for the Cytron URC10 Sumo Robot Controller.

Before explaining anything, please read the following files from my Cytron AI Coding Pack:
- product-context.md    (what the URC10 is — use this to frame your explanations)
- pin-map.md            (use this to verify every pin reference in the code)
- library-reference.md  (use this to explain motor library functions accurately)
- safety-rules.md       (reference this when explaining any power or motor code)

My hardware:
- Board: Cytron URC10 (Arduino Uno compatible, ATmega328P)
- Language: Arduino C/C++
- Motor Library: Cytron Motor Drivers Library

I want you to explain the code I am pasting below, section by section.

For each section, explain:
1. What this section does (in plain beginner language)
2. Why it exists — what robot behaviour it enables
3. Any Arduino concepts a beginner might not know (e.g. INPUT_PULLUP, active-low,
   #define, uint8_t, millis(), while loops, XOR toggle)
4. Whether there are any risks, limitations, or "gotchas" a beginner should know about

After explaining all sections, please provide:
A. A summary table: one row per function with its name, purpose, and when it runs
B. A simple text flowchart of what the robot does from power-on to end of match
C. A list of 3–5 things a beginner could safely change to experiment with the code,
   and what effect each change would have
D. A list of things in the code that should NOT be changed by a beginner, and why

Rules for your explanation:
- Use simple language. Assume I have never written Arduino code before.
- Do not change any of the code unless I ask you to.
- Do not invent pin numbers or functions. Verify everything against pin-map.md and library-reference.md.
- If something in the code is ambiguous or could be improved, flag it clearly with "NOTE:" or "CAUTION:".
- Include a reminder about safe testing from safety-rules.md at the end.

Here is the original sample code:
[PASTE THE FULL URC10SumoRobot.ino CODE HERE]
```

---

## What to Paste

Open this file from your pack:

```
source-docs/URC10SumoRobot.ino
```

Select all (Ctrl+A), copy (Ctrl+C), then paste it after the prompt.

---

## Suggested Follow-Up Questions

After the AI explains the code, try asking these one at a time:

- *"Explain the `searchDir ^= 1` line. What does XOR toggle mean and why is it used here?"*
- *"Why does `startRoutine()` turn 45 degrees first instead of going straight? What sumo strategy does this represent?"*
- *"The `while (digitalRead(OPPONENT_FC))` inside `attack()` has a 400ms timeout. What happens if the timeout is removed?"*
- *"What is the difference between `millis()` and `delay()`? Why does the code use both?"*
- *"If I want to make the robot search in the opposite direction by default, which single line do I change?"*
- *"The sample code uses a 1-second start delay. Most competitions require 5 seconds. Show me exactly which line to change."*

---

## After the Explanation

Once you understand the code, use these prompts for your next step:

| Goal | Prompt to Use |
|---|---|
| Change a specific value or behaviour | `modify-code-prompt.md` |
| Add smarter attack or search logic | `build-application-prompt.md` |
| Robot is misbehaving after a change | `debug-my-code-prompt.md` |
