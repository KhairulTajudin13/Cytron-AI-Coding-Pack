/*
  Project: Dot Matrix Clock with NTP Server using ESP32
  Target Board: Cytron Maker ESP32
  
  Description:
  Fetches exact time and date from an internet NTP (Network Time Protocol) server 
  over Wi-Fi and displays a digital clock on a 4-in-1 MAX7219 Dot Matrix display module.
  
  Pin Connections (Maker ESP32 -> 4-in-1 MAX7219 Dot Matrix Display):
    5V   -> VCC
    GND  -> GND
    27   -> DIN (Data In)
    17   -> CS  (Chip Select / Load)
    25   -> CLK (Clock)
    
  Note on CS Pin:
  GPIO17 is used for CS instead of GPIO26 because GPIO26 on Maker ESP32 
  is connected to the onboard piezo buzzer.
  
  Required External Libraries:
  1. MD_MAX72XX by majicDesigns (Library Manager)
  2. MD_Parola by majicDesigns (Library Manager)
  3. NTPClient by Fabrice Weinberg (Library Manager / GitHub)
*/

#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

// Wi-Fi Credentials Placeholders
const char ssid[] = "YOUR_WIFI_SSID";         // Replace with your Wi-Fi SSID
const char password[] = "YOUR_WIFI_PASSWORD"; // Replace with your Wi-Fi Password

// NTP Client Setup
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

// MAX7219 Display Configuration
// Note: If text appears scrambled or inverted, change HARDWARE_TYPE to FC16_HW or GENERIC_HW
#define HARDWARE_TYPE MD_MAX72XX::ICSTATION_HW
#define MAX_DEVICES   4

#define DATA_PIN  27 // DIN on MAX7219
#define CS_PIN    17 // CS on MAX7219 (GPIO17 avoids onboard buzzer on GPIO26)
#define CLK_PIN   25 // CLK on MAX7219

MD_Parola DotMatrix = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

// Display Animation and Timing Variables
uint8_t scrollSpeed = 50;                     // Frame delay in ms for scrolling text
textEffect_t scrollEffect = PA_SCROLL_LEFT;
textPosition_t scrollAlign = PA_LEFT;
uint16_t scrollPause = 3000;                  // Pause duration in ms

long currentMillis = 0;
long previousMillis = 0;
int interval = 1000;

String formattedDate;
String timeStamp, hour, minute, second;
String dateStamp, year, month, date;
char dateBuffer[30] = "";                     // Fixed 30-byte buffer to prevent memory overflow

String monthArray[12] = {
  " Jan ", " Feb ", " Mar ", " Apr ", " May ", " Jun ",
  " Jul ", " Aug ", " Sep ", " Oct ", " Nov ", " Dec "
};

enum { TIME, DATE };
boolean displayMode = TIME;

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  Serial.print("Connecting to Wi-Fi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Initialize Dot Matrix Display
  DotMatrix.begin();
  DotMatrix.setIntensity(0); // Set brightness (0 to 15)

  // Initialize NTP Client (GMT+8 offset = 28800 seconds)
  timeClient.begin();
  timeClient.setTimeOffset(28800);

  // Display startup message
  DotMatrix.displayText("NTP Clock", scrollAlign, scrollSpeed, scrollPause, scrollEffect, scrollEffect);
  displayMode = DATE;
}

void loop() {
  // Sync time with NTP server
  while (!timeClient.update()) {
    timeClient.forceUpdate();
  }

  // Handle date scrolling animation completion
  if (displayMode == DATE && DotMatrix.displayAnimate()) {
    DotMatrix.displayReset();
    displayMode = TIME;
  }

  currentMillis = millis();
  if (currentMillis - previousMillis > interval && displayMode == TIME) {
    previousMillis = millis();

    // Formatted date string format from NTP: YYYY-MM-DDTHH:MM:SSZ
    formattedDate = timeClient.getFormattedDate();
    Serial.println(formattedDate);

    // Extract Date Components
    year = formattedDate.substring(0, 4);
    month = formattedDate.substring(5, 7);
    month = monthArray[month.toInt() - 1];
    date = formattedDate.substring(8, 10);
    date = String(date.toInt());
    dateStamp = year + ", " + date + month;
    dateStamp.toCharArray(dateBuffer, sizeof(dateBuffer));

    // Extract Time Components
    hour = formattedDate.substring(11, 13);
    minute = formattedDate.substring(14, 16);
    second = formattedDate.substring(17, 19);

    // Convert 24-hour to 12-hour format
    if (hour.toInt() == 0) {
      hour = String(hour.toInt() + 12);
    }
    else if (hour.toInt() < 13) {
      hour = String(hour.toInt());
    }
    else {
      hour = String(hour.toInt() - 12);
    }

    // Trigger date scroll at top of every minute
    if (second.toInt() == 0) {
      displayMode = DATE;
      DotMatrix.displayClear();
      DotMatrix.displayText(dateBuffer, scrollAlign, scrollSpeed, scrollPause, scrollEffect, scrollEffect);
      return;
    }
    // Blink colon every second
    else if (second.toInt() % 2) {
      timeStamp = hour + ":" + minute;
    }
    else {
      timeStamp = hour + " " + minute;
    }

    // Display static time centered on matrix
    DotMatrix.setTextAlignment(PA_CENTER);
    DotMatrix.print(timeStamp);
  }
}
