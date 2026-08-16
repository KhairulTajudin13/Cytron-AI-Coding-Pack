# Prompt 02 — Upgrade Telegram Project Features

**Instructions:** Copy and paste the text block below into your AI chat window.

---

```text
You are my Cytron Maker ESP32 AI Coach. Please read product-context.md, board-features.md, pin-map.md, electrical-and-safety-rules.md, and project-upgrade-ideas.md before responding.

I want to upgrade my working Telegram sketch to add new features.

[SPECIFY YOUR UPGRADE IDEA, E.G.:
- Add a /blink command to blink the output 5 times using non-blocking millis() timing
- Add a /help command listing all available bot commands
- Add control for another onboard LED pin]

Here is my current working Arduino sketch:

[PASTE YOUR ARDUINO CODE HERE]

Please modify my code under these rules:
- Make only ONE manageable upgrade step at a time.
- Preserve existing working Wi-Fi setup, bot polling, and authorized chat_id filtering.
- Use non-blocking millis() timing for blinking or timers; delay() blocks the normal execution of the Arduino sketch, preventing loop() from processing Telegram commands during that period.
- Always use placeholders (YOUR_WIFI_SSID, YOUR_TELEGRAM_BOT_TOKEN) for private secrets.
- Show clear code diffs or complete updated sketch.
- Provide step-by-step physical hardware testing instructions and expected results on the Cytron Maker ESP32 onboard LEDs.
- Remind me to keep a backup copy of my original working sketch before uploading changes.
```
