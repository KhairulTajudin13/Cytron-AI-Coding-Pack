# Electrical and Safety Rules — Cytron Maker ESP32

These electrical limits, hardware specifications, and secret credential security rules are verified directly against the **Maker ESP32 Datasheet** (`source-docs/Maker ESP32 Datasheet.pdf`).

---

## ⚡ 1. Power Supply Ratings

| Parameter | Min | Max | Unit | Notes |
|---|---|---|---|---|
| **Power Input Voltage (USB-C / VIN)** | 4.6 | 5.5 | VDC | Standard 5V USB Power |
| **3V3 Maximum Current** | — | 1.35 | A | Total capacity including onboard peripherals & Maker Port |
| **Operating Temperature** | -40 | +85 | °C | Industrial temperature range |

---

## 🔌 2. GPIO Electrical Limits

| Parameter | Min | Max | Unit | Notes |
|---|---|---|---|---|
| **Digital Input Low Level ($V_{IL}$)** | -0.3 | 0.8 | V | State LOW threshold |
| **Digital Input High Level ($V_{IH}$)** | 2.5 | 3.6 | V | State HIGH threshold |
| **Analog Input Voltage** | 0.0 | 3.3 | V | ADC input range |
| **Digital Output Low ($V_{OL}$)** | 0.0 | 0.4 | V | Max low output voltage |
| **Digital Output High ($V_{OH}$)** | 2.6 | 3.3 | V | Min high output voltage |
| **Low Level Sink Current ($I_{OL}$)** | — | 28 | mA | Absolute max current sink |
| **High Level Source Current ($I_{OH}$)** | — | 40 | mA | Absolute max current source |
| **Internal Pull-Up/Pull-Down ($R_{PU}/R_{PD}$)** | 45 | 45 | kΩ | Internal pull resistors |

> ⚠️ **CRITICAL ELECTRICAL WARNINGS:**
> 1. **3.3V LOGIC ONLY:** Do NOT apply 5V directly to any ESP32 GPIO pin!
> 2. **NO DIRECT MOTOR/RELAY DRIVING:** Do not power high-current inductive loads (motors, relays, solenoids) directly from GPIO pins. Use external transistor/MOSFET driver circuits or motor driver boards.
> 3. **COMMON GROUND:** All external devices must share a common GND connection with the Maker ESP32.

---

## 🔒 3. Secret Credential Protection Rules

When working with Wi-Fi and Telegram Bot projects:

> ⚠️ **NEVER print, expose, or commit private keys, Wi-Fi credentials, or bot tokens!**

### Placeholder Standard
Use standardized placeholders in code, logs, and AI prompts:

```cpp
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
#define BOTtoken "YOUR_TELEGRAM_BOT_TOKEN"
#define CHAT_ID "YOUR_TELEGRAM_CHAT_ID"
```

---

*Verified against `source-docs/Maker ESP32 Datasheet.pdf`*
