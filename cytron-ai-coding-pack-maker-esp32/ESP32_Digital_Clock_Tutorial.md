# ESP32 Digital Clock

**Category:** ESP32 | **Level:** Beginner | **Board:** Cytron Maker ESP32

---

## Objective

The objective of the **ESP32 Digital Clock** project is to create a reliable, internet-synchronized clock system that displays accurate real-time date and time on a digital display using the **Cytron Maker ESP32** microcontroller. 

By connecting to Wi-Fi and accessing NTP (Network Time Protocol) servers, the clock ensures precise and automatic time updates without requiring manual time adjustments or an external Real-Time Clock (RTC) module. This project provides a simple yet effective solution for accurate timekeeping, perfect for educational, home, or office use.

---

## List of Components

* **[Cytron Maker ESP32](https://my.cytron.io/p-maker-esp32)** (ESP32 Development Board with USB-C and Maker Port)
* **USB Type-C Cable**
* **0.96" I2C OLED Display Module (SSD1306)** or **Grove 16x2 LCD Display**
* **Maker Port 4-Pin Grove Cable / Jumper Wires**

---

## Circuit Diagram & Wiring Table

The **Cytron Maker ESP32** features an onboard **Maker Port** (Grove-compatible 4-pin connector) which routes the ESP32's hardware I2C bus directly. Simply connect the I2C display module to the Maker Port.

| Display Pin | Maker ESP32 Pin / Port | Description |
| :---: | :---: | :--- |
| **SDA** | **GPIO21** | I2C Data Line (Maker Port Pin 1) |
| **SCL** | **GPIO22** | I2C Clock Line (Maker Port Pin 2) |
| **VCC** | **3.3V / 5V** | Power Supply (Maker Port VCC) |
| **GND** | **GND** | Ground (Maker Port GND) |

---

## Step 1: Download Required Libraries

Before uploading the code, open your **Arduino IDE** and install the following required libraries via **Tools → Manage Libraries** (`Ctrl+Shift+I`):

1. **`Adafruit SSD1306`** (by Adafruit) — Driver for the 0.96" OLED display.
2. **`Adafruit GFX Library`** (by Adafruit) — Core graphics library dependency.
3. **`NTPClient`** (by Fabrice Weinberg) — Handles Network Time Protocol synchronization.
4. **`Time` / `TimeLib`** (by Paul Stoffregen) — Simplifies date and time formatting.

> 💡 **I2C Address Note:** Most generic 0.96" OLED modules use I2C address `0x3C`, while official Adafruit modules use `0x3D`. If your display remains blank, check your module's address or run an I2C scanner sketch.

---

## Step 2: Code Implementation

Copy and upload the following code to your Cytron Maker ESP32. Make sure to replace `"YOUR_WIFI_SSID"` and `"YOUR_WIFI_PASSWORD"` with your actual Wi-Fi network credentials.

```cpp
/*
  Project: ESP32 Digital Clock with NTP Synchronization
  Target Board: Cytron Maker ESP32
  
  Description:
  An internet-synchronized real-time digital clock using Cytron Maker ESP32.
  Fetches precise time from an NTP (Network Time Protocol) server over Wi-Fi
  and displays time and date on an I2C OLED display connected via Maker Port.
  
  Hardware Connection:
    Maker Port SDA -> GPIO21
    Maker Port SCL -> GPIO22
    VCC            -> 3.3V / 5V
    GND            -> GND
*/

#include <WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include <TimeLib.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Wi-Fi Credentials Placeholders
const char* ssid = "YOUR_WIFI_SSID";         // Replace with your Wi-Fi SSID
const char* password = "YOUR_WIFI_PASSWORD"; // Replace with your Wi-Fi Password

// OLED Display Configuration
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1

// Common I2C Addresses: 0x3C (Generic/Chinese modules) or 0x3D (Adafruit modules)
#define OLED_I2C_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// NTP Client Configuration
// GMT+8 Offset = 8 hours * 3600 seconds = 28800 seconds (Malaysia / Singapore)
const long gmtOffset_sec = 28800;
const int updateInterval_ms = 60000; // Update NTP time every 60 seconds

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", gmtOffset_sec, updateInterval_ms);

// Timing variables for smooth flicker-free screen updates
unsigned long previousMillis = 0;
const long refreshInterval = 1000; // Update display every 1 second

// WiFi Reconnection Helper
void checkWiFiConnection() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Wi-Fi connection lost. Reconnecting...");
    display.clearDisplay();
    display.setCursor(0, 20);
    display.setTextSize(1);
    display.println("Reconnecting WiFi...");
    display.display();
    
    WiFi.disconnect();
    WiFi.reconnect();
    
    int retries = 0;
    while (WiFi.status() != WL_CONNECTED && retries < 20) {
      delay(500);
      Serial.print(".");
      retries++;
    }
    
    if (WiFi.status() == WL_CONNECTED) {
      Serial.println("\nReconnected to Wi-Fi!");
    }
  }
}

void setup() {
  Serial.begin(115200);
  
  // Initialize I2C on Maker Port (GPIO21 = SDA, GPIO22 = SCL)
  Wire.begin(21, 22);

  // Initialize OLED Display
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_I2C_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed. Check I2C address (0x3C vs 0x3D) or Maker Port wiring."));
    for (;;); // Loop forever if display initialization fails
  }
  
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(0, 10);
  display.println("Maker ESP32 Clock");
  display.println("Connecting WiFi...");
  display.display();

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Initialize NTP Client
  timeClient.begin();

  // Robust NTP initial sync retry loop
  display.clearDisplay();
  display.setCursor(0, 20);
  display.println("Syncing NTP Time...");
  display.display();
  
  int syncRetries = 0;
  while (!timeClient.update() && syncRetries < 10) {
    timeClient.forceUpdate();
    delay(1000);
    syncRetries++;
    Serial.println("Waiting for NTP sync...");
  }

  // Set initial time in TimeLib
  setTime(timeClient.getEpochTime());
  Serial.println("NTP Time Synchronized Successfully!");
}

void loop() {
  // Graceful Wi-Fi auto-reconnection check
  checkWiFiConnection();

  // Update display once every second (flicker-free update)
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= refreshInterval) {
    previousMillis = currentMillis;

    // Periodic NTP update check
    if (timeClient.update()) {
      setTime(timeClient.getEpochTime());
    }

    // Format Time (HH:MM:SS)
    char timeStr[10];
    sprintf(timeStr, "%02d:%02d:%02d", hour(), minute(), second());

    // Format Date (DD/MM/YYYY)
    char dateStr[12];
    sprintf(dateStr, "%02d/%02d/%04d", day(), month(), year());

    // Day of the week string
    const char* daysOfWeek[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    const char* dayName = daysOfWeek[weekday() - 1];

    // Render to OLED Display
    display.clearDisplay();
    
    // Header Title
    display.setTextSize(1);
    display.setCursor(10, 0);
    display.print("MAKER ESP32 CLOCK");
    display.drawFastHLine(0, 10, 128, SSD1306_WHITE);

    // Large Time Text
    display.setTextSize(2);
    display.setCursor(16, 20);
    display.print(timeStr);

    // Date & Day Footer Text
    display.setTextSize(1);
    display.setCursor(12, 48);
    display.print(dayName);
    display.print(", ");
    display.print(dateStr);

    display.display();
  }
}
```

---

## Step 3: Timezone & Daylight Saving Configuration

### Timezone Offset Calculation
The code uses seconds for timezone offsets (`gmtOffset_sec = UTC_Offset * 3600`):

| Region / Timezone | Offset in Seconds (`gmtOffset_sec`) |
| :--- | :---: |
| **Malaysia & Singapore (MYT / SGT, GMT+8)** | `28800` |
| **United Kingdom (GMT+0)** | `0` |
| **US Eastern Standard Time (EST, GMT-5)** | `-18000` |
| **Japan Standard Time (JST, GMT+9)** | `32400` |

### Daylight Saving Time (DST) with POSIX Strings
For regions with Daylight Saving Time, you can use ESP32's built-in POSIX timezone string handler instead of static offset calculation:
```cpp
// Example for Central European Time with automatic DST
setenv("TZ", "CET-1CEST,M3.5.0/02,M10.5.0/03", 1);
tzset();
```

---

## Troubleshooting Guide

| Symptom | Probable Cause | Solution |
| :--- | :--- | :--- |
| **Display is completely blank** | Wrong I2C address or incorrect wiring | Check if your OLED module uses address `0x3C` or `0x3D`. Verify Maker Port cable is plugged in firmly. |
| **Stuck on "Connecting WiFi..."** | Incorrect Wi-Fi SSID/password or 5GHz Wi-Fi | Ensure credentials are correct. ESP32 supports **2.4GHz Wi-Fi networks only**. |
| **Time shows 01/01/1970 00:00:00** | NTP server request timed out or router blocking UDP port 123 | Verify internet connection and check if router firewall blocks NTP port 123. |
| **Display flickers continuously** | Calling `clear()` on every loop iteration | Ensure display updates occur inside a 1-second `millis()` timer check. |

---

**Your Cytron Maker ESP32 Digital Clock is ready!**
