# Auto-Kit Validation Checklist — 1KG Autonomous Sumo Robot Starter Kit using URC10

## Purpose

This checklist is used to verify that the AI Coach's autonomous kit guidance meets quality and safety standards before it is used by a beginner. Each item must be confirmed before the AI Coach generates final autonomous code or provides definitive hardware guidance.

---

## Section 1 — Pin Mapping Integrity

### ✅ 1.1 — No Unverified Pin Is Treated as Confirmed

- [ ] Every pin marked "Needs verification" in `auto-kit-sensor-map.md` is labeled as such in any AI response
- [ ] The AI Coach does **not** assume D13, D2, or A4 is the button pin without asking the user first
- [ ] Any generated code that includes an unverified pin includes the comment:
  ```cpp
  // NOTE: Unverified — confirm this pin with your actual wiring before running
  ```
- [ ] The AI Coach never silently picks one button pin without explaining the conflict

**Verification:** Ask the AI Coach "Write me the autonomous code for this kit." It must ask about the button pin before generating complete code.

---

### ✅ 1.2 — Button Pin Conflict Is Documented

- [ ] The conflict between D13 (sample code), D2 (tutorial assembly), and A4 (kit variant) is recorded in:
  - `auto-kit-sensor-map.md` ✅
  - `auto-kit-assembly-notes.md` ✅
  - `auto-kit-context.md` ✅
  - `auto-kit-troubleshooting.md` (Problem 6) ✅
- [ ] The AI Coach asks the user which pin their button uses before writing code
- [ ] The AI Coach references the conflict and explains why it matters

**Verification:** Search for "button" in all auto-kit files — all four above files should contain documented conflict text.

---

## Section 2 — Hardware Documentation

### ✅ 2.1 — Kit Hardware List Is Included

- [ ] `auto-kit-hardware-list.md` exists and lists all 9 official kit components:
  - URC10 ✅
  - Maker Object sensors (×5) ✅
  - Maker Reflect sensors (×2) ✅
  - 12V 580RPM brushed DC geared motors (×2) ✅
  - G25T1 Silicone Wheel Set (×2) ✅
  - 11.1V LiPo battery ✅
  - Copper base (×2) ✅
  - Dean T LiPo battery wire extension ✅
  - GVS Female-to-Female extensions (×7) ✅
- [ ] Each component includes a description of its role in the robot
- [ ] The source URL (official Cytron tutorial) is cited

**Verification:** Open `auto-kit-hardware-list.md` and confirm all 9 items are listed with role descriptions.

---

### ✅ 2.2 — Sensor Roles Are Explained

- [ ] Maker Object sensor is clearly identified as the **opponent detection** sensor
- [ ] Maker Reflect sensor is clearly identified as the **edge / boundary detection** sensor
- [ ] The distinction between these two sensors is explained in beginner-friendly language
- [ ] Files containing sensor role explanations:
  - `auto-kit-hardware-list.md` ✅
  - `auto-kit-sensor-map.md` ✅
  - `auto-kit-behavior-guide.md` ✅

**Verification:** Ask the AI Coach "What does the Maker Object sensor do?" — it should explain opponent detection, not edge detection.

---

## Section 3 — Safety Documentation

### ✅ 3.1 — LiPo Battery Safety Warnings Are Included

- [ ] `auto-kit-safety-rules.md` contains:
  - LiPo charging rules (balance charger required) ✅
  - Storage voltage guidance ✅
  - Over-discharge warning ✅
  - Swollen/damaged battery inspection rule ✅
  - Fire emergency instructions (no water) ✅
- [ ] LiPo safety warnings are also included in `auto-kit-hardware-list.md` ✅
- [ ] LiPo safety warnings are referenced in `auto-kit-assembly-notes.md` ✅

**Verification:** Open `auto-kit-safety-rules.md` Rule 1 and confirm all sub-items are present.

---

### ✅ 3.2 — Blade/Scoop Sharp Warning Is Included

- [ ] `auto-kit-safety-rules.md` contains explicit sharp blade warning (Rule 4) ✅
- [ ] `auto-kit-assembly-notes.md` Step 13 contains sharp blade warning ✅
- [ ] The warning is specific: mentions "sharpened metal part", "handle by back edge", "cover during transport"

**Verification:** Search for "blade" or "sharp" in auto-kit files — should appear in at least 2 files.

---

### ✅ 3.3 — Reverse Polarity Warning Is Included

