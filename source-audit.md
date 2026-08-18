# Technical Source Audit: Cytron AI Coding Packs

This document contains technical audits, hardware specifications, and pin mappings for the products supported in the **Cytron AI Coding Pack Repository**.

---

# Part 1: Cytron URC10 Sumo Robot Controller

## 1. Product Name and Purpose
* **Product Name:** URC10 Sumo Robot Controller (by Cytron Technologies).
* **Purpose:** A specialized all-in-one controller for Sumo Robots. Combines an Arduino-compatible microcontroller with a high-current dual-channel motor driver and dedicated sensor ports.

## 2. Controller/Microcontroller Type
* **Type:** Arduino-compatible (standard Arduino Uno form factor/logic).
* **Microcontroller:** ATmega328P (select "Arduino Uno" in Arduino IDE).

## 3. Programming Platform and Language
* **Platform:** Arduino IDE.
* **Language:** C++ / Arduino Sketch.

## 4. Required Setup & Drivers
* **Board Selection:** "Arduino/Genuino Uno".
* **USB Driver:** CH340 USB-to-UART driver.
* **Required Library:** `Cytron Motor Drivers Library` (`#include <CytronMotorDriver.h>`).

## 5. Motor Driver Pin Mapping
* Control Scheme: **PWM / DIR**.
* **Motor 1 (Left):** PWM: **D5**, DIR: **D4**.
* **Motor 2 (Right):** PWM: **D6**, DIR: **D7**.

## 6. Sensor Pin Mapping
* **Start Button:** D13.
* **Edge Sensors:** Left Edge: D12, Right Edge: D11.
* **Opponent Sensors:** Left: D3, Right: D10, Front Left: A2, Front Center: A1, Front Right: A0.
* **Ultrasonic Ports:**
  * Sensor 1: TRIG (D9), ECHO (D8)
  * Sensor 2: TRIG (D11), ECHO (D10) *(Caution: Shares pins with Right Edge and Right Opponent)*.

## 7. Power & Safety Limits
* **Input Voltage (Vin):** 8V to 25V DC (VM & GND terminals).
* **Max Motor Current:** 10A Continuous, 30A Peak (< 10 seconds).
* **Safety Rules:** Reverse battery polarity will destroy the board **instantaneously**. Avoid using pins D4–D7 for sensors or external shields.

---

# Part 2: Cytron Maker ESP32

## 1. Board Overview & Architecture
* **Product Name:** Cytron Maker ESP32.
* **Module:** ESP32-WROOM-32E (N8 - 8MB Flash memory).
* **USB Interface:** USB Type-C (Silicon Labs CP2104 / CH340 USB-to-UART bridge).
* **Power Supply:** USB 5V VBUS rail, onboard 3.3V LDO voltage regulator supplying up to **1.35A max**.

## 2. Onboard Peripherals & GPIO Mapping
* **User Button:** Connected to **GPIO4** (Active LOW; requires `INPUT_PULLUP`).
* **Piezo Buzzer:** Connected to **GPIO26** via transistor driver.
* **GPIO Indicator LEDs:** Onboard blue LEDs connected to GPIOs: `0, 2, 4, 5, 12, 13, 14, 15, 16, 17, 18, 19, 21, 22, 23, 25, 26, 27, 32, 33`.
* **Power LEDs:** Onboard status LEDs for VIN, 3.3V, and USB 5V.

## 3. GPIO Pin Classification & Restrictions

| Category | GPIO Pins | Restriction / Behavioral Note |
|---|---|---|
| **Input-Only Pins** | GPIO34, 35, 36, 39 | No internal pull-up/pull-down resistors. Cannot be used as outputs. |
| **Flash Memory Pins** | GPIO6, 7, 8, 9, 10, 11 | Integrated SPI flash connection. **DO NOT USE.** |
| **Boot Strapping Pins** | GPIO0, 2, 4, 5, 12, 15 | Must be at required logic levels during startup/boot sequence. |
| **Buzzer Pin** | **GPIO26** | **Hardwired to piezo buzzer.** Do NOT use as CS / SPI data pin unless audio tone feedback is desired. |
| **Safe General Purpose I/O** | GPIO13, 14, 16, 17, 18, 19, 21, 22, 23, 25, 27, 32, 33 | Safe for sensors, displays, relays, actuators, and software SPI. |

