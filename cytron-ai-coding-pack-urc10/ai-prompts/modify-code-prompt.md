# Modify Code Prompt — Change My URC10 Robot Behaviour

**Who this is for:** Your robot is working. Now you want to change something specific — such as speed, start delay, search direction, or how it responds to sensors.

---

## How to Use This Prompt

1. Copy the full prompt block below.
2. Fill in the two sections marked `[...]`.
3. Paste it into your AI coding assistant.
4. The AI will explain the change first, then provide updated code.

---

## Prompt

```
You are helping me modify the Arduino code for my Cytron URC10 Sumo Robot Controller.

Before making any changes, please read the following files from my Cytron AI Coding Pack:
- product-context.md    (what the URC10 is and its capabilities)
- pin-map.md            (confirmed pin assignments — do not deviate from these)
- library-reference.md  (only use setSpeed() from the Cytron Motor Drivers Library)
- safety-rules.md       (safety constraints to respect in all generated code)

My hardware:
- Board: Cytron URC10 (Arduino Uno compatible, ATmega328P)
- Language: Arduino C/C++
- Motor Library: Cytron Motor Drivers Library
- Motor Left:  CytronMD motorL(PWM_DIR, 5, 4);
- Motor Right: CytronMD motorR(PWM_DIR, 6, 7);
- D4, D5, D6, D7 are reserved for the motor driver — do not assign them to anything else
- All sensors use INPUT_PULLUP and are active-low (triggered = LOW)

Here is my current code:
[PASTE YOUR FULL CODE HERE]

I want to make the following change:
[DESCRIBE EXACTLY WHAT YOU WANT TO CHANGE — examples below]

Rules for your response:
1. Explain what the change involves and why BEFORE showing any modified code.
2. Show only the lines or functions that changed — not the entire file unless necessary.
3. Do not change or remove any other part of the code.
4. Do not invent new pin numbers. Use only pins from pin-map.md.
5. Do not use library functions other than setSpeed(). Do not invent new ones.
6. After showing the change, include:
   - A testing step: how to verify the change worked correctly.
   - A safety reminder relevant to this specific change.
```

---

## Example Changes — Copy One Into the Prompt

| What You Want | What to Write in the Prompt |
|---|---|
| Longer start delay | *"Change the start delay from 1 second to 5 seconds. I am entering a competition."* |
| Slower search | *"Reduce the search arc speed so the robot turns more slowly while looking for opponents."* |
| Faster attack | *"Increase the attack speed to full speed (255) only when OPPONENT_FC is triggered."* |
| Search direction | *"Make the robot search clockwise (to the right) instead of counter-clockwise."* |
| Longer backoff | *"Make the robot reverse for longer before turning when an edge is detected."* |
| LED countdown | *"Flash LED0 and LED1 alternately 5 times before the robot starts moving."* |
| Stop on second press | *"Make the robot stop permanently if the Start button is pressed a second time during the match."* |

---

## Tips

- The simpler you describe the change, the more accurate the AI response will be.
- Ask for one change at a time rather than multiple changes in a single prompt.
- Always test with wheels lifted off the ground after any motor code change.
- Refer to `troubleshooting.md` if the robot behaves unexpectedly after the change.
