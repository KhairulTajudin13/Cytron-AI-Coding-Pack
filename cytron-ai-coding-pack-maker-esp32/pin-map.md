# Pin Map & Hardware Reference — Cytron Maker ESP32

This document provides the complete pinout breakdown, peripheral mapping, special pin caveats, and electrical rules for the **Cytron Maker ESP32**.

---

## 📌 Master GPIO Table

| GPIO Pin | Onboard Hardware | Input / Output | Special Functions | Safe for General IO? |
|---|---|---|---|---|
| **GPIO0** | — | In/Out | Strapping Pin (Flash Mode) | ⚠️ Pull-up required during boot |
| **GPIO2** | Onboard LED | In/Out | Strapping Pin / Onboard LED | ✅ Safe Output / LED |
| **GPIO4** | User Pushbutton | In/Out | Strapping Pin / User Button | ✅ Safe Input (Active LOW) |
| **GPIO5** | — | In/Out | Strapping Pin (VSPI CS) | ✅ Safe IO |
| **GPIO6-11**| — | **DO NOT USE** | Connected to Internal SPI Flash | ❌ **NEVER USE** |
| **GPIO12** | Onboard LED | In/Out | Strapping Pin (Boot fails if HIGH) | ⚠️ Keep LOW during power-on |
| **GPIO13** | Onboard LED | In/Out | HSPI MOSI | ✅ Safe Output / LED |
| **GPIO14** | — | In/Out | HSPI CLK / Touch | ✅ Safe IO |
| **GPIO15** | — | In/Out | Strapping Pin (HSPI CS) | ⚠️ Boot timing sensitivity |
| **GPIO16** | Onboard LED | In/Out | UART2 RX / Output LED | ✅ Safe Output / LED |
| **GPIO17** | Onboard LED | In/Out | UART2 TX / Output LED | ✅ Safe Output / LED |
| **GPIO18** | Onboard LED | In/Out | VSPI SCK / Output LED | ✅ Safe Output / LED |
| **GPIO19** | Onboard LED | In/Out | VSPI MISO / Output LED | ✅ Safe Output / LED |
| **GPIO21** | Onboard LED / Maker Port | In/Out | I2C SDA / Output LED | ✅ Safe IO / I2C Data |
| **GPIO22** | Onboard LED / Maker Port | In/Out | I2C SCL / Output LED | ✅ Safe IO / I2C Clock |
| **GPIO23** | Onboard LED | In/Out | VSPI MOSI / Output LED | ✅ Safe Output / LED |
| **GPIO25** | Onboard LED | In/Out | DAC1 / Output LED | ✅ Safe Output / LED |
| **GPIO26** | Piezo Buzzer | In/Out | DAC2 / Passive Buzzer | ✅ Safe Audio Output |
| **GPIO27** | Onboard LED | In/Out | Touch / Output LED | ✅ Safe Output / LED |
| **GPIO32** | Onboard LED | In/Out | ADC1_CH4 / Output LED | ✅ Safe IO / Analog In |
| **GPIO33** | Onboard LED | In/Out | ADC1_CH5 / Output LED | ✅ Safe IO / Analog In |
| **GPIO34** | — | **INPUT ONLY** | ADC1_CH6 | ⚠️ Input only (No internal pull-up) |
| **GPIO35** | — | **INPUT ONLY** | ADC1_CH7 | ⚠️ Input only (No internal pull-up) |
| **GPIO36** | — | **INPUT ONLY** | ADC1_CH0 (VP) | ⚠️ Input only (No internal pull-up) |
| **GPIO39** | — | **INPUT ONLY** | ADC1_CH3 (VN) | ⚠️ Input only (No internal pull-up) |

---

## 🛑 Critical Pin Categories & Rules

### 1. Input-Only Pins (GPIO 34, 35, 36, 39)
- **Restriction:** These pins **CANNOT** be configured as digital outputs (`OUTPUT`).
- **Missing Hardware:** They do **not** possess software-controllable internal pull-up or pull-down resistors.
- **Use Case:** Analog sensors, external voltage monitoring, digital input with external pull resistors.

### 2. Internal Flash Pins (GPIO 6 to 11)
- **Restriction:** Connected internally to the 8MB SPI Flash memory chip inside the ESP32-WROOM-32E module.
- **Danger:** Assigning these pins in code or connecting external wires to GPIO 6–11 will **corrupt code execution** and cause instant boot loops!

### 3. Bootstrapping / Strapping Pins (GPIO 0, 2, 4, 5, 12, 15)
- **Explanation:** During reset or power-up, the ESP32 checks the voltage levels on these pins to determine whether to enter Flash Download Mode or Normal SPI Boot Mode.
- **GPIO12 Warning:** Must NOT be pulled HIGH externally during power-up, or the voltage regulator logic may fail and crash the ESP32 boot process.
- **GPIO0 Warning:** Pulling LOW during boot forces the ESP32 into programming mode.

### 4. Preservation of Tutorial Pin Assignments
- Always preserve the original tutorial pin assignments (e.g. GPIO2 or GPIO12 for Telegram LED output) unless specifically requested by the user.

---

*Made with ❤️ by Cytron Technologies | [www.cytron.io](https://www.cytron.io)*
