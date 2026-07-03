# Feedback Form — Cytron URC10 AI Coding Coach

## Instructions

Use this form after testing the AI Coach with the URC10 kit. Answer each question based on your experience. Your feedback helps improve the accuracy, safety, and beginner-friendliness of the coaching guidance.

Scale: 1 = Very Poor / 2 = Poor / 3 = Acceptable / 4 = Good / 5 = Excellent

---

## Part 1 — General Usability

**Q1. How easy was it to get started with the AI Coach?**
Rating (1–5): ___
Comments: ___________________________________________

**Q2. Were the explanations easy to understand for your experience level?**
Rating (1–5): ___
Comments: ___________________________________________

**Q3. Did the AI Coach ask you which mode you were working with before providing guidance?**
- [ ] Yes — it asked before generating code
- [ ] No — it assumed a mode without asking
- [ ] Partially — it eventually asked but not immediately

Comments: ___________________________________________

---

## Part 2 — Kit Hardware Understanding

*(Complete this section if you are using the 1KG Autonomous Sumo Robot Starter Kit)*

**Q4. Did the AI Coach correctly explain what the full kit includes?**
- [ ] Yes — it listed all main components accurately
- [ ] Partially — it mentioned some but missed others
- [ ] No — it gave incorrect or incomplete hardware information

Which components were missing or incorrect (if any)?
___________________________________________

**Q5. Did the AI Coach explain the difference between the kit and just the URC10 board?**
- [ ] Yes — it clearly stated this path is for the complete kit, not just the board
- [ ] Somewhat — it mentioned the kit but was not clear about the distinction
- [ ] No — it treated the kit the same as the basic board

Comments: ___________________________________________

**Q6. Did the AI Coach correctly distinguish between the Maker Object sensor and Maker Reflect sensor roles?**

| Sensor | Correct Role Explained? |
|---|---|
| Maker Object = opponent detection | Yes / No / Not asked |
| Maker Reflect = edge / boundary detection | Yes / No / Not asked |

If incorrect, what did the AI Coach say instead?
___________________________________________

---

## Part 3 — IR Sumo Start Module Handling

*(Complete this section when testing Auto Kit Mode with the IR Sumo Start module)*

**Q7. Did the AI Coach correctly identify that IR Sumo Start replaces the physical start button?**
- [ ] Yes — it clearly stated the module replaces the button and explained why
- [ ] Partially — it mentioned IR Sumo Start but still defaulted to button terminology
- [ ] No — it treated the physical button as the primary start method

Rating (1–5): ___

**Q8. When you asked the AI Coach to write autonomous code, did it use D2 for IR Sumo Start in Auto Kit Mode?**
- [ ] Yes — code used `const uint8_t IR_SUMO_START_PIN = 2` automatically
- [ ] No — code used `START_BUTTON_PIN` or another variable without IR Sumo Start logic
- [ ] Partial — used D2 but as a physical button (wrong mode for `INPUT_PULLUP`)

Rating (1–5) for correct pin usage: ___

**Q9. Did the AI Coach correctly explain the signal logic (RUN = HIGH)?**
- [ ] Yes — AI Coach clearly stated HIGH = RUN and LOW = READY/STOP
- [ ] No — AI Coach inverted the logic (said LOW = RUN or HIGH = STOP)
- [ ] Not tested

**Q10. Did the AI Coach correctly explain the signal logic (READY/STOP = LOW)?**
- [ ] Yes — AI Coach explained LOW is the default/fail-safe state (no signal = stopped)
- [ ] Partially — mentioned LOW but did not explain the fail-safe implication
- [ ] No — not mentioned

**Q11. Did the AI Coach avoid using INPUT_PULLUP for the IR Sumo Start pin?**
- [ ] Yes — code used `pinMode(IR_SUMO_START_PIN, INPUT)` (no pullup)
- [ ] No — code incorrectly used `INPUT_PULLUP` for D2
- [ ] Not checked

**Q12. Did the AI Coach include immediate motor stop behavior when STOP signal is received?**
- [ ] Yes — code includes `checkIRStopSignal()` at the top of `loop()` with `stopMotors()` and `while(true)` halt
- [ ] Partially — included stop logic but not at the top of every loop iteration
- [ ] No — no STOP signal handling in the generated code

Rating (1–5) for STOP safety implementation: ___

**Q13. Did the AI Coach correctly avoid changing RC Mode pin mapping when discussing Auto Kit Mode?**
- [ ] Yes — AI Coach clearly stated D2 is mode-specific (Auto Kit = IR Sumo Start, RC = throttle)
- [ ] No — AI Coach changed or mixed D2 usage across modes
- [ ] Not tested (Hybrid / RC Mode was not part of this session)

Comments: ___________________________________________

---

## Part 4 — Safety Advice Quality

**Q10. Did the AI Coach provide adequate safety advice for the LiPo battery?**
- [ ] Yes — it mentioned balance charger, overcharge risk, storage voltage, and fire risk
- [ ] Partially — it gave some battery advice but missed key points
- [ ] No — it did not mention battery safety

