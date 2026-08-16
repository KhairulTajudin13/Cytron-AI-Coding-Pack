# Project Upgrade Ideas — Cytron Maker ESP32

This roadmap outlines progressive project upgrades for your Cytron Maker ESP32 Telegram Bot.

---

## 🎯 Phase 1: Core Telegram Bot Upgrades

The following upgrades expand your baseline tutorial code while enforcing non-blocking timing (`millis()`) and electrical safety rules:

### 1. `/blink` — Non-Blocking Visual Notification
- **Goal:** Blink the onboard GPIO LED 5 times (500ms ON / 500ms OFF) and return to the previous state.
- **Implementation Rule:** Must use `millis()` state machine timing; **do NOT use blocking `delay()` calls** that freeze Telegram polling!
- **Telegram Reply:** `"LED will blink 5 times."` followed by completion message `"LED blinking completed."`.

### 2. `/help` — Interactive Command Menu
- **Goal:** Provide a formatted help menu listing all valid commands when `/help` is sent.
- **Telegram Reply:**
  ```text
  🤖 Available Commands:
  /led_on
  /led_off
  /blink
  /state
  /help
  ```

---

## 🚀 Phase 2: Advanced Peripheral & IoT Expansion

Once core commands are working, try expanding your project with onboard hardware and Maker Port (JST-SH 4-pin I2C connector) accessories:

1. **Local Button Control (GPIO4):**
   - Combine local button interaction with remote cloud control.
   - Pressing the onboard User Button on **GPIO4** toggles the output LED state locally and notifies Telegram.
2. **Audio Command Feedback (GPIO26 Buzzer):**
   - Provide immediate audible feedback when commands are processed (respecting the physical hardware **Mute Switch**).
3. **Maker Port Sensors (I2C):**
   - Connect an environmental sensor (e.g., BME280/SHT30) via Maker Port (SDA=GPIO21, SCL=GPIO22) to report live sensor data via Telegram commands.

---

*Made with ❤️ by Cytron Technologies | [www.cytron.io](https://www.cytron.io)*
