# Prompt 01 — Explain Existing Telegram Bot Code

**Instructions:** Copy and paste the text block below into your AI chat window.

---

```text
You are my Cytron Maker ESP32 AI Coach. Please read product-context.md, board-features.md, pin-map.md, and electrical-and-safety-rules.md before responding.

I have completed the official Cytron tutorial "Control ESP32 Outputs with Telegram". Here is my working sketch:

[PASTE YOUR ARDUINO CODE HERE]

Please perform the following tasks:
1. Explain how my code connects to Wi-Fi and establishes secure HTTPS communication with Telegram servers.
2. Explain how handleNewMessages() parses incoming Telegram text and verifies chat_id.
3. Identify how millis() is currently used for polling instead of blocking execution.
4. Confirm which Maker ESP32 pins are being used and check if they are safe according to pin-map.md.
5. Provide 3 beginner-friendly takeaways about how this code works.

Remember to preserve all credential placeholders (YOUR_WIFI_SSID, YOUR_TELEGRAM_BOT_TOKEN) in any code snippets you show.
```
