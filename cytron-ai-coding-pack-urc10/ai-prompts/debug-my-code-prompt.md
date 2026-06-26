# Debug My Code Prompt — My Robot Uploads But Behaves Wrongly

**Who this is for:** You can upload code to the URC10 without errors. But when you run the robot, the motors, sensors, or overall behaviour is not what you expected.

> **First:** Before using this prompt, try uploading `02-sensor-test.ino` from `code-examples/` to confirm your sensors work. This will isolate whether the problem is hardware wiring or code logic.

---

## How to Use This Prompt

1. Copy the full prompt block below.
2. Fill in both `[...]` sections: paste your code and describe the problem.
3. Include any Arduino IDE error messages if relevant.
4. Paste it into your AI coding assistant.

---

## Prompt

```
You are helping me debug my Arduino code for the Cytron URC10 Sumo Robot Controller.

Before diagnosing, please read the following files from my Cytron AI Coding Pack:
- product-context.md    (URC10 hardware context)
- pin-map.md            (correct pin assignments to cross-check against my code)
- library-reference.md  (correct motor library usage)
- safety-rules.md       (safety constraints — do not suggest fixes that violate these)

My hardware:
- Board: Cytron URC10 (Arduino Uno compatible, ATmega328P)
- Language: Arduino C/C++
- Motor Library: Cytron Motor Drivers Library
- Motor Left:  CytronMD motorL(PWM_DIR, 5, 4);
- Motor Right: CytronMD motorR(PWM_DIR, 6, 7);
- D4, D5, D6, D7 are reserved for the motor driver — do not reassign them
- All sensors use INPUT_PULLUP and are active-low (triggered = LOW)

Here is my code:
[PASTE YOUR FULL CODE HERE]

The problem I am experiencing:
[DESCRIBE EXACTLY WHAT IS HAPPENING — be as specific as possible]

What I expected to happen:
[DESCRIBE THE CORRECT BEHAVIOUR YOU WANTED]

Arduino IDE errors (if any):
[PASTE ERROR MESSAGES, OR WRITE "No errors — code uploads successfully"]

Please help me by:
1. Identifying the most likely cause of the problem.
2. Explaining WHY this causes the symptom I described.
3. Providing a corrected version of only the affected lines or functions.
4. Including a step-by-step testing procedure to confirm the fix worked.

Rules for your response:
- Do not change or remove unrelated parts of the code.
- Do not invent new pin numbers. Only use pins confirmed in pin-map.md.
- Do not use library functions other than setSpeed().
- If you are not certain about the cause, list two or three possible causes ranked by likelihood.
- End your response with a troubleshooting checklist I can follow.
```

---

## Quick Symptom Guide — Fill In the Problem Section

| Symptom | What to write in "The problem I am experiencing" |
|---|---|
| Robot doesn't move | *"After pressing the button, nothing happens. Motors do not spin."* |
| One motor only | *"Only the left / right motor spins. The other does nothing."* |
| Drives off the ring | *"Robot does not stop when it reaches the edge. It drives off."* |
| Spins in circles | *"Robot spins continuously in one direction and never drives straight."* |
| Never detects opponent | *"Robot keeps searching even when I put an object directly in front of it."* |
| Attacks phantom targets | *"Robot charges forward even when there is no opponent in front."* |
| Won't start after button | *"I press the button but the robot does not respond at all."* |
| Wrong motor direction | *"The left motor spins backward when it should spin forward."* |

---

## Before You Submit — Checklist

Run through this before pasting the prompt:

- [ ] Ran `01-motor-test.ino` — confirmed both motors work individually?
- [ ] Ran `02-sensor-test.ino` — confirmed each sensor shows TRIGGERED in Serial Monitor?
- [ ] Checked `pin-map.md` — are sensor pins in my code correct?
- [ ] Battery connected and within 8V–25V range?
- [ ] Board selected as **Arduino Uno** in IDE?
- [ ] Correct COM port selected?
