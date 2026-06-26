/*******************************************************************************
 * 07 — Hybrid RC and Autonomous Mode
 * Cytron URC10 Sumo Robot Controller (RC Path)
 *
 * PURPOSE:
 * Implements mode switching using a toggle switch on pin A3 (digital input).
 * - Switch ON (LOW): Radio Controlled manual drive via Throttle (D2) & Steering (D3)
 * - Switch OFF (HIGH): Simplified autonomous edge-avoidance behavior using
 *   the edge sensors EDGE_L (D12) and EDGE_R (D11).
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
 * - Mode Switch Input: A3 (INPUT_PULLUP, LOW = RC Mode, HIGH = Autonomous Mode)
 * - Left Floor/Edge Sensor: D12 (INPUT_PULLUP, active-low)
 * - Right Floor/Edge Sensor: D11 (INPUT_PULLUP, active-low)
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
#define THROTTLE_PIN   2   // RC Throttle input
#define STEERING_PIN   3   // RC Steering input
#define MODE_SWITCH    A3  // Switch to toggle modes (INPUT_PULLUP)
#define EDGE_L_PIN     12  // Left floor/edge sensor (active-low)
#define EDGE_R_PIN     11  // Right floor/edge sensor (active-low)
#define SERIAL_BAUD    9600
#define PULSE_TIMEOUT  25000

// --- RC Calibration Constants ---
#define RC_MIN         1000
#define RC_NEUTRAL     1500
#define RC_MAX         2000
#define RC_DEADBAND    50
#define MOTOR_MAX      255
#define SAFE_MIN       900
#define SAFE_MAX       2100

// --- Autonomous Speed Constants ---
#define AUTO_DRIVE_SPEED 120  // Slow, safe speed for autonomous roaming
#define AUTO_TURN_SPEED  150  // Speed used during edge turn recovery
#define AUTO_REVERSE_MS  600  // Duration in milliseconds to reverse away from edge
#define AUTO_TURN_MS     500  // Duration in milliseconds to turn away from edge

// --- Motor Objects ---
CytronMD motorL(PWM_DIR, 5, 4);
CytronMD motorR(PWM_DIR, 6, 7);

// Declare function prototypes
int mapRcChannel(unsigned long pulse, int deadband);
void runRcMode();
void runAutonomousMode();

/*******************************************************************************
 * setup()
 * Runs once on power-up. Configures inputs, stops motors, and starts Serial.
 *******************************************************************************/
void setup() {
  // Config RC pins and mode switch
  pinMode(THROTTLE_PIN, INPUT);
  pinMode(STEERING_PIN, INPUT);
  pinMode(MODE_SWITCH,  INPUT_PULLUP);

  // Config edge sensor pins
  pinMode(EDGE_L_PIN, INPUT_PULLUP);
  pinMode(EDGE_R_PIN, INPUT_PULLUP);

  // Stop both motors immediately — safety first.
  motorL.setSpeed(0);
  motorR.setSpeed(0);

  // Start Serial for monitoring mode transitions
  Serial.begin(SERIAL_BAUD);
  Serial.println("--- Cytron URC10 Hybrid RC/Auto Mode ---");
  Serial.println("A3 Switch LOW (Closed) = RC Mode");
  Serial.println("A3 Switch HIGH (Open)  = Autonomous Mode");
}

/*******************************************************************************
 * loop()
 * Checks mode switch on A3 and runs the corresponding behavior function.
 *******************************************************************************/
void loop() {
  // Read mode switch (A3). Since it has an internal pullup:
  // - If connected to GND (switch closed): reads LOW.
  // - If disconnected (switch open): reads HIGH.
  if (digitalRead(MODE_SWITCH) == LOW) {
    runRcMode();
  } else {
    runAutonomousMode();
  }
}

/*******************************************************************************
 * runRcMode()
 * Executes standard RC drive logic with arcade mixing and failsafe.
 *******************************************************************************/