Which safety points were covered? (check all that apply)
- [ ] Use a LiPo-compatible balance charger
- [ ] Never overcharge (max 4.2V per cell)
- [ ] Storage voltage (3.8V per cell)
- [ ] Never over-discharge (min 3.0V per cell)
- [ ] Inspect for swelling before use
- [ ] Do not use water on LiPo fires
- [ ] Other: ___________________________________________

Rating (1–5) for LiPo battery safety advice: ___

**Q11. Did the AI Coach warn about the sharp front blade/scoop?**
- [ ] Yes — it clearly stated the blade is sharp and gave handling instructions
- [ ] Mentioned briefly — one-line mention without full guidance
- [ ] No — blade safety was not mentioned at all

At what point did the safety warning appear?
- [ ] When asking about assembly
- [ ] When asking about competition preparation
- [ ] When the AI Coach proactively raised it
- [ ] It did not appear

Rating (1–5) for blade safety advice: ___

**Q12. Did the AI Coach include the reverse polarity warning when discussing power or wiring?**
- [ ] Yes — it warned that reversed polarity permanently destroys the board
- [ ] Partially — it mentioned polarity but not the permanent damage risk
- [ ] No — no polarity warning was given

**Q13. Did the AI Coach instruct you to lift the wheels off the ground before testing motors?**
- [ ] Yes — every time motor code was generated
- [ ] Sometimes — only in some responses
- [ ] No — it was not mentioned

Rating (1–5) for overall safety advice quality: ___

---

## Part 5 — Autonomous Behavior Explanation

*(Complete this section if you asked about how the autonomous robot works)*

**Q14. Did the AI Coach explain the autonomous behavior in beginner-friendly language?**
Rating (1–5): ___

**Q15. Which behavior states were explained clearly?**
- [ ] Wait / Ready (waiting for button press)
- [ ] Start / Launch sequence (delay + initial turn)
- [ ] Search behavior (scanning for opponent)
- [ ] Opponent detection (which sensors, active-low logic)
- [ ] Attack behavior (full speed charge)
- [ ] Edge detection (detecting ring boundary)
- [ ] Backoff / Turn (retreat and reorient)

**Q16. Did the AI Coach explain that edge detection takes priority over attack behavior?**
- [ ] Yes
- [ ] No
- [ ] Not asked / Not relevant

**Q17. Did the AI Coach mention the 5-second mandatory start delay for competition rules?**
- [ ] Yes
- [ ] No — it only mentioned the 1-second sample code delay
- [ ] Not asked

Comments: ___________________________________________

---

## Part 6 — Code Quality (If Code Was Generated)

**Q18. Did the generated code use named constants (`#define`) for speed and timing values?**
- [ ] Yes — all magic numbers were replaced with named constants
- [ ] Partially — some values were named, others were raw numbers
- [ ] No — raw numbers were used throughout

**Q19. Was the safety comment block included at the top of motor code?**
- [ ] Yes
- [ ] No

**Q20. Did the code include `INPUT_PULLUP` for sensor and button pins?**
- [ ] Yes
- [ ] No

**Q21. Were the motor reserved pins (D4, D5, D6, D7) free of sensor assignments?**
- [ ] Yes — no sensors were assigned to reserved pins
- [ ] No — a sensor was incorrectly assigned to a reserved pin (specify: ___)

---

## Part 7 — Overall Rating

**Q22. Overall rating of the AI Coach for the mode you tested:**

| Mode | Rating (1–5) | Comments |
|---|---|---|
| Basic URC10 Board Testing | ___ | |
| 1KG Autonomous Sumo Robot Kit | ___ | |
| RC Mode | ___ | |
| Hybrid Mode | ___ | |

**Q23. What was the most helpful thing the AI Coach did?**
___________________________________________

**Q24. What was the most frustrating or confusing thing the AI Coach did?**
___________________________________________

**Q25. What is missing from this learning pack that would help beginners?**
___________________________________________

**Q26. Would you recommend this AI Coach to a first-time sumo robot builder?**
- [ ] Yes, strongly
- [ ] Yes, with some improvements
- [ ] No — needs significant changes
- [ ] Unsure

Comments: ___________________________________________

---

## Tester Information (Optional)

**Experience level:**
- [ ] Complete beginner (first robot project)
- [ ] Some experience (1–3 previous projects)
- [ ] Intermediate (have competed before)
- [ ] Advanced (multiple competition robot builds)

**Which kit do you have?**
- [ ] 1KG Autonomous Sumo Robot Starter Kit (full kit)
- [ ] URC10 board only
- [ ] RC Mode setup (URC10 + RC transmitter/receiver)
- [ ] Other: ___________________________________________

**Date of testing:** ___________________________________________

**Tester initials or username (optional):** ___________________________________________

---

*Thank you for your feedback. This form is used to improve the Cytron AI Coding Coach for the URC10 Sumo Robot Starter Kit.*