---

# Part 3: Tutorial Technical Audits for Maker ESP32

## 1. Telegram Remote Control Tutorial Audit
* **Tutorial Purpose:** Control ESP32 GPIO outputs wirelessly via Telegram messaging bot.
* **Baseline Code:** `sample-code/telegram-basic.ino`.
* **GPIO Allocation:**
  * LED 1: **GPIO2** (Onboard blue GPIO indicator LED).
  * LED 2: **GPIO16** (External LED output).
* **Libraries:** `UniversalTelegramBot` by Brian Lough, `WiFiClientSecure`.

## 2. Dot Matrix Clock with NTP Server Tutorial Audit
* **Tutorial Purpose:** Display internet time & scrolling date on a 4-in-1 MAX7219 Dot Matrix display.
* **Sample Code:** `sample-code/dot-matrix-clock-maker-esp32.ino`.
* **Hardware Conflict Resolved:**
  * Original tutorial assigned CS to **GPIO26**. On Maker ESP32, GPIO26 drives the onboard buzzer, causing loud screeching noise on display updates.
  * **Upgraded CS Pin:** **GPIO17** (Clean SPI CS pin with onboard blue indicator LED).
* **Memory Overflow Bug Fixed:**
  * Original code defined `char dateBuffer[] = ""` (1 byte) and executed `dateStamp.toCharArray(dateBuffer, dateStamp.length()+1)`, causing stack memory corruption.
  * **Fixed Code:** `char dateBuffer[30] = ""` (Prevents memory overflow).
* **Libraries:** `MD_Parola`, `MD_MAX72XX`, `NTPClient`.

## 3. Blynk App LED Strip Control Tutorial Audit
* **Platform Status:** **Blynk Legacy is PERMANENTLY RETIRED (Dec 2022).** Original tutorial code using `BlynkSimpleEsp32.h` without Template IDs will not connect.
* **Migration Requirement:** Must be updated for **Blynk IoT** (`blynk.cloud`) with `BLYNK_TEMPLATE_ID` & `BLYNK_TEMPLATE_NAME`.
* **Power Safety:** 1M 30-LED SK6812 strip requires up to **1.8A max** at full white brightness. Powered via external 5V 2A DC supply with common GND.

## 4. ESP32 Digital Clock Tutorial Audit
* **Tutorial URL:** `https://my.cytron.io/tutorial/esp32-digital-clock`
* **Tutorial Purpose:** Display an internet-synced real-time clock and date on an OLED display or Grove RGB LCD using ESP32 built-in NTP support without external RTC hardware.
* **Revamp Status:** Grade A - Valid (Keep decision). Small revamp scope.
* **Sample Code:** `sample-code/esp32-digital-clock-maker-esp32.ino`.
* **Maker ESP32 Hardware Integration:**
  * Connects I2C OLED / Grove LCD directly via the onboard **Maker Port** (4-pin Grove I2C connector).
  * Pin Mapping: **SDA = GPIO21**, **SCL = GPIO22**.
* **Technical Audits & Fixes Implemented:**
  1. **Timezone Configuration:** Configured default offset `gmtOffset_sec = 28800` (GMT+8 for Malaysia / Singapore). Documented POSIX timezone strings (`setenv("TZ", ...)`, `tzset()`) for automatic DST adjustment.
  2. **OLED I2C Address Variation:** Documented standard `0x3C` (generic OLED modules) vs `0x3D` (Adafruit OLED modules) I2C address differences.
  3. **Async NTP Sync Robustness:** Added initial NTP sync retry loop (`syncRetries < 10`) after `timeClient.begin()` to prevent initial blank screen failures on slow Wi-Fi.
  4. **WiFi Auto-Reconnection:** Added automatic Wi-Fi reconnect helper (`checkWiFiConnection()`) in `loop()` so the clock recovers seamlessly if the Wi-Fi connection drops.
  5. **Flicker-Free Display Refresh:** Removed redundant screen clear calls on every loop cycle, refreshing display cleanly once per second.
* **Libraries Required:** `Adafruit_SSD1306`, `Adafruit_GFX`, `NTPClient`, `TimeLib`.
