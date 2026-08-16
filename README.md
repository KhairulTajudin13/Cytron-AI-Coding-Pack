# Cytron AI Coding Pack Repository

This repository contains the official **Cytron AI Coding Packs**, designed to help users continue learning after completing a Cytron hardware tutorial.

Instead of following static getting-started guides, users open a coding pack in an AI coding assistant (such as **Antigravity**) to explain code, upgrade features, debug hardware issues, and safely expand projects using dedicated Cytron AI Coach guidance.

---

## 📦 Available Coding Packs

This repository currently includes two active Cytron AI Coding Packs:

### 1. `cytron-ai-coding-pack-maker-esp32/`
- **Target Hardware:** Cytron Maker ESP32 (ESP32-WROOM-32E-N8, USB Type-C, 1.35A 3.3V LDO regulator)
- **Primary Learning Path:** Telegram Bot Remote Control, Dot Matrix NTP Clock, and Vibe-Coding IoT Projects
- **Key Features:** Built-in GPIO LEDs, Onboard Piezo Buzzer (GPIO26), User Button (GPIO4), USB-C power rail
- **Included Sample Code:**
  - `sample-code/telegram-basic.ino` — Baseline Telegram bot control sketch
  - `sample-code/dot-matrix-clock-maker-esp32.ino` — Dot Matrix NTP Clock (CS mapped to GPIO17 to avoid GPIO26 buzzer, fixed buffer overflow)

### 2. `cytron-ai-coding-pack-urc10/`
- **Target Hardware:** URC10 Sumo Robot Controller (ATmega328P, 10A Continuous Dual Motor Driver)
- **Primary Learning Path:** Autonomous Sumo Robot & Radio-Controlled (RC) Sumo Robot
- **Key Features:** Pre-routed motor pins (D4, D5, D6, D7), high-current motor terminals, dedicated sensor headers

---

## 🎯 What These Packs Help With

Users can use these AI Coding Packs to:
* **Understand** original tutorial sketches line-by-line in plain beginner language
* **Modify** project behavior (e.g. add LED indicators, adjust matrix scroll speeds, change robot tactics)
* **Debug** hardware issues step-by-step before altering code
* **Avoid critical hardware mistakes** (e.g. GPIO26 buzzer screeching on Maker ESP32, motor pin conflicts on URC10, reverse polarity warnings)

> 💡 **Note:** These AI Coding Packs are designed to **extend** official Cytron tutorials, not replace them. Users should first complete the official tutorial setup before opening the pack in Antigravity for AI-assisted learning.

---

## 🚀 How to Use

1. Click **Code → Download ZIP** (or clone this repository).
2. Extract the ZIP file on your computer.
3. Open the specific coding pack folder (e.g., `cytron-ai-coding-pack-maker-esp32`) in **Antigravity**.
4. Start a new chat with Antigravity.
5. Use the prompts provided in `prompts/` or `TESTER GUIDE.md`.
6. Record testing results using `FEEDBACK FORM.md`.

---

## 📁 Repository Structure

```text
Cytron-AI-Coding-Pack/
├── README.md                          # Repository Overview
├── TESTER GUIDE.md                    # Multi-Pack Testing Guide & Prompts
├── FEEDBACK FORM.md                   # Tester Feedback & Evaluation Sheet
├── source-audit.md                    # Technical Audits (URC10 & Maker ESP32)
│
├── cytron-ai-coding-pack-maker-esp32/ # Maker ESP32 AI Coding Pack
│   ├── README.md                      # Pack getting started guide
│   ├── start-here.md                  # Quick workflow overview
│   ├── product-context.md             # Maker ESP32 specs & architecture
│   ├── board-features.md              # Onboard peripherals (LEDs, buzzer, button)
│   ├── pin-map.md                     # Safe pin allocation rules
│   ├── electrical-and-safety-rules.md # 5V power, current limits, logic levels
│   ├── troubleshooting.md             # Common upload, Wi-Fi & display fixes
│   ├── project-upgrade-ideas.md       # Ideas for post-tutorial projects
│   ├── sample-code/
│   │   ├── README.md
│   │   ├── telegram-basic.ino         # Original Telegram tutorial baseline
│   │   └── dot-matrix-clock-maker-esp32.ino # Updated NTP Dot Matrix Clock
│   ├── prompts/
│   │   ├── 01-explain-code.md
│   │   ├── 02-upgrade-telegram-project.md
│   │   └── 03-debug-project.md
│   └── .agents/
│       └── skills/
│           └── cytron-maker-esp32-ai-coach/
│               └── SKILL.md           # Maker ESP32 AI Coach system skill
│
└── cytron-ai-coding-pack-urc10/       # URC10 Sumo Robot Controller Pack
    ├── README.md
    ├── start-here.md
    ├── product-context.md
    ├── pin-map.md
    ├── safety-rules.md
    ├── sample-code/
    └── .agents/
        └── skills/
            └── cytron-ai-coding-coach/
```

---

## 🧪 Testing Goal

Our core evaluation objective across all packs is:

> **Can the AI Coach guide a beginner to safely understand, upgrade, debug, and expand Cytron tutorial projects without introducing hardware conflicts or dangerous advice?**