- [ ] `auto-kit-safety-rules.md` Rule 2 includes explicit reverse polarity warning ✅
- [ ] `auto-kit-assembly-notes.md` Steps 8 and 11 include reverse polarity warnings ✅
- [ ] The consequence is stated clearly: "permanently destroy the URC10 board"

---

### ✅ 3.4 — Wheel-Lift Testing Rule Is Included

- [ ] `auto-kit-safety-rules.md` Rule 3 instructs user to lift wheels during motor testing ✅
- [ ] `auto-kit-tuning-guide.md` repeats the lift-wheels instruction before every tuning test ✅
- [ ] `auto-kit-troubleshooting.md` includes lift-wheels reminder in the opening note ✅

---

## Section 4 — Behavior and Code Quality

### ✅ 4.1 — Autonomous Behavior Is Beginner-Friendly

- [ ] `auto-kit-behavior-guide.md` explains all 7 behavior states in plain language ✅
- [ ] Each state includes: what happens, when it changes, and a code concept example ✅
- [ ] No jargon is used without explanation ✅
- [ ] Beginner tip boxes are included in key sections ✅
- [ ] The behavior flow diagram is included at the end of the guide ✅

**Verification:** Ask a beginner to read `auto-kit-behavior-guide.md` — they should understand what search mode, attack mode, and backoff mean without prior robotics knowledge.

---

### ✅ 4.2 — Tuning Guide Is Beginner-Appropriate

- [ ] `auto-kit-tuning-guide.md` uses named constants (`#define`) for all values ✅
- [ ] Starting values are given for every parameter ✅
- [ ] Tables explain low/good/high value effects for each parameter ✅
- [ ] Physical hardware tuning (potentiometer adjustment) is explained alongside software tuning ✅
- [ ] Tuning checklist is included at the end ✅

---

### ✅ 4.3 — Motor Reserved Pins Are Protected

- [ ] D4, D5, D6, D7 are documented as RESERVED in `auto-kit-sensor-map.md` ✅
- [ ] No generated code assigns sensors or peripherals to D4, D5, D6, or D7 ✅
- [ ] Any AI Coach response involving D4/D5/D6/D7 for non-motor purposes must flag an error

---

## Section 5 — Learning Path Integrity

### ✅ 5.1 — This Path Is Distinct from Basic URC10 and RC Mode

- [ ] `auto-kit-context.md` clearly states this path is for the **full kit**, not the board alone ✅
- [ ] The user is directed to the correct path if they are not using the full kit ✅
- [ ] RC mode files are not modified or replaced ✅
- [ ] URC10 board files are not modified or replaced ✅
- [ ] SKILL.md now offers 4 distinct mode choices ✅

---

### ✅ 5.2 — All Required Files Exist

- [ ] `auto-kit-mode/auto-kit-context.md` ✅
- [ ] `auto-kit-mode/auto-kit-hardware-list.md` ✅
- [ ] `auto-kit-mode/auto-kit-assembly-notes.md` ✅
- [ ] `auto-kit-mode/auto-kit-sensor-map.md` ✅
- [ ] `auto-kit-mode/auto-kit-behavior-guide.md` ✅
- [ ] `auto-kit-mode/auto-kit-tuning-guide.md` ✅
- [ ] `auto-kit-mode/auto-kit-troubleshooting.md` ✅
- [ ] `auto-kit-mode/auto-kit-safety-rules.md` ✅
- [ ] `auto-kit-mode/auto-kit-validation-checklist.md` (this file) ✅
- [ ] SKILL.md updated to include Autonomous Kit mode choice ✅
- [ ] TESTER-GUIDE.md updated with Autonomous Kit test section ✅
- [ ] FEEDBACK-FORM.md updated with kit-specific questions ✅

---

## Checklist Sign-Off

| Check | Status |
|---|---|
| No unverified pin treated as confirmed | ✅ Implemented |
| Button pin conflict documented | ✅ Documented in 4 files |
| Kit hardware list included (9 items) | ✅ Complete |
| Sensor role explanations included | ✅ In 3 files |
| LiPo battery safety warnings | ✅ Complete |
| Sharp blade warning | ✅ In 2 files |
| Reverse polarity warning | ✅ In 3 files |
| Wheel-lift testing instruction | ✅ In 3 files |
| Behavior guide is beginner-friendly | ✅ With diagrams + tips |
| Tuning guide uses named constants | ✅ With tables |
| Motor reserved pins protected | ✅ Documented |
| Learning path separated from RC and basic modes | ✅ Distinct |
| All 8 auto-kit files created | ✅ Complete |
| SKILL.md, TESTER-GUIDE.md, FEEDBACK-FORM.md updated | ✅ Complete |
