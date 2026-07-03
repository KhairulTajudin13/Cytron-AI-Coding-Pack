# Auto-Kit Context — 1KG Autonomous Sumo Robot Starter Kit using URC10

## ⚠️ Important: This Is a Complete Kit, Not Just the URC10 Board

This learning path is for the **complete 1KG Autonomous Sumo Robot Starter Kit** from Cytron Technologies, which uses the URC10 board as its controller. This is **not** a general URC10 board guide, and not the same as the RC Mode path.

If you are:
- **Testing the URC10 board alone** → use the Basic URC10 Board Testing path
- **Building a radio-controlled sumo robot** → use the RC Mode path
- **Building an autonomous sumo robot using the full kit** → you are in the right place ✅

---

## What Is This Kit?

The **1KG Autonomous Sumo Robot Starter Kit** is a beginner-friendly competition robot designed to fight in 1KG sumo robot competitions. It is completely autonomous — once started, it finds and pushes its opponent out of the ring without any human remote control input.

| Specification | Value |
|---|---|
| Weight class | Under 1 KG |
| Size limit | 15cm × 15cm footprint |
| Control method | Fully autonomous (no RC input) |
| Controller board | URC10 (Arduino-compatible, ATmega328P) |
| Motor support | Up to 10A continuous per channel |
| Target user | Beginner roboteer / competition enthusiast |

---

## Kit Purpose Summary

This kit is designed to:

1. **Meet competition weight and size rules** — the assembled robot fits within the standard 1KG sumo class rules (under 1KG, within 15cm × 15cm)
2. **Drive autonomously** — the URC10 reads sensor data and makes decisions without human input during a match
3. **Detect opponents** — Maker Object sensors scan for the enemy robot in the ring
4. **Detect the ring boundary** — Maker Reflect sensors detect the white edge line so the robot does not drive out
5. **Push opponents out** — high-torque brushed DC motors and the front blade/scoop give the robot pushing power
6. **Support Arduino-compatible coding** — the URC10 is programmable via Arduino IDE and can be customized by beginners

---

## How This Path Is Organized

| File | Contents |
|---|---|
| `auto-kit-context.md` | This file — overview and kit purpose |
| `auto-kit-hardware-list.md` | Complete hardware list from the official tutorial |
| `auto-kit-assembly-notes.md` | Step-by-step assembly guidance and safety warnings |
| `auto-kit-sensor-map.md` | Pin mapping for all kit sensors — verified and unverified |
| `auto-kit-behavior-guide.md` | How the autonomous logic works (start, search, attack, edge avoidance) |
| `auto-kit-tuning-guide.md` | Speed, timing, and sensor threshold tuning for competition |
| `auto-kit-troubleshooting.md` | Common problems and how to fix them |
| `auto-kit-safety-rules.md` | LiPo battery, blade, polarity, and testing safety rules |

---

## Source Reference

This path is based on the official Cytron tutorial:

> **1KG Autonomous Sumo Robot Starter Kit User Guide using URC10**
> https://my.cytron.io/tutorial/1-kg-autonomous-sumo-robot-starter-kit-user-guide-using-urc10
> Author: Adrian Afiq — Published: 15 Apr 2025

---

## ✅ Resolved: Start Button Pin Standard

For this AI Coding Pack, the Start Button pin for all Autonomous Kit Mode code is **A4**.
This matches the 1KG Autonomous Sumo Robot Starter Kit assembly and wiring guide.

All generated code uses:
```cpp
#define START_BUTTON_PIN  A4  // Matches the 1KG Autonomous Sumo Robot Starter Kit wiring guide
                              // Legacy note: older sample code used D13; some tutorials reference D2
                              // If your button is wired to D13 or D2, change A4 to match
```

**Legacy / Variant Notes (for reference only):**
| Source | Pin |
|---|---|
| Cytron sample code (`URC10SumoRobot.ino`) | D13 |
| Some tutorial assembly steps | D2 |

See `auto-kit-sensor-map.md` for the full pin table.

---

## Reminder: This Is a Learning Path, Not Just a Code Generator

The AI Coach for this path will:
- Explain what each part does before giving code
- Ask which button wiring you are using before writing autonomous code
- Warn you about safety hazards (blade, LiPo battery, reverse polarity)
- Help you test one thing at a time
- Explain what any code change does and why