void runRcMode() {
  unsigned long throttlePulse = pulseIn(THROTTLE_PIN, HIGH, PULSE_TIMEOUT);
  unsigned long steeringPulse = pulseIn(STEERING_PIN, HIGH, PULSE_TIMEOUT);

  // Signal-loss Failsafe
  if (throttlePulse == 0 || steeringPulse == 0 ||
      throttlePulse < SAFE_MIN || throttlePulse > SAFE_MAX ||
      steeringPulse < SAFE_MIN || steeringPulse > SAFE_MAX) {
    motorL.setSpeed(0);
    motorR.setSpeed(0);
    Serial.println("[RC Mode] WARNING: Signal lost! Motors halted.");
    delay(100);
    return;
  }

  // Parse pulse widths with deadband
  int throttleSpeed = mapRcChannel(throttlePulse, RC_DEADBAND);
  int steeringSpeed = mapRcChannel(steeringPulse, RC_DEADBAND);

  // Arcade mixing
  int leftMotorSpeed = throttleSpeed + steeringSpeed;
  int rightMotorSpeed = throttleSpeed - steeringSpeed;

  // Constrain limits
  leftMotorSpeed = constrain(leftMotorSpeed, -MOTOR_MAX, MOTOR_MAX);
  rightMotorSpeed = constrain(rightMotorSpeed, -MOTOR_MAX, MOTOR_MAX);

  // Drive motors
  motorL.setSpeed(leftMotorSpeed);
  motorR.setSpeed(rightMotorSpeed);

  Serial.print("[RC Mode] Left: ");
  Serial.print(leftMotorSpeed);
  Serial.print(" | Right: ");
  Serial.println(rightMotorSpeed);
  
  delay(20);
}

/*******************************************************************************
 * runAutonomousMode()
 * Runs simplified edge-avoidance behavior.
 * Drives forward until an edge is detected, then backs up and turns.
 *******************************************************************************/
void runAutonomousMode() {
  // Read edge sensors (INPUT_PULLUP, active-low: LOW = white edge detected)
  bool edgeLeft = (digitalRead(EDGE_L_PIN) == LOW);
  bool edgeRight = (digitalRead(EDGE_R_PIN) == LOW);

  // -----------------------------------------------------------------------
  // Edge Detection Actions:
  // If either edge sensor is triggered, the robot must back up and turn away.
  // -----------------------------------------------------------------------
  if (edgeLeft) {
    Serial.println("[Auto Mode] Edge Left detected! Backing up and turning right...");
    
    // Step 1: Stop and reverse
    motorL.setSpeed(-AUTO_DRIVE_SPEED);
    motorR.setSpeed(-AUTO_DRIVE_SPEED);
    delay(AUTO_REVERSE_MS);

    // Step 2: Spin turn right
    motorL.setSpeed(AUTO_TURN_SPEED);
    motorR.setSpeed(-AUTO_TURN_SPEED);
    delay(AUTO_TURN_MS);

    // Step 3: Stop
    motorL.setSpeed(0);
    motorR.setSpeed(0);
    
  } else if (edgeRight) {
    Serial.println("[Auto Mode] Edge Right detected! Backing up and turning left...");

    // Step 1: Stop and reverse
    motorL.setSpeed(-AUTO_DRIVE_SPEED);
    motorR.setSpeed(-AUTO_DRIVE_SPEED);
    delay(AUTO_REVERSE_MS);

    // Step 2: Spin turn left
    motorL.setSpeed(-AUTO_TURN_SPEED);
    motorR.setSpeed(AUTO_TURN_SPEED);
    delay(AUTO_TURN_MS);

    // Step 3: Stop
    motorL.setSpeed(0);
    motorR.setSpeed(0);
    
  } else {
    // No edge detected: drive forward slowly
    motorL.setSpeed(AUTO_DRIVE_SPEED);
    motorR.setSpeed(AUTO_DRIVE_SPEED);
    
    Serial.println("[Auto Mode] Roaming forward...");
    delay(50); // Small delay to prevent polling overload
  }
}

/*******************************************************************************
 * mapRcChannel(unsigned long pulse, int deadband)
 * Maps an RC pulse width (1000 - 2000 us) to motor speed (-255 to 255).
 * Applies a deadband around the center (1500 us). Returns 0 if in deadband.
 *******************************************************************************/
int mapRcChannel(unsigned long pulse, int deadband) {
  if (pulse == 0) return 0;
  
  long deviation = (long)pulse - RC_NEUTRAL;

  if (abs(deviation) < deadband) {
    return 0;
  }

  int mappedSpeed;
  if (deviation > 0) {
    mappedSpeed = map(pulse, RC_NEUTRAL + deadband, RC_MAX, 0, MOTOR_MAX);
  } else {
    mappedSpeed = map(pulse, RC_MIN, RC_NEUTRAL - deadband, -MOTOR_MAX, 0);
  }

  return constrain(mappedSpeed, -MOTOR_MAX, MOTOR_MAX);
}
