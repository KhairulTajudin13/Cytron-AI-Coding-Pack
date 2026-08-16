# Product Context — Cytron Maker ESP32

This document provides technical background, hardware architecture, and project scope for the **Cytron Maker ESP32**.

---

## 🚀 Overview

The **Cytron Maker ESP32** is a beginner-friendly microcontroller board designed by Cytron Technologies. Powered by the **ESP32-WROOM-32E-N8** module, it brings dual-core 32-bit computing power, built-in Wi-Fi, and Bluetooth connectivity into a NodeMCU-compatible form factor with rich onboard hardware diagnostic tools.

Unlike generic ESP32 development boards, the Maker ESP32 features **onboard status LEDs for every GPIO output**, a **programmable user button**, a **passive piezo buzzer with a hardware mute switch**, and plug-and-play **Maker Port (JST-SH 4-pin I2C)** connectivity.

---

## 🛠️ Key Hardware Specifications

| Parameter | Specification |
|---|---|
| **Board Name** | Cytron Maker ESP32 |
| **Main Module** | ESP32-WROOM-32E-N8 |
| **Processor Core** | Dual-core 32-bit Xtensa LX6 @ 240 MHz |
| **Flash Memory** | 8 MB |
| **SRAM** | 520 KB |
| **Wireless Connectivity** | 2.4 GHz Wi-Fi (802.11 b/g/n) & Bluetooth 4.2 / BLE |
| **Power Input** | USB-C (5V) or VIN pin (4.6V – 5.5V) |
| **Logic Operating Voltage** | 3.3V DC |
| **3.3V Regulator Capacity** | 1.35A Max LDO Regulator |
| **Form Factor** | Compatible with NodeMCU ESP32 |
| **Programming Interface** | USB-C via USB-to-UART bridge (CP2102/CH340) |

---

## ⚡ Onboard Peripherals & Features

### 1. GPIO Indicator LEDs (14 LEDs)
- Located directly next to their respective GPIO header pins.
- **Active HIGH:** Turns **ON** when the GPIO pin is driven `HIGH` (3.3V).
- **LED Pins:** GPIO 2, 12, 13, 16, 17, 18, 19, 21, 22, 23, 25, 27, 32, 33.
- **Benefit:** Instant visual feedback when testing code without connecting external LEDs or breadboards!

### 2. Onboard User Pushbutton
- Connected to **GPIO4**.
- Includes a physical pull-up resistor (Reads `LOW` when pressed, `HIGH` when released).

### 3. Onboard Piezo Sounder (Buzzer)
- Passive piezo buzzer connected to **GPIO26**.
- Supports tone generation (`tone()`, PWM audio, beeps).
- **Physical Mute Switch:** Allows silent code testing without disturbing others!

### 4. Maker Port (JST-SH 4-Pin Connector)
- Plug-and-play I2C port.
- **Pin Assignment:** Pin 1: GND, Pin 2: 3.3V, Pin 3: SDA (GPIO21), Pin 4: SCL (GPIO22).
- **Compatibility:** Directly compatible with SparkFun Qwiic, Adafruit STEMMA QT, and Seeed Grove sensors/displays (via conversion cable).

---

## 📡 Pilot Tutorial Scope: Control ESP32 Outputs with Telegram

The pilot tutorial for this pack is **[Control ESP32 Outputs with Telegram](https://my.cytron.io/tutorial/control-esp32-outputs-with-telegram)**.

### Tutorial Concept
1. The ESP32 connects to local 2.4GHz Wi-Fi.
2. The ESP32 polls the Telegram Bot API over HTTPS (`WiFiClientSecure`) using the `UniversalTelegramBot` library.
3. Incoming messages from Telegram trigger GPIO state changes (e.g. driving an onboard GPIO LED `HIGH` or `LOW`).
4. The user receives real-time confirmation replies on their smartphone or PC via Telegram.

---

*Made with ❤️ by Cytron Technologies | [www.cytron.io](https://www.cytron.io)*
