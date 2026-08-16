# Start Here — Using This Pack with an AI Coding Assistant

Welcome! This guide explains **how to use this Cytron AI Coding Pack with Antigravity** (or any AI assistant) to modify, debug, and expand your Maker ESP32 Telegram project.

---

## 🛑 Step 1: Complete the Official Tutorial First

Before making any AI-guided modifications, verify your baseline setup:

- [x] You have a **Cytron Maker ESP32** connected via USB-C.
- [x] You have installed the **ESP32 Board Support Package** in Arduino IDE.
- [x] You have installed required libraries: `UniversalTelegramBot` and `ArduinoJson`.
- [x] You created a Telegram bot via `@BotFather` and retrieved your **Bot Token** and **Chat ID**.
- [x] You successfully uploaded the tutorial sketch: **[Control ESP32 Outputs with Telegram](https://my.cytron.io/tutorial/control-esp32-outputs-with-telegram)**.
- [x] Sending `/led_on` or `/led_off` in Telegram successfully lights up an onboard GPIO LED (e.g. GPIO2).

> ⚠️ **Important:** Keep a backup copy of your original working sketch before attempting AI-guided modifications!

---

## 💻 Step 2: Open This Folder with Antigravity

1. Open **Antigravity**.
2. Open the directory: `cytron-ai-coding-pack-maker-esp32/`.
3. Open or copy your working baseline Arduino code into the workspace.  
   *(If you need a clean reference sketch, see [`sample-code/telegram-basic.ino`](file:///e:/Cytron-AI-Coding-Pack/cytron-ai-coding-pack-maker-esp32/sample-code/telegram-basic.ino)).*

When you interact with the AI assistant, it will automatically load:
- Product context & hardware specs (`product-context.md`, `board-features.md`)
- Pin mapping & warnings (`pin-map.md`)
- Electrical and safety rules (`electrical-and-safety-rules.md`)
- AI Coach instructions (`.agents/skills/cytron-maker-esp32-ai-coach/SKILL.md`)

---

## 🤖 Step 3: Use Structured AI Prompts

Use the ready-made prompt files inside [`prompts/`](file:///e:/Cytron-AI-Coding-Pack/cytron-ai-coding-pack-maker-esp32/prompts/) or ask questions in your own words:

### 1. 🔍 Understand existing logic
> Use [`prompts/01-explain-code.md`](file:///e:/Cytron-AI-Coding-Pack/cytron-ai-coding-pack-maker-esp32/prompts/01-explain-code.md) to ask:  
> *"Explain how my code connects to Wi-Fi and handles Telegram messages."*

### 2. ⚡ Add new features
> Use [`prompts/02-upgrade-telegram-project.md`](file:///e:/Cytron-AI-Coding-Pack/cytron-ai-coding-pack-maker-esp32/prompts/02-upgrade-telegram-project.md) to ask:  
> *"Add a `/blink` command to blink the output 5 times using non-blocking `millis()` timing."*

### 3. 🐛 Debug connection or code errors
> Use [`prompts/03-debug-project.md`](file:///e:/Cytron-AI-Coding-Pack/cytron-ai-coding-pack-maker-esp32/prompts/03-debug-project.md) to ask:  
> *"My ESP32 connects to Wi-Fi but does not respond to Telegram commands. Help me debug step by step."*

---

## 🛡️ Step 4: AI Coach Operational Rules

When working with AI, the assistant adheres to these safety rules:

1. **Read context files first** before generating code.
2. **Confirm baseline file location** before making changes.
3. **Explain existing logic** before suggesting edits.
4. **Preserve working Telegram functions**.
5. **Make ONE manageable upgrade at a time**.
6. **Clearly show file changes (diffs)**.
7. **Explain new libraries** before adding dependencies.
8. **Never invent fake pins or hardware specs**.
9. **Warn before changing secrets, Wi-Fi, or pin assignments**.
10. **NEVER expose private credentials** (Wi-Fi SSID, Password, Telegram Token, Chat ID).
11. **Always use placeholders** (`YOUR_WIFI_SSID`, `YOUR_TELEGRAM_BOT_TOKEN`).
12. **Avoid blocking code:** `delay()` blocks the normal execution of the Arduino sketch, preventing `loop()` from processing Telegram commands during that period.
13. **Use `millis()` for timing** in upgraded features.
14. **Keep explanations beginner-friendly**.
15. **Provide physical hardware testing steps & expected results**.
16. **Instruct user to return to their original working code backup** if an upgrade fails.

---

## 🗺️ Quick File Reference

| Purpose | File to Read |
|---|---|
| Safe Voltage & Secret Credentials Rules | [`electrical-and-safety-rules.md`](file:///e:/Cytron-AI-Coding-Pack/cytron-ai-coding-pack-maker-esp32/electrical-and-safety-rules.md) |
| Onboard LEDs, Button & Buzzer details | [`board-features.md`](file:///e:/Cytron-AI-Coding-Pack/cytron-ai-coding-pack-maker-esp32/board-features.md) |
| Pinout & Bootstrapping cautions | [`pin-map.md`](file:///e:/Cytron-AI-Coding-Pack/cytron-ai-coding-pack-maker-esp32/pin-map.md) |
| Product Specs Overview | [`product-context.md`](file:///e:/Cytron-AI-Coding-Pack/cytron-ai-coding-pack-maker-esp32/product-context.md) |
| Upgrade ideas & roadmap | [`project-upgrade-ideas.md`](file:///e:/Cytron-AI-Coding-Pack/cytron-ai-coding-pack-maker-esp32/project-upgrade-ideas.md) |
| Troubleshooting connectivity/code | [`troubleshooting.md`](file:///e:/Cytron-AI-Coding-Pack/cytron-ai-coding-pack-maker-esp32/troubleshooting.md) |
| Baseline reference sketch | [`sample-code/telegram-basic.ino`](file:///e:/Cytron-AI-Coding-Pack/cytron-ai-coding-pack-maker-esp32/sample-code/telegram-basic.ino) |
