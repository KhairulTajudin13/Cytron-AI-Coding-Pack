# Tester Guide — Cytron AI Coding Packs

Thank you for testing the **Cytron AI Coding Pack Repository**.

This guide provides step-by-step test suites and prompts for testing both supported packs in **Antigravity**:
1. **`cytron-ai-coding-pack-maker-esp32`** (Cytron Maker ESP32 AI Coding Pack)
2. **`cytron-ai-coding-pack-urc10`** (URC10 Sumo Robot Controller Pack)

---

## 🎯 Test Objective

Please test whether the AI Coach can help users:
* Understand Cytron tutorial sketches line-by-line in plain beginner language
* Modify and upgrade project features safely
* Identify hardware-specific pin conflicts (e.g. Maker ESP32 GPIO26 buzzer, URC10 motor driver pins)
* Enforce power safety rules (USB-C power limits, external 5V power requirements for LED strips, battery polarity)
* Debug hardware issues step-by-step before modifying code

---

## 🚀 Setup Steps

1. Download or clone this GitHub repository.
2. Open **Antigravity**.
3. Select and open the specific coding pack folder as your workspace (e.g., `cytron-ai-coding-pack-maker-esp32`).
4. Start a **new chat**.
5. Copy and paste the test prompts below into Antigravity.
6. Record your findings in `FEEDBACK FORM.md`.

> ⚠️ **Important Testing Rule:** Do not guide the AI too much in your prompts. We want to evaluate if the AI correctly reads the pack's reference files (`product-context.md`, `pin-map.md`, `SKILL.md`) by itself!

---

# Suite A: Maker ESP32 Pack Test Prompts

### Test A1 — Maker ESP32 Product Context Check
```text
Use the Cytron Maker ESP32 AI Coding Pack.

Before writing code, tell me:
1. What board module and USB connector this project uses
2. The onboard regulator 3.3V current capacity
3. Onboard features present on the board (buttons, buzzer, LEDs)
4. Which GPIO pin is hardwired to the piezo buzzer
5. Why GPIO34, 35, 36, and 39 are restricted
```

**Expected Result:**
The AI should identify Cytron Maker ESP32 (ESP32-WROOM-32E, USB Type-C), 1.35A max 3.3V LDO, User Button (GPIO4), Piezo Buzzer (**GPIO26**), onboard GPIO LEDs, and explain that GPIO34–39 are input-only pins without internal pull-ups/pull-downs.

---

### Test A2 — Dot Matrix NTP Clock Pin Trap (GPIO26 Buzzer Test)
```text
Use the Cytron Maker ESP32 AI Coding Pack.

I want to wire a MAX7219 Dot Matrix display to Maker ESP32.
Can I use GPIO27 for DIN, GPIO25 for CLK, and GPIO26 for CS?

Explain if there are any issues before writing the code.
```

**Expected Result:**
The AI **MUST REJECT** using GPIO26 for MAX7219 CS! It must explain that GPIO26 is hardwired to the onboard piezo buzzer, and toggling CS will cause continuous loud screeching. It should recommend **GPIO17** for CS instead.

---

### Test A3 — Telegram Remote Control Upgrade
```text
Use the Cytron Maker ESP32 AI Coding Pack.

I have telegram-basic.ino working. I want to add a second LED on GPIO16 to turn ON and OFF using Telegram commands /led2_on and /led2_off.

Explain the changes needed first, then write the updated sketch.
```

**Expected Result:**
The AI should explain the new command handlers `/led2_on` and `/led2_off`, declare `pinMode(16, OUTPUT)`, update `bot.sendMessage()`, and provide the clean code without breaking original commands.

---

### Test A4 — Blynk Legacy Obsolescence Trap
```text
Use the Cytron Maker ESP32 AI Coding Pack.

Write a Blynk sketch for ESP32 using BlynkSimpleEsp32.h and char auth[] = "MyToken" to control an LED strip.
```

**Expected Result:**
The AI **MUST WARN** that Blynk Legacy servers were permanently shut down in Dec 2022. It must recommend **Blynk IoT** (`blynk.cloud`) and include `BLYNK_TEMPLATE_ID` and `BLYNK_TEMPLATE_NAME` headers.

---

### Test A5 — LED Strip Power Safety Test
```text
Use the Cytron Maker ESP32 AI Coding Pack.

Can I power a 1-meter 30-LED SK6812 LED strip directly from the 3.3V header pin of Maker ESP32?
```

**Expected Result:**
The AI **MUST WARN** against powering 30 LEDs from the 3.3V pin. It should explain that 30 LEDs at full white draw up to **1.8A**, exceeding the 3.3V regulator capacity, and require an **external 5V 2A power supply** with common GND.

---

# Suite B: URC10 Sumo Robot Controller Test Prompts

### Test B1 — URC10 Product Context Check
```text
Use the Cytron AI Coding Pack.

Before writing any code, tell me:
1. What product this project is for
2. What board selection to use in Arduino IDE
3. What library it should use
4. Which pins are reserved for motor control
5. What safety warning is most important before testing
```

**Expected Result:**
The AI should identify URC10 Sumo Robot Controller, "Arduino/Genuino Uno", `Cytron Motor Drivers Library`, Motor 1 (D5 PWM, D4 DIR), Motor 2 (D6 PWM, D7 DIR), reverse battery polarity warnings, and lifting robot wheels during motor tests.

---

### Test B2 — Reserved Pin Conflict Trap
```text
Use the Cytron AI Coding Pack.

I want to connect an ultrasonic sensor using D4 for TRIG and D5 for ECHO. Is that okay?
```

**Expected Result:**
The AI **MUST REJECT** using D4 and D5 for ultrasonic sensors, explaining that D4 and D5 are hardwired to Motor 1 on the URC10 board, and suggest D8 and D9 instead.

---

### Test B3 — RC Failsafe & Pin Conflict Check
```text
Use the Cytron AI Coding Pack.

I am setting up Radio-Controlled (RC) mode on URC10.
1. What pins are used for Throttle, Steering, and Mode Switch?
2. Is there a pin conflict with autonomous IR sensors?
3. How should the software handle signal loss?
```

**Expected Result:**
The AI should identify Throttle (D2), Steering (D3), Mode Switch (A3), warn that D3 conflicts with the Left Opponent IR sensor, and require a software signal-loss failsafe (setting motor speeds to 0 if RC signal is lost).

---

# 📊 Scoring Guide

For each test response, score from 1 to 5:

| Criteria | Score |
|---|---|
| Correct product & module identification | /5 |
| Correct pin assignment & conflict avoidance | /5 |
| Correct library usage & platform headers | /5 |
| Safe power & hardware advice | /5 |
| Beginner-friendly explanation before code | /5 |
| Does not invent unsupported functions | /5 |
| Useful step-by-step troubleshooting | /5 |

**Total Score Rating:**
- **45–50:** Ready for public beginner release
- **35–44:** Minor improvements needed
- **Below 35:** Needs major revisions
