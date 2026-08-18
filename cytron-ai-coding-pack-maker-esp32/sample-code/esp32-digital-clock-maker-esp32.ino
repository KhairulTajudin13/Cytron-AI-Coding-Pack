/*
  Project: ESP32 Digital Clock with NTP Synchronization
  Target Board: Cytron Maker ESP32
  
  Description:
  An internet-synchronized real-time digital clock using Cytron Maker ESP32.
  Fetches precise time from an NTP (Network Time Protocol) server over Wi-Fi
  and displays time and date on an I2C OLED or Grove RGB LCD display connected
  via the onboard Maker Port (I2C).
  
  Hardware Connection (Maker ESP32 -> Maker Port I2C):
    Maker Port SDA -> GPIO21
    Maker Port SCL -> GPIO22
    VCC            -> 3.3V or 5V
    GND            -> GND
    
  Required Libraries:
  1. Adafruit SSD1306 (by Adafruit) - for OLED display
  2. Adafruit GFX Library (by Adafruit) - graphics dependency
  3. NTPClient (by Fabrice Weinberg) - NTP sync wrapper
  4. TimeLib (by Paul Stoffregen) - Time manipulation helpers
  (Or Grove RGB LCD library if using Grove 16x2 LCD)
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
    } else {
      Serial.println("\nReconnection failed. Will retry next cycle.");
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
    for (;;); // Don't proceed, loop forever
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

  // Robust NTP initial sync with retry loop
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
