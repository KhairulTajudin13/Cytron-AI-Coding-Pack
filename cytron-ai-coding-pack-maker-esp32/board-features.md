# Board Features — Cytron Maker ESP32

This guide details the hardware features, onboard peripherals, electrical specifications, and interface capabilities of the **Cytron Maker ESP32**, verified directly against official datasheet (`source-docs/Maker ESP32 Datasheet.pdf`).

---

## 🎯 Hardware Feature Overview

```
                      +----------------------------------+
                      |           USB-C POWER           |
                      |          & PROGRAMMING           |
                      +----------------------------------+
                                       |
  +-------------------+                v                +-------------------+
  |  USER BUTTON      | ---> [ GPIO4 ]    [ GPIO26 ] <--- |  PIEZO BUZZER     |
  | (Active LOW)      |                                 | (w/ Mute Switch)  |
  +-------------------+                                 +-------------------+
                                       |
  +-------------------+                                 +-------------------+
  | 14x GPIO LEDs     | <--- [ GPIO 2, 12, 13, 16,  ]   |  MAKER PORT (I2C) |
  | (Active HIGH)     |      [ 17, 18, 19, 21, 22, ] --> |  GPIO21 (SDA)     |
  |                   |      [ 23, 25, 27, 32, 33  ]     |  GPIO22 (SCL)     |
  +-------------------+                                 +-------------------+
```

---

## 1. Power Architecture & USB-C Interface

- **Power Input:** USB Type-C connector or VIN pin (4.6V to 5.5V DC).
- **Onboard 3.3V Regulator:** High-capacity Low Dropout (LDO) linear regulator supplying up to **1.35A maximum current** (including onboard LED/buzzer usage).
- **Functions:**
  - Provides power to board & attached Maker Port accessories.
  - Firmware upload & Serial Monitor access via onboard USB-to-UART bridge.
  - Dedicated TX/RX communication activity LEDs.
  - Power LED (3.3V) indicating power status.

---

## 2. Onboard GPIO Indicator LEDs

The Maker ESP32 includes **14 onboard blue indicator LEDs** connected to the following GPIO pins:

| Pin | LED Indicator | Primary Function | Notes |
|---|---|---|---|
| **GPIO2** | Onboard LED | Digital Output / PWM | Used in Official Telegram Tutorial |
| **GPIO12** | Onboard LED | Digital Output / PWM | Strapping pin (Boot fails if pulled HIGH) |
| **GPIO13** | Onboard LED | Digital Output / PWM | Standard IO |
| **GPIO16** | Onboard LED | Digital Output / PWM | Standard IO |
| **GPIO17** | Onboard LED | Digital Output / PWM | Standard IO |
| **GPIO18** | Onboard LED | Digital Output / SPI SCK | Standard IO |
| **GPIO19** | Onboard LED | Digital Output / SPI MISO | Standard IO |
| **GPIO21** | Onboard LED / Maker Port | Digital Output / I2C SDA | Connected to Maker Port |
| **GPIO22** | Onboard LED / Maker Port | Digital Output / I2C SCL | Connected to Maker Port |
| **GPIO23** | Onboard LED | Digital Output / SPI MOSI | Standard IO |
| **GPIO25** | Onboard LED | Digital Output / DAC1 | Analog Output / Tone |
| **GPIO27** | Onboard LED | Digital Output / Touch | Standard IO |
| **GPIO32** | Onboard LED | Digital Output / ADC1 | Standard IO |
| **GPIO33** | Onboard LED | Digital Output / ADC1 | Standard IO |

- **Behavior:** Active HIGH. `digitalWrite(GPIO_NUM, HIGH)` turns the LED **ON**. `digitalWrite(GPIO_NUM, LOW)` turns it **OFF**.

---

## 3. Onboard User Pushbutton & Boot/EN Buttons

- **User Button:** Connected to **GPIO4**.
  - General-purpose pushbutton for user interaction.
  - Active LOW (`pinMode(4, INPUT_PULLUP)` reads `LOW` when pressed).
- **EN Button:** Hardware reset button (restarts execution).
- **Boot Button:** Forces firmware download mode during reset.

---

## 4. Passive Piezo Sounder (Buzzer) & Mute Switch

- **GPIO Assignment:** **GPIO26**
- **Sound Generation:** Programmable passive piezo sounder.
- **Physical Mute Switch:** Allows user to mute the buzzer hardware during silent development without affecting code.

---

## 5. Maker Port (JST-SH 4-Pin Connector)

Plug-and-play I2C expansion connector. Compatible with SparkFun Qwiic, Adafruit STEMMA QT, and Seeed Grove (via conversion cable).

| Pin | Signal | Description |
|---|---|---|
| **Pin 1** | **GND** | System Ground (0V) |
| **Pin 2** | **3V3** | 3.3V DC Power Output (up to 1.35A rail shared) |
| **Pin 3** | **SDA** | I2C Data (GPIO21) |
| **Pin 4** | **SCL** | I2C Clock (GPIO22) |

---

*Verified against `source-docs/Maker ESP32 Datasheet.pdf`*
