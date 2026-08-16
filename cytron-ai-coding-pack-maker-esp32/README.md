# Cytron AI Coding Pack — Maker ESP32

Welcome to the **Cytron AI Coding Pack for Maker ESP32**!

This pack is designed to help you **continue learning and expanding your projects after completing official Cytron Maker ESP32 tutorials** — starting with the pilot tutorial: **[Control ESP32 Outputs with Telegram](https://my.cytron.io/tutorial/control-esp32-outputs-with-telegram)**.

Using **Antigravity** (or any AI coding assistant), this pack gives you hardware reference documentation, electrical safety guidelines, pin maps, structured AI prompts, and baseline sample code to transition smoothly from basic tutorials to interactive "vibe coding" project upgrades.

---

## 🎯 Beginner Vibe-Coding Workflow

Follow these 8 simple steps to work with your AI assistant:

1. **Complete the Official Tutorial:** Build and verify the baseline [Control ESP32 Outputs with Telegram](https://my.cytron.io/tutorial/control-esp32-outputs-with-telegram) project on your Maker ESP32.
2. **Open This Workspace:** Open the `cytron-ai-coding-pack-maker-esp32` folder in **Antigravity**.
3. **Add Your Sketch:** Open or copy your working Arduino sketch into the workspace.  
   *(💡 **Tip:** Always keep a backup copy of your original working sketch before applying AI-generated changes!)*
4. **Choose a Prompt:** Select a ready-to-use template from the [`prompts/`](file:///e:/Cytron-AI-Coding-Pack/cytron-ai-coding-pack-maker-esp32/prompts/) folder.
5. **Ask Antigravity:** Paste the prompt into Antigravity to explain, modify, or debug your code.
6. **Review Proposed Changes:** Check the code diffs, non-blocking `millis()` logic, and explanations.
7. **Upload & Test:** Upload the updated sketch to your Cytron Maker ESP32 and physically verify onboard LED behaviors.
8. **Revert if Necessary:** If an upgrade does not work as expected, return to your original working sketch backup and consult [`troubleshooting.md`](file:///e:/Cytron-AI-Coding-Pack/cytron-ai-coding-pack-maker-esp32/troubleshooting.md).

---

## 📁 Pack Navigation

| File / Directory | Purpose |
|---|---|
| [`start-here.md`](file:///e:/Cytron-AI-Coding-Pack/cytron-ai-coding-pack-maker-esp32/start-here.md) | Guide for using Antigravity AI assistant |
| [`product-context.md`](file:///e:/Cytron-AI-Coding-Pack/cytron-ai-coding-pack-maker-esp32/product-context.md) | Cytron Maker ESP32 overview & architecture |
| [`board-features.md`](file:///e:/Cytron-AI-Coding-Pack/cytron-ai-coding-pack-maker-esp32/board-features.md) | Specs for onboard LEDs, button, buzzer, mute switch & Maker Port |
| [`pin-map.md`](file:///e:/Cytron-AI-Coding-Pack/cytron-ai-coding-pack-maker-esp32/pin-map.md) | Master GPIO mapping, input-only pins & pin cautions |
| [`electrical-and-safety-rules.md`](file:///e:/Cytron-AI-Coding-Pack/cytron-ai-coding-pack-maker-esp32/electrical-and-safety-rules.md) | 3.3V logic limits, voltage rules & secret security |
| [`project-upgrade-ideas.md`](file:///e:/Cytron-AI-Coding-Pack/cytron-ai-coding-pack-maker-esp32/project-upgrade-ideas.md) | Step-by-step roadmap for future project features |
| [`troubleshooting.md`](file:///e:/Cytron-AI-Coding-Pack/cytron-ai-coding-pack-maker-esp32/troubleshooting.md) | Diagnosing Wi-Fi, Telegram Bot API & hardware issues |
| [`prompts/`](file:///e:/Cytron-AI-Coding-Pack/cytron-ai-coding-pack-maker-esp32/prompts/) | Ready-to-use AI prompts for explanation, upgrades & debugging |
| [`sample-code/`](file:///e:/Cytron-AI-Coding-Pack/cytron-ai-coding-pack-maker-esp32/sample-code/) | Original baseline tutorial sketch reference ([`telegram-basic.ino`](file:///e:/Cytron-AI-Coding-Pack/cytron-ai-coding-pack-maker-esp32/sample-code/telegram-basic.ino)) |
| [`.agents/skills/cytron-maker-esp32-ai-coach/`](file:///e:/Cytron-AI-Coding-Pack/cytron-ai-coding-pack-maker-esp32/.agents/skills/cytron-maker-esp32-ai-coach/SKILL.md) | AI Coach skill rules for Antigravity AI assistant |

---

## 🛠️ Board Hardware Highlights

- **Main Controller:** ESP32-WROOM-32E-N8 module (Dual-Core 32-bit @ 240 MHz, 8MB Flash)
- **Power & Programming:** USB-C (5V power input, CP2102/CH340 USB-UART bridge)
- **Onboard Peripherals:**
  - **14 GPIO LEDs:** Connected to GPIO 2, 12, 13, 16, 17, 18, 19, 21, 22, 23, 25, 27, 32, 33 (Active HIGH)
  - **User Button:** GPIO4 (Active LOW with pull-up)
  - **Piezo Buzzer:** GPIO26 with physical Mute Switch
  - **Maker Port:** 4-pin JST-SH connector (GPIO21=SDA, GPIO22=SCL, 3V3, GND)

---

*Made with ❤️ by Cytron Technologies | [www.cytron.io](https://www.cytron.io)*
