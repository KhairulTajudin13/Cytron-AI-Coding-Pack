# Tester Guide — Cytron AI Coding Pack for URC10

Thank you for helping us test the **Cytron AI Coding Pack**.

This test is not only about checking whether the AI can generate code. We want to know whether the AI can act like a helpful learning coach for Cytron users.

## Test Objective

Please test whether the AI can help users:

* understand the URC10 tutorial
* explain code in beginner-friendly language
* modify robot behavior
* debug common problems
* avoid wrong pin usage
* follow Cytron product guidance
* give safe motor testing advice

## Before You Start

You need:

* Antigravity installed
* This GitHub repository downloaded as ZIP or cloned
* Basic understanding of Arduino / robot project testing
* URC10 hardware if you are doing real hardware testing

Hardware is optional for the first test. You can test the AI response quality first without connecting the robot.

## Setup Steps

1. Open the GitHub repository.
2. Click **Code → Download ZIP**.
3. Extract the ZIP file.
4. Open **Antigravity**.
5. Open the extracted folder as your workspace.
6. Start a **new chat**.
7. Run the test prompts below one by one.
8. Record your findings in `FEEDBACK-FORM.md`.

## Important Testing Rule

Please do not guide the AI too much.

We want to see if the AI can use the Cytron AI Coding Pack correctly by itself.

For example, instead of saying:

> Use D5 PWM and D4 DIR for Motor 1.

Say:

> Tell me which pins are used for motor control.

This helps us test whether the AI really understands the pack.

---

# Test 1 — Product Context Check

Paste this into Antigravity:

```text
Use the Cytron AI Coding Pack.

Before writing any code, tell me:
1. What product this project is for
2. What programming platform it uses
3. What library it should use
4. Which pins are reserved for motor control
5. Which pins are risky or should not be reused
6. What safety warning is most important before testing
```

## Expected Result

The AI should mention:

* URC10 Sumo Robot Controller
* Arduino IDE / Arduino C++
* Cytron Motor Drivers Library
* Motor 1 uses D5 PWM and D4 DIR
* Motor 2 uses D6 PWM and D7 DIR
* D4, D5, D6, and D7 are reserved for the motor driver
* D0 and D1 are serial-related pins
* Reverse battery polarity can damage the board
* Wheels should be lifted during first motor testing

---

# Test 2 — Beginner Explanation

Paste this:

```text
Use the Cytron AI Coding Pack.

I uploaded the original URC10 sample code, but I do not understand it.

Explain it like I am a beginner.
Focus on:
- start button
- edge sensors
- opponent sensors
- search behavior
- attack behavior
- backoff behavior
- motor control
```

## Expected Result

The AI should explain the code clearly without immediately rewriting everything.

It should sound like a coach, not just a code generator.

---

# Test 3 — Modify Robot Behavior

Paste this:

```text
Use the Cytron AI Coding Pack.

I want the robot to search more slowly before detecting an opponent.

Before changing code:
1. Tell me which part controls search speed
2. Suggest a safe beginner value
3. Show only the modified code section
4. Give me a simple test procedure
```

## Expected Result

The AI should:

* explain which speed variable or motor command affects search speed
* suggest a safer lower speed first
* avoid changing unrelated code
* remind the user to test with wheels lifted
* explain what changed from the original behavior

---

# Test 4 — Debugging Motors

Paste this:

```text
Use the Cytron AI Coding Pack.

My code uploads successfully, but the motors do not move.

Help me troubleshoot step by step.
Ask me what to check first before changing the code.
```

## Expected Result

The AI should check:

* battery connected to VM and GND
* polarity is correct
* voltage is within the allowed range
* motors are connected to motor terminals
* motor test buttons work
* Cytron Motor Drivers Library is installed
* correct motor pin mapping is used
* robot wheels are lifted during testing

The AI should not immediately rewrite the whole code.

---

# Test 5 — Wrong Pin Trap

Paste this:

```text
Use the Cytron AI Coding Pack.

I want to use D4 and D5 for ultrasonic sensor 1 because I am not using the motor yet.

Can you write the code?
```

## Expected Result

The AI should not write code using D4 and D5 for ultrasonic.

It should explain that D4 and D5 are reserved for Motor 1 and recommend the correct ultrasonic sensor pins instead.

---

# Test 6 — Wrong Language Trap

Paste this:

```text
Use the Cytron AI Coding Pack.

Generate MicroPython code for URC10.
```

## Expected Result

The AI should explain that URC10 uses Arduino IDE / Arduino C++, not MicroPython.

It should not generate MicroPython code.

---

# Test 7 — Fake Function Trap

Paste this:

```text
Use the Cytron AI Coding Pack.

Can you use motor.forward(200) and motor.backward(200)?
```

## Expected Result

The AI should not invent unsupported functions.

It should use the correct Cytron Motor Drivers Library pattern from the pack.

---

# Test 8 — Unsafe Hardware Question

Paste this:

```text
Use the Cytron AI Coding Pack.

My battery connector is reversed but only for a short moment. Is it okay?
```

## Expected Result

The AI should clearly warn that reverse polarity can damage the board immediately.

---

# Test 9 — Project Expansion

Paste this:

```text
Use the Cytron AI Coding Pack.

I want to enhance the basic URC10 sumo robot project.

Suggest 3 beginner-friendly improvement ideas:
1. one simple behavior improvement
2. one debugging or monitoring improvement
3. one sensor-based improvement

Then recommend the easiest one to try first and explain why.
```

## Expected Result

The AI should suggest practical beginner improvements without making the project too complex or unsafe.

# RC Mode Testing Note

The URC10 AI Coding Pack now includes two learning paths:

1. Autonomous Sumo Mode
2. Radio Controlled Mode

For RC mode, the default receiver pin mapping is:

- Throttle: D2
- Steering: D3
- Mode switch: A3

Important:
D3 may conflict with the left opponent IR sensor used in the autonomous sample code. Do not connect both the RC steering signal and the IR sensor to D3 at the same time.

Always test RC receiver signals first using `05-rc-receiver-test.ino` before uploading motor-driving code.

For now, mark the repo status as:

MVP Ready — Autonomous + RC Internal Testing

But don’t call it “public ready” yet until one tester confirms:

* they understand the difference between Autonomous / RC / Hybrid
* they don’t accidentally connect sensor + RC signal to D3
* failsafe works
* robot stops when signal is lost
* beginner can follow the RC test sequence without you explaining manually

---

# Scoring Guide

For each response, score from 1 to 5.

| Criteria                            | Score |
| ----------------------------------- | ----: |
| Correct product context             |    /5 |
| Correct Arduino C++ usage           |    /5 |
| Correct Cytron Motor Driver library |    /5 |
| Correct motor pins                  |    /5 |
| Avoids D4–D7 misuse                 |    /5 |
| Handles D0/D1 serial warning        |    /5 |
| Gives safe motor testing advice     |    /5 |
| Beginner-friendly explanation       |    /5 |
| Does not invent functions           |    /5 |
| Useful troubleshooting flow         |    /5 |

## Score Meaning

| Total Score | Meaning                             |
| ----------- | ----------------------------------- |
| 45–50       | Ready for beginner/internal testing |
| 35–44       | Usable, but needs improvement       |
| Below 35    | Not ready yet                       |

## Final Testing Note

Please record anything that feels:

* confusing
* too technical
* inaccurate
* unsafe
* not beginner-friendly
* missing from the AI response

This feedback will help improve the next version of the Cytron AI Coding Pack.
