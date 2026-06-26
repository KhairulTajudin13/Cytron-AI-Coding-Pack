/*******************************************************************************
 * 06 — Radio Controlled Drive
 * Cytron URC10 Sumo Robot Controller (RC Path)
 *
 * PURPOSE:
 * Reads throttle and steering pulses from an RC receiver, mixes them for arcade
 * drive, applies a center deadband, and drives the motors using the Cytron
 * Motor Drivers Library. Includes a failsafe for signal loss.
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
 * - Throttle Input: D2
 * - Steering Input: D3 (Unplug Left Opponent IR Sensor)
 * - Motor Left  (Motor 1): PWM = D5, DIR = D4 (Reserved pins)
 * - Motor Right (Motor 2): PWM = D6, DIR = D7 (Reserved pins)
 * - Serial Monitor: Pins D0 and D1 are active for diagnostics. Do not write
 *   GPIO outputs to D0 and D1 (LED0 and LED1).
 *
 * MOTOR WIRING NOTE:
 * // NOTE: "Forward" assumes default motor wiring on the URC10.
 * // If a motor spins the wrong way, swap its two wires on the motor terminal.
 *******************************************************************************/

#include <CytronMotorDriver.h>

// --- Pin Definitions ---
#define THROTTLE_PIN 2   // RC Throttle input (Channel 2 or 3)
#define STEERING_PIN 3   // RC Steering input (Channel 1 or 4)
#define SERIAL_BAUD  9600
#define PULSE_TIMEOUT 25000 // Timeout in microseconds (25ms) for 50Hz pulses

// --- Calibration Constants ---
#define RC_MIN       1000  // Minimum expected RC pulse in us
#define RC_NEUTRAL   1500  // Center/neutral RC pulse in us
#define RC_MAX       2000  // Maximum expected RC pulse in us
#define RC_DEADBAND  50    // Ignore stick variations within +/- 50us of center
#define MOTOR_MAX    255   // Max speed value for Cytron setSpeed()

// --- Failsafe Limits ---
#define SAFE_MIN     900   // Absolute minimum safe pulse width in us
#define SAFE_MAX     2100  // Absolute maximum safe pulse width in us

// --- Motor Objects ---
// CytronMD(mode, pwmPin, dirPin)
// Motor Left  (Motor 1): PWM on D5, Direction on D4
// Motor Right (Motor 2): PWM on D6, Direction on D7
CytronMD motorL(PWM_DIR, 5, 4);
CytronMD motorR(PWM_DIR, 6, 7);

// Declare function prototype
int mapRcChannel(unsigned long pulse, int deadband);

/*******************************************************************************
 * setup()
 * Runs once on power-up. Configures receiver pins, stops motors, and starts Serial.
 *******************************************************************************/
void setup() {
  // Set RC receiver input pins
  pinMode(THROTTLE_PIN, INPUT);
  pinMode(STEERING_PIN, INPUT);

  // Stop both motors immediately on startup — safety first.
  motorL.setSpeed(0);
  motorR.setSpeed(0);

  // Initialize Serial for speed diagnostics
  Serial.begin(SERIAL_BAUD);
  Serial.println("--- Cytron URC10 Radio Controlled Drive ---");
  Serial.println("Power order: Transmitter ON first, then Robot ON.");
  Serial.println("Lift wheels off the ground for testing.");
}

/*******************************************************************************
 * loop()
 * Reads pulses, validates signals, mixes arcade drive, and commands motors.
 *******************************************************************************/
void loop() {
  // Measure pulse lengths in microseconds
  unsigned long throttlePulse = pulseIn(THROTTLE_PIN, HIGH, PULSE_TIMEOUT);
  unsigned long steeringPulse = pulseIn(STEERING_PIN, HIGH, PULSE_TIMEOUT);

  // -----------------------------------------------------------------------
  // SIGNAL-LOSS FAILSAFE:
  // If the transmitter is off, out of range, or disconnected, pulseIn()
  // returns 0. Also checks if pulses are physically impossible (noise).
  // -----------------------------------------------------------------------
  if (throttlePulse == 0 || steeringPulse == 0 ||
      throttlePulse < SAFE_MIN || throttlePulse > SAFE_MAX ||
      steeringPulse < SAFE_MIN || steeringPulse > SAFE_MAX) {
    
    // Stop both motors immediately to prevent runaway robot
    motorL.setSpeed(0);
    motorR.setSpeed(0);
    
    Serial.println("WARNING: Signal lost or out of bounds! Motors halted.");
    delay(100);
    return; // Exit loop and wait for next signal frame
  }

  // -----------------------------------------------------------------------
  // CONVERT & SCALE INPUTS:
  // Convert microsecond pulses (1000 to 2000) to speed values (-255 to 255)
  // applying the center deadband.
  // -----------------------------------------------------------------------
  int throttleSpeed = mapRcChannel(throttlePulse, RC_DEADBAND);
  int steeringSpeed = mapRcChannel(steeringPulse, RC_DEADBAND);

  // -----------------------------------------------------------------------
  // MIX SPEEDS (ARCADE DRIVE):
  // Left Motor Speed  = Throttle + Steering
  // Right Motor Speed = Throttle - Steering
  // -----------------------------------------------------------------------
  int leftMotorSpeed = throttleSpeed + steeringSpeed;
  int rightMotorSpeed = throttleSpeed - steeringSpeed;

  // Constrain speeds to remain within motor driver limits [-255, 255]
  leftMotorSpeed = constrain(leftMotorSpeed, -MOTOR_MAX, MOTOR_MAX);
  rightMotorSpeed = constrain(rightMotorSpeed, -MOTOR_MAX, MOTOR_MAX);

  // -----------------------------------------------------------------------
  // DRIVE MOTORS:
  // Write the calculated speeds to the motor driver.
  // -----------------------------------------------------------------------
  motorL.setSpeed(leftMotorSpeed);
  motorR.setSpeed(rightMotorSpeed);

  // Print diagnostic speeds to Serial Monitor
  Serial.print("T-Pulse: ");
  Serial.print(throttlePulse);
  Serial.print(" us | S-Pulse: ");
  Serial.print(steeringPulse);
  Serial.print(" us | Left Spd: ");
  Serial.print(leftMotorSpeed);
  Serial.print(" | Right Spd: ");
  Serial.println(rightMotorSpeed);

  // Small delay to match the typical 20ms RC frame interval
  delay(20);
}

/*******************************************************************************
 * mapRcChannel(unsigned long pulse, int deadband)
 * Maps an RC pulse width (1000 - 2000 us) to motor speed (-255 to 255).
 * Applies a deadband around the center (1500 us). Returns 0 if in deadband.
 *******************************************************************************/
int mapRcChannel(unsigned long pulse, int deadband) {
  // Safe default
  if (pulse == 0) return 0;
  
  long deviation = (long)pulse - RC_NEUTRAL;

  // If signal is within deadband around neutral center, return 0 (no motion)
  if (abs(deviation) < deadband) {
    return 0;
  }

  int mappedSpeed;
  
  // Scale deviation to speed ranges, handling deadband offset smoothly
  if (deviation > 0) {
    mappedSpeed = map(pulse, RC_NEUTRAL + deadband, RC_MAX, 0, MOTOR_MAX);
  } else {
    mappedSpeed = map(pulse, RC_MIN, RC_NEUTRAL - deadband, -MOTOR_MAX, 0);
  }

  // Constrain speed output as safety fallback
  return constrain(mappedSpeed, -MOTOR_MAX, MOTOR_MAX);
}
