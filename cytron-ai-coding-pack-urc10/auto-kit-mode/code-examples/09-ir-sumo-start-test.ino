/*******************************************************************************
 * 09 — IR Sumo Start Signal Test
 * 1KG Autonomous Sumo Robot Starter Kit using URC10
 *
 * PURPOSE:
 * Tests the IR Sumo Start module signal without moving any motors.
 * Use this code first to confirm the module is wired correctly and that
 * D2 reads HIGH on RUN and LOW on READY / STOP before running the full
 * match code (08-auto-kit-standard.ino).
 *
 * HOW TO USE:
 *   1. Wire the IR Sumo Start module: + to 5V, - to GND, S to D2
 *   2. Upload this code to the URC10
 *   3. Power on — the onboard LED (D13) should be OFF (READY state)
 *   4. Send RUN from the IR transmitter or press the module's test button
 *   5. Confirm the D13 LED turns ON (RUN = HIGH detected)
 *   6. Send STOP — confirm the D13 LED turns OFF (STOP = LOW)
 *   7. If LED behavior is correct, proceed to 08-auto-kit-standard.ino
 *
 * ⚠️  This code does NOT move the motors at any time.
 *     It is safe to run with the battery connected.
 *
 * SIGNAL LOGIC:
 *   D2 HIGH = RUN        → D13 LED ON
 *   D2 LOW  = READY/STOP → D13 LED OFF
 *
 * WIRING:
 *   IR Sumo Start (+) → URC10 5V
 *   IR Sumo Start (-) → URC10 GND
 *   IR Sumo Start (S) → URC10 D2
 *
 * PIN MODE:
 *   D2 uses INPUT (not INPUT_PULLUP).
 *   The module provides a driven digital output — no internal pullup needed.
 *
 * D2 ROLE NOTE:
 *   In Auto Kit Mode, D2 is the IR Sumo Start signal input.
 *   In RC Mode, D2 is used for RC throttle pulse input.
 *   These modes are mutually exclusive — confirm which mode is active
 *   before using this pin for anything else.
 *
 * HARDWARE: Cytron URC10 + Cytron IR Sumo Start Module (IR-SUMO-START)
 * BOARD:    Arduino Uno (select in Arduino IDE)
 * PRODUCT:  https://my.cytron.io/p-ir-sumo-start-module
 *******************************************************************************/

// Pin for IR Sumo Start signal input.
// Auto Kit Mode standard: D2 = IR Sumo Start.
const uint8_t IR_SUMO_START_PIN = 2;

// D13 = onboard Arduino LED (active-high on most Uno-compatible boards).
// Used here as a simple visual indicator — no other hardware needed.
const uint8_t STATUS_LED_PIN = 13;


void setup() {
  // IR Sumo Start: INPUT mode — module drives D2 actively.
  // Do NOT use INPUT_PULLUP for this module.
  pinMode(IR_SUMO_START_PIN, INPUT);

  // D13 LED: output for visual signal indicator.
  pinMode(STATUS_LED_PIN, OUTPUT);

  // Start with LED off — READY state.
  digitalWrite(STATUS_LED_PIN, LOW);
}


void loop() {
  // Read the IR Sumo Start signal on D2.
  // HIGH = RUN  → LED ON
  // LOW  = READY / STOP → LED OFF

  if (digitalRead(IR_SUMO_START_PIN) == HIGH) {
    // RUN signal received — LED on.
    digitalWrite(STATUS_LED_PIN, HIGH);
  } else {
    // READY or STOP state — LED off.
    digitalWrite(STATUS_LED_PIN, LOW);
  }

  // No motor commands in this test file.
  // Motors are never moved regardless of signal state.
}
