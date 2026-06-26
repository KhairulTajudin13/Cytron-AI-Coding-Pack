/*******************************************************************************
 * 02 — Sensor Test
 * Cytron URC10 Sumo Robot Controller
 *
 * PURPOSE:
 * Read the Start button, both edge sensors, and all five opponent sensors.
 * Print their live status to the Serial Monitor so you can verify every
 * sensor is wired and working before running the sumo code.
 *
 * TESTING STEPS:
 * -----------------------------------------------------------------------
 * Step 1: Upload this sketch (no battery needed — USB power is enough).
 * Step 2: Open Serial Monitor: Tools → Serial Monitor → set baud to 9600.
 * Step 3: You should see a table of sensors printing every 300ms.
 * Step 4: Manually trigger each sensor one at a time:
 *           - Edge sensors:    place on a white surface, or cover the sensor
 *           - Opponent sensors: wave a dark object in front of each one
 *           - Start button:    press it with your finger
 * Step 5: Confirm each sensor shows "TRIGGERED" when activated.
 * Step 6: If a sensor never shows TRIGGERED, check its wiring and ground.
 * -----------------------------------------------------------------------
 *
 * ACTIVE-LOW EXPLAINED:
 * All sensors on the URC10 use INPUT_PULLUP mode.
 * This means:
 *   - When NOT triggered: pin reads HIGH (1)
 *   - When TRIGGERED:     pin reads LOW  (0)  ← "active-low"
 *
 * In code, we detect a triggered sensor like this:
 *   if (digitalRead(SENSOR_PIN) == LOW)   ← triggered
 *   if (!digitalRead(SENSOR_PIN))         ← same thing using NOT operator
 *
 * PINOUT USED IN THIS SKETCH (matches original sample code):
 *   D13 = Start button
 *   D12 = Edge sensor LEFT
 *   D11 = Edge sensor RIGHT
 *   D3  = Opponent sensor LEFT (side)
 *   D10 = Opponent sensor RIGHT (side)
 *   A2  = Opponent sensor FRONT-LEFT
 *   A1  = Opponent sensor FRONT-CENTER
 *   A0  = Opponent sensor FRONT-RIGHT
 *
 * ⚠️ D4, D5, D6, D7 are reserved for the motor driver — NOT used here.
 *
 * HARDWARE: Cytron URC10 Sumo Robot Controller
 * BOARD:    Arduino Uno (select in Arduino IDE)
 * LIBRARY:  Cytron Motor Drivers Library (included but motors not used here)
 *******************************************************************************/

#include <CytronMotorDriver.h>

// --- Sensor and Button Pin Definitions ---
#define BUTTON      13  // Start button
#define EDGE_L      12  // Left edge / floor sensor
#define EDGE_R      11  // Right edge / floor sensor
#define OPPONENT_L   3  // Side opponent sensor — LEFT
#define OPPONENT_R  10  // Side opponent sensor — RIGHT
#define OPPONENT_FR A0  // Front opponent sensor — FRONT RIGHT
#define OPPONENT_FC A1  // Front opponent sensor — FRONT CENTER
#define OPPONENT_FL A2  // Front opponent sensor — FRONT LEFT

// --- LED Pins ---
// ⚠️ WARNING: LED0 (D0) = TX and LED1 (D1) = RX — the same pins used by Serial.
// Do NOT use pinMode(LED0/LED1) in this sketch while Serial.begin() is active.
// Doing so will corrupt serial output and may produce garbled text.
// LED mirroring is disabled in this sketch for this reason.
// Use 03-basic-sumo-behavior.ino to see LED mirroring in a non-Serial context.


/*******************************************************************************
 * setup()
 * Configure all sensor pins as input with pull-up resistors.
 * Start Serial communication for the Serial Monitor.
 *******************************************************************************/
void setup() {
  // INPUT_PULLUP enables a built-in resistor that keeps the pin at HIGH
  // when nothing is connected. When the sensor fires, it pulls the pin LOW.
  pinMode(BUTTON,      INPUT_PULLUP);
  pinMode(EDGE_L,      INPUT_PULLUP);
  pinMode(EDGE_R,      INPUT_PULLUP);
  pinMode(OPPONENT_L,  INPUT_PULLUP);
  pinMode(OPPONENT_R,  INPUT_PULLUP);
  pinMode(OPPONENT_FL, INPUT_PULLUP);
  pinMode(OPPONENT_FC, INPUT_PULLUP);
  pinMode(OPPONENT_FR, INPUT_PULLUP);

  // NOTE: LED mirroring is intentionally disabled in this sketch.
  // D0 (LED0) and D1 (LED1) conflict with Serial TX/RX.
  // See the LED warning comment near the top of this file for details.

  // Start serial communication at 9600 baud.
  // Open Serial Monitor in Arduino IDE to see the output.
  Serial.begin(9600);
  Serial.println("===================================");
  Serial.println("  URC10 Sensor Test — v1.0");
  Serial.println("  Trigger each sensor to confirm.");
  Serial.println("===================================");
  Serial.println();
}


/*******************************************************************************
 * printSensor()
 * Helper function: print one sensor's name and current state.
 *
 * Parameters:
 *   name  — label to display (e.g. "EDGE_L")
 *   pin   — Arduino pin number to read
 *******************************************************************************/
void printSensor(const char* name, int pin) {
  // Active-low: LOW means triggered, HIGH means not triggered.
  bool triggered = (digitalRead(pin) == LOW);

  Serial.print("  ");
  Serial.print(name);
  Serial.print(": ");
  if (triggered) {
    Serial.println("TRIGGERED <<<");
  } else {
    Serial.println("--");
  }
}


/*******************************************************************************
 * loop()
 * Read all sensors every 300ms and print to Serial Monitor.
 * Also mirror edge sensor states on the onboard LEDs.
 *******************************************************************************/
void loop() {
  Serial.println("--- Sensor Readings ---");

  // --- Edge Sensors ---
  printSensor("EDGE_L        (D12)", EDGE_L);
  printSensor("EDGE_R        (D11)", EDGE_R);

  // --- Side Opponent Sensors ---
  printSensor("OPPONENT_L    (D3) ", OPPONENT_L);
  printSensor("OPPONENT_R    (D10)", OPPONENT_R);

  // --- Front Opponent Sensors ---
  printSensor("OPPONENT_FL   (A2) ", OPPONENT_FL);
  printSensor("OPPONENT_FC   (A1) ", OPPONENT_FC);
  printSensor("OPPONENT_FR   (A0) ", OPPONENT_FR);

  // --- Start Button ---
  printSensor("BUTTON        (D13)", BUTTON);

  Serial.println();

  // NOTE: LED mirroring not used here — D0/D1 conflict with Serial.
  // Use Serial Monitor output above to monitor all sensor states.

  delay(300);  // Refresh every 300ms — slow enough to read on screen
}
