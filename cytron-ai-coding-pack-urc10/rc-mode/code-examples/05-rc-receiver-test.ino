/*******************************************************************************
 * 05 — RC Receiver Test
 * Cytron URC10 Sumo Robot Controller (RC Path)
 *
 * PURPOSE:
 * Reads raw PWM pulse widths from Throttle (D2) and Steering (D3) channels of
 * an RC receiver and prints the values to the Serial Monitor.
 * Motors are kept at ZERO speed for safety.
 *
 * SAFETY — BEFORE RUNNING THIS CODE:
 * 1. Lift the robot wheels off the ground.
 * 2. Confirm motor directions are correct before placing on the floor.
 * 3. Start at low speed (e.g. setSpeed(100)) before testing at full speed.
 * See safety-rules.md for full guidance.
 *
 * POWER & GND WARNING:
 * - Confirm your receiver's operating voltage (usually 5V).
 * - You MUST connect a common Ground (GND) wire between the receiver and URC10.
 * - Never reverse battery polarity on the URC10 power terminal (VM+ and GND).
 *
 * HARDWARE MAPPING:
 * - Throttle Input: D2 (Avoids reserved motor pins and D0/D1 Serial)
 * - Steering Input: D3 (Unplug Left Opponent IR Sensor to avoid conflicts)
 * - Motor Left  (Motor 1): PWM = D5, DIR = D4 (Reserved pins)
 * - Motor Right (Motor 2): PWM = D6, DIR = D7 (Reserved pins)
 * - Serial Monitor Pins: D0 (TX) and D1 (RX) are active. Avoid controlling LED0 (D0)
 *   and LED1 (D1) when Serial communication is active.
 *
 * SIGNAL REFERENCE:
 * - Typical RC PWM pulse width: ~1000 µs (min), ~1500 µs (neutral), ~2000 µs (max)
 *******************************************************************************/

#include <CytronMotorDriver.h>

// --- Pin Definitions ---
#define THROTTLE_PIN 2   // RC Throttle input (Channel 2/3)
#define STEERING_PIN 3   // RC Steering input (Channel 1/4)
#define SERIAL_BAUD  9600
#define PULSE_TIMEOUT 25000 // Timeout in microseconds (25ms) to catch 50Hz pulses

// --- Motor Objects ---
// Declare motor objects globally to keep them shut off during tests.
// ⚠️ D4, D5, D6, D7 are internally wired to the motor driver on the URC10.
//    Do NOT use them for anything else.
CytronMD motorL(PWM_DIR, 5, 4);
CytronMD motorR(PWM_DIR, 6, 7);

/*******************************************************************************
 * setup()
 * Runs once on power-up. Configures receiver pins, stops motors, and starts Serial.
 *******************************************************************************/
void setup() {
  // Set RC receiver input pins
  pinMode(THROTTLE_PIN, INPUT);
  pinMode(STEERING_PIN, INPUT);

  // Stop both motors immediately — safety first.
  motorL.setSpeed(0);
  motorR.setSpeed(0);

  // Start Serial communication at 9600 baud.
  // Note: Onboard LEDs D0 (LED0) and D1 (LED1) share pins with Serial RX/TX.
  // We do not configure or write to LED0 or LED1 while Serial is active.
  Serial.begin(SERIAL_BAUD);
  Serial.println("--- Cytron URC10 RC Receiver Test ---");
  Serial.println("Power order: Transmitter ON first, then Robot ON.");
  Serial.println("Lift wheels off the ground for testing.");
}

/*******************************************************************************
 * loop()
 * Continuously measures pulse widths and prints them. Motors remain stopped.
 *******************************************************************************/
void loop() {
  // Read the active-high pulse length in microseconds.
  // pulseIn() waits up to PULSE_TIMEOUT (25ms) for the pulse to start and end.
  // If no pulse is detected within the timeout, it returns 0 (failsafe/signal lost).
  unsigned long throttlePulse = pulseIn(THROTTLE_PIN, HIGH, PULSE_TIMEOUT);
  unsigned long steeringPulse = pulseIn(STEERING_PIN, HIGH, PULSE_TIMEOUT);

  // Ensure motors stay at absolute zero speed
  motorL.setSpeed(0);
  motorR.setSpeed(0);

  // Print raw pulse readings to the Serial Monitor
  Serial.print("Throttle (D2): ");
  if (throttlePulse == 0) {
    Serial.print("LOST (0 us)");
  } else {
    Serial.print(throttlePulse);
    Serial.print(" us");
  }

  Serial.print("  |  Steering (D3): ");
  if (steeringPulse == 0) {
    Serial.println("LOST (0 us)");
  } else {
    Serial.print(steeringPulse);
    Serial.println(" us");
  }

  // Small delay to make the Serial monitor readable
  delay(100);
}
