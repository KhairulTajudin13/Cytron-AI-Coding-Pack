# Troubleshooting Guide — Cytron Maker ESP32

This guide helps you diagnose and fix common hardware, connection, compilation, and Telegram API issues on the **Cytron Maker ESP32**.

---

## 🔍 Diagnostic Decision Tree

```
                      +-----------------------------------+
                      |   PROBLEM DETECTED ON ESP32       |
                      +-----------------------------------+
                                        |
        +-------------------------------+-------------------------------+
        |                               |                               |
        v                               v                               v
[ Wi-Fi / Connection ]       [ Telegram Bot API ]            [ Hardware / LEDs ]
- Failed IP Connection       - No Command Response          - LED Not Lighting
- Serial prints "....."      - "Unauthorized user"          - Buzzer Silent (Check Mute!)
- 5GHz vs 2.4GHz router      - SSL Handshake fail           - Button Unresponsive
```

---

## 1. Wi-Fi Connectivity Problems

### Symptom: Serial Monitor prints dots continuously (`.......`) and never connects.
- **Cause 1: 5GHz Wi-Fi Network.** The ESP32 hardware radio **only supports 2.4GHz Wi-Fi networks**. It cannot connect to 5GHz-only Wi-Fi.
  - *Fix:* Ensure your Wi-Fi router broadcasts a separate 2.4GHz SSID or create a 2.4GHz mobile hotspot.
- **Cause 2: Incorrect SSID or Password.**
  - *Fix:* Double-check capitalization and special characters in your `ssid` and `password` variables.
- **Cause 3: Insufficient USB Power.**
  - *Fix:* Connect the USB-C cable directly to a computer USB 3.0 port or a 5V/1A power adapter (avoid unpowered USB hubs).

---

## 2. Telegram Bot & API Failures

### Symptom: ESP32 prints "Wi-Fi Connected", but sending commands in Telegram yields no reply.
- **Cause 1: Incorrect Bot Token.**
  - *Fix:* Verify your token string obtained from `@BotFather` (e.g. `123456789:ABCdefGhIJKlmNoPQRstuVWXyz`). Ensure there are no accidental spaces.
- **Cause 2: Incorrect Chat ID / Unauthorized Filter.**
  - *Fix:* Re-check your chat ID using Telegram bot `@myidbot`. If your `CHAT_ID` constant does not match your numeric Telegram user ID, the bot will filter your messages as unauthorized!
- **Cause 3: Missing SSL Certificate Root Setup.**
  - *Fix:* Ensure `client.setCACert(TELEGRAM_CERTIFICATE_ROOT);` is included in `setup()` before connecting to Wi-Fi.
- **Cause 4: Code Blocked by `delay()` Calls.**
  - *Fix:* `delay()` blocks the normal execution of the Arduino sketch, preventing `loop()` from processing Telegram commands during that period. Use non-blocking `millis()` state machine timers instead.

---

## 3. Hardware & Onboard Peripherals Troubleshooting

### Symptom: Buzzer produces no sound when `tone(26, 1000)` is called.
- **Check the Physical Mute Switch!**
  - The Maker ESP32 features a hardware Mute Switch next to the piezo buzzer.
  - *Fix:* Slide the physical mute switch to the **ON** position to enable sound.

### Symptom: Onboard GPIO Indicator LED does not light up.
- **Check GPIO Pin Assignment:**
  - Verify that your code specifies an actual LED pin (e.g. `GPIO2`, `GPIO12`, `GPIO13`, `GPIO16`, `GPIO17`, `GPIO18`, `GPIO19`, `GPIO21`, `GPIO22`, `GPIO23`, `GPIO25`, `GPIO27`, `GPIO32`, `GPIO33`).
  - Ensure `pinMode(ledPin, OUTPUT);` was called in `setup()`.
  - Remember onboard GPIO LEDs are **Active HIGH** (`digitalWrite(ledPin, HIGH)` turns them ON).

---

## 4. Arduino IDE Compilation & Library Errors

### Error: `'UniversalTelegramBot' does not name a type` or missing `<ArduinoJson.h>`
- **Fix:** Install the following libraries via Arduino IDE Library Manager (**Tools -> Manage Libraries...**):
  1. `UniversalTelegramBot` by Brian Lough (v1.3.0 or higher)
  2. `ArduinoJson` by Benoit Blanchon (v6.x or v7.x compatible)

---

## 🚨 Rollback Advice

If an AI-generated code edit causes compilation errors, Wi-Fi disconnects, or unresponsive behavior:
1. Revert to your saved original working sketch backup.
2. Re-upload your working backup to confirm hardware health.
3. Use [`prompts/03-debug-project.md`](file:///e:/Cytron-AI-Coding-Pack/cytron-ai-coding-pack-maker-esp32/prompts/03-debug-project.md) to debug the error.

---

*Made with ❤️ by Cytron Technologies | [www.cytron.io](https://www.cytron.io)*
