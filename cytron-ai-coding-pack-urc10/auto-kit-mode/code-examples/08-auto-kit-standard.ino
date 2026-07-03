/*******************************************************************************
 * 08 — Auto Kit Standard Code (IR Sumo Start Edition)
 * 1KG Autonomous Sumo Robot Starter Kit using URC10
 *
 * Derived from the original Cytron URC10SumoRobot.ino sample.
 * Cleaned, standardized, and updated for IR Sumo Start module.
 *
 * ---------------------------------------------------------------------------
 * START SIGNAL: IR Sumo Start Module on D2
 *
 *   IR Sumo Start REPLACES the physical start button.
 *   The module receives an IR signal from the judge's remote control and
 *   outputs a digital level that this code reads on D2:
 *
 *     Signal HIGH = RUN        → robot is permitted to move
 *     Signal LOW  = READY/STOP → robot must stay stopped immediately
 *
 *   ⚠️  If the signal goes LOW while the robot is running, motors stop
 *       immediately. This is a competition safety requirement.
 *
 * ---------------------------------------------------------------------------
 * WIRING — IR Sumo Start Module to URC10:
 *   IR Sumo Start (+) → URC10 5V
 *   IR Sumo Start (-) → URC10 GND
 *   IR Sumo Start (S) → URC10 D2
 *
 * IR SIGNAL PIN MODE: INPUT (not INPUT_PULLUP)
 *   The module provides a driven digital output. Do not add a pullup —
 *   it would interfere with the driven output.
 *
 * ---------------------------------------------------------------------------
 * D2 PIN USAGE NOTE — MODE-SPECIFIC:
 *   Auto Kit Mode  : D2 = IR Sumo Start signal input   (this file)
 *   RC Mode        : D2 = RC throttle pulse input       (06-radio-controlled-drive.ino)
 *   Hybrid Mode    : Confirm pin mapping with user before generating final code
 *   These modes are mutually exclusive — do not mix pin roles.
 *
 * ---------------------------------------------------------------------------
 * SENSOR WIRING:
 *   All sensors (edge + opponent) use INPUT_PULLUP.
 *   Not triggered = HIGH. Triggered (active) = LOW.
 *
 * MOTOR PINS (fixed on URC10 board — do not change):
 *   Motor Left  (M1): PWM = D5, DIR = D4
 *   Motor Right (M2): PWM = D6, DIR = D7
 *   ⚠️  D4, D5, D6, D7 are RESERVED. Never use them for sensors or modules.
 *   Motor direction depends on how wires are connected to the terminal.
 *   If a motor spins the wrong way, swap its two wires on the terminal block.
 *
 * ---------------------------------------------------------------------------
 * BEFORE FIRST TEST:
 *   1. ⚠️  Check battery polarity before connecting. Reversed polarity
 *          permanently destroys the URC10 board.
 *   2. ⚠️  Lift the robot wheels off the ground before sending the RUN signal.
 *          Motors will spin immediately once RUN is received.
 *   3. Run 01-motor-test.ino first to confirm motor directions.
 *   4. Run 02-sensor-test.ino to confirm all sensors trigger correctly.
 *   5. Run 09-ir-sumo-start-test.ino to confirm D2 reads HIGH on RUN and LOW
 *      on STOP before running this full match code.
 *   6. Start at low speed (ATTACK_SPEED 150) before increasing to 200–255.
 *
 * HARDWARE: Cytron URC10 + 1KG Autonomous Sumo Robot Starter Kit
 *           + Cytron IR Sumo Start Module (IR-SUMO-START)
 * BOARD:    Arduino Uno (select in Arduino IDE)
 * LIBRARY:  Cytron Motor Drivers Library
 * PRODUCT:  https://my.cytron.io/p-ir-sumo-start-module
 *******************************************************************************/

#include <CytronMotorDriver.h>


// =============================================================================
// PIN DEFINITIONS
// =============================================================================

// Onboard LEDs (active-low: LOW = ON, HIGH = OFF)
// D0 = TX, D1 = RX — do not use Serial.begin() while these LEDs are in use.
const uint8_t LED0_PIN = 0;
const uint8_t LED1_PIN = 1;

// IR Sumo Start Module — Auto Kit Mode signal input
// D2 = IR Sumo Start in Auto Kit Mode. (In RC Mode, D2 is used for RC throttle.)
// The module actively drives D2. Use INPUT — do NOT use INPUT_PULLUP.
//   HIGH = RUN  (judge sends start, match is active)
//   LOW  = READY / STOP (judge sends stop, or no signal received)
const uint8_t IR_SUMO_START_PIN = 2;

// Edge sensors (Maker Reflect) — mounted on the underside of the chassis
// Active-low: LOW = white boundary line detected = edge of the ring.
const uint8_t EDGE_LEFT_PIN  = 12;
const uint8_t EDGE_RIGHT_PIN = 11;

// Opponent sensors (Maker Object) — detect the opposing robot
// Active-low: LOW = opponent detected within range.
const uint8_t OPPONENT_SIDE_LEFT_PIN    =  3;
const uint8_t OPPONENT_SIDE_RIGHT_PIN   = 10;
const uint8_t OPPONENT_FRONT_RIGHT_PIN  = A0;
const uint8_t OPPONENT_FRONT_CENTER_PIN = A1;
const uint8_t OPPONENT_FRONT_LEFT_PIN   = A2;

// ⚠️  D4, D5, D6, D7 are RESERVED for the onboard motor driver.
// Never assign any sensor, module, or LED to these pins.


// =============================================================================
// MOTOR DRIVER
// =============================================================================
// Motor Left  (M1): PWM = D5, Direction = D4
// Motor Right (M2): PWM = D6, Direction = D7
//
// setSpeed() range: -255 (full reverse) to +255 (full forward).
// "Forward" means robot moves toward the front blade.
// If a wheel spins the wrong direction, swap its two motor wires on the terminal.
CytronMD motorL(PWM_DIR, 5, 4);
CytronMD motorR(PWM_DIR, 6, 7);


// =============================================================================
// TUNING CONSTANTS
// =============================================================================
// Adjust these values to tune robot performance.
// ⚠️  Always test with wheels lifted first whenever you change a speed value.

// Search: slow circular rotation to scan for opponent
const int SEARCH_SPEED = 90;

// Attack: speed when charging at the detected opponent.
// Tip: start at 150 for your first test. Increase to 200–255 once you confirm
// the robot behaves correctly on the ring.
const int ATTACK_SPEED = 200;

// Turn: speed when spinning to face a side-detected opponent
const int TURN_SPEED = 140;

// Back-off: reverse speed when an edge is detected
const int BACKOFF_SPEED = 180;

// Timings (milliseconds)
const uint32_t START_DELAY_MS       = 1000; // Delay after RUN before first move.
                                             // Change to 5000 for competitions.
const uint32_t BACKOFF_DELAY_MS     =  200; // How long to reverse after edge
const uint32_t BACKOFF_STOP_MS      =   80; // Brief stop between backoff moves
const uint32_t TURN_TIMEOUT_MS      =  300; // Max spin time during backoff turn
const uint32_t SIDE_TURN_TIMEOUT_MS =  400; // Max spin when acquiring side target


// =============================================================================
// STATE
// =============================================================================
// searchDir alternates each time an edge event fires so the robot does not
// always circle in the same direction.
const uint8_t SEARCH_LEFT  = 0;
const uint8_t SEARCH_RIGHT = 1;
uint8_t searchDir = SEARCH_LEFT;


// =============================================================================
// HELPER: stopMotors()
// Immediately stops both drive motors.
// Call this before every direction change, delay, and on any STOP signal.
// =============================================================================
void stopMotors() {
  motorL.setSpeed(0);
  motorR.setSpeed(0);
}


// =============================================================================
// HELPER: irRunSignalActive()
// Returns true when the IR Sumo Start module outputs a RUN signal (HIGH).
// Returns false when the module outputs READY / STOP (LOW).
//
//   HIGH → true  → robot is permitted to move
//   LOW  → false → robot must stop immediately
// =============================================================================
bool irRunSignalActive() {
  return digitalRead(IR_SUMO_START_PIN) == HIGH;
}


// =============================================================================
// HELPER: edgeLeftDetected()
// Returns true when the left Maker Reflect sensor sees the white edge line.
// Sensor is active-low (INPUT_PULLUP): LOW = triggered.
// =============================================================================
bool edgeLeftDetected() {
  return digitalRead(EDGE_LEFT_PIN) == LOW;
}


// =============================================================================
// HELPER: edgeRightDetected()
// Returns true when the right Maker Reflect sensor sees the white edge line.
// =============================================================================
bool edgeRightDetected() {
  return digitalRead(EDGE_RIGHT_PIN) == LOW;
}


// =============================================================================
// HELPER: anyOpponentDetected()
// Returns true when any of the five Maker Object sensors sees the opponent.
// Sensors are active-low (INPUT_PULLUP): LOW = triggered.
// =============================================================================
bool anyOpponentDetected() {
  return (
    digitalRead(OPPONENT_FRONT_CENTER_PIN) == LOW ||
    digitalRead(OPPONENT_FRONT_LEFT_PIN)   == LOW ||
    digitalRead(OPPONENT_FRONT_RIGHT_PIN)  == LOW ||
    digitalRead(OPPONENT_SIDE_LEFT_PIN)    == LOW ||
    digitalRead(OPPONENT_SIDE_RIGHT_PIN)   == LOW
  );
}


// =============================================================================
// FUNCTION: checkIRStopSignal()
// Checks whether the IR Sumo Start module has sent a STOP signal (LOW).
// If STOP is received, motors halt immediately and stay stopped until reset.
//
// ⚠️  Call this at the TOP of loop() on every iteration.
//     It is a competition safety requirement. Do not remove or bypass it.
// =============================================================================
void checkIRStopSignal() {
  if (!irRunSignalActive()) {
    // STOP signal received from judge — halt immediately.
    stopMotors();
    digitalWrite(LED0_PIN, HIGH);  // Both LEDs off.
    digitalWrite(LED1_PIN, HIGH);

    // Keep robot stopped until reset.
    // Press the reset button or upload new code to restart.
    while (true) {
      // STOP signal active — robot stays stopped.
    }
  }
}


// =============================================================================
// FUNCTION: waitForIRStartSignal()
// Stops motors and blocks until the IR Sumo Start module sends RUN (HIGH).
// While waiting, LED1 mirrors the left edge sensor and LED0 mirrors the right
// edge sensor — useful for checking sensor placement before the match.
// =============================================================================
void waitForIRStartSignal() {
  stopMotors();

  // Wait for IR Sumo Start to output HIGH (RUN).
  // Signal is driven by the module — no pullup needed on D2.
  while (!irRunSignalActive()) {
    // Waiting for RUN signal from IR Sumo Start.
    // READY and STOP states are LOW — robot stays stopped.

    // Mirror edge sensor state on LEDs during the wait.
    // Active-low: sensor LOW → LED LOW → LED ON.
    // D0/D1 are also TX/RX — do not use Serial.begin() with this code.
    digitalWrite(LED1_PIN, digitalRead(EDGE_LEFT_PIN));   // LOW = edge = LED on
    digitalWrite(LED0_PIN, digitalRead(EDGE_RIGHT_PIN));  // LOW = edge = LED on
  }
}


// =============================================================================
// FUNCTION: startRoutine()
// Runs once immediately after the RUN signal is received.
// Performs the start delay, then an opening move before the main loop.
//
// Opening move: sweep right ~45°, surge forward, then sweep left while
// watching for the opponent front-center sensor.
// =============================================================================
void startRoutine() {

  // Start delay — required by most competition rules.
  // Change START_DELAY_MS to 5000 for a 5-second competition delay.
  delay(START_DELAY_MS);

  // Sweep right ~45 degrees to clear the starting zone.
  motorL.setSpeed(ATTACK_SPEED);
  motorR.setSpeed(0);
  delay(180);

  // Surge straight forward into the ring.
  motorL.setSpeed(ATTACK_SPEED);
  motorR.setSpeed(ATTACK_SPEED);
  delay(450);

  // Sweep left while watching for the front-center opponent sensor.
  motorL.setSpeed(0);
  motorR.setSpeed(ATTACK_SPEED);
  uint32_t sweepStart = millis();
  while (digitalRead(OPPONENT_FRONT_CENTER_PIN) == HIGH) {
    if (millis() - sweepStart > SIDE_TURN_TIMEOUT_MS) break;
  }
}


// =============================================================================
// FUNCTION: searchOpponent()
// Moves in a slow circular arc to scan the ring when no opponent is visible.
// Direction alternates each time handleEdge() is called.
// =============================================================================
void searchOpponent() {
  if (searchDir == SEARCH_LEFT) {
    motorL.setSpeed(SEARCH_SPEED);
    motorR.setSpeed(SEARCH_SPEED * 2);
  } else {
    motorL.setSpeed(SEARCH_SPEED * 2);
    motorR.setSpeed(SEARCH_SPEED);
  }
}


// =============================================================================
// FUNCTION: attackOpponent()
// Tracks and charges at the detected opponent. Checks front sensors first,
// then side sensors. Safe to call when no sensor is triggered.
// =============================================================================
void attackOpponent() {

  uint32_t attackStart = millis();

  if (digitalRead(OPPONENT_FRONT_CENTER_PIN) == LOW) {
    // Front center — charge straight forward.
    motorL.setSpeed(ATTACK_SPEED);
    motorR.setSpeed(ATTACK_SPEED);
  }
  else if (digitalRead(OPPONENT_FRONT_LEFT_PIN) == LOW) {
    // Front left — curve left toward opponent.
    motorL.setSpeed(0);
    motorR.setSpeed(ATTACK_SPEED);
  }
  else if (digitalRead(OPPONENT_FRONT_RIGHT_PIN) == LOW) {
    // Front right — curve right toward opponent.
    motorL.setSpeed(ATTACK_SPEED);
    motorR.setSpeed(0);
  }
  else if (digitalRead(OPPONENT_SIDE_LEFT_PIN) == LOW) {
    // Side left — spin left until opponent appears at front center.
    motorL.setSpeed(-TURN_SPEED);
    motorR.setSpeed(TURN_SPEED);
    while (digitalRead(OPPONENT_FRONT_CENTER_PIN) == HIGH) {
      if (millis() - attackStart > SIDE_TURN_TIMEOUT_MS) break;
    }
  }
  else if (digitalRead(OPPONENT_SIDE_RIGHT_PIN) == LOW) {
    // Side right — spin right until opponent appears at front center.
    motorL.setSpeed(TURN_SPEED);
    motorR.setSpeed(-TURN_SPEED);
    while (digitalRead(OPPONENT_FRONT_CENTER_PIN) == HIGH) {
      if (millis() - attackStart > SIDE_TURN_TIMEOUT_MS) break;
    }
  }
}


// =============================================================================
// FUNCTION: handleEdge(dir)
// Called when a ring boundary is detected.
// Reverses away from the edge, turns to face the ring, then optionally surges.
//
// Parameters:
//   dir — SEARCH_LEFT or SEARCH_RIGHT: which way to turn after reversing
// =============================================================================
void handleEdge(uint8_t dir) {

  stopMotors();
  delay(BACKOFF_STOP_MS);

  motorL.setSpeed(-BACKOFF_SPEED);
  motorR.setSpeed(-BACKOFF_SPEED);
  delay(BACKOFF_DELAY_MS);

  stopMotors();
  delay(BACKOFF_STOP_MS);

  // Turn away from the edge. Exit early if opponent spotted during turn.
  if (dir == SEARCH_LEFT) {
    motorL.setSpeed(-TURN_SPEED);
    motorR.setSpeed(TURN_SPEED);
  } else {
    motorL.setSpeed(TURN_SPEED);
    motorR.setSpeed(-TURN_SPEED);
  }

  uint32_t turnStart = millis();
  while (millis() - turnStart < TURN_TIMEOUT_MS) {
    if (digitalRead(OPPONENT_FRONT_CENTER_PIN) == LOW ||
        digitalRead(OPPONENT_FRONT_LEFT_PIN)   == LOW ||
        digitalRead(OPPONENT_FRONT_RIGHT_PIN)  == LOW ||
        digitalRead(OPPONENT_SIDE_LEFT_PIN)    == LOW ||
        digitalRead(OPPONENT_SIDE_RIGHT_PIN)   == LOW) {
      stopMotors();
      delay(BACKOFF_STOP_MS);
      return;
    }
  }

  // No opponent during turn — surge forward briefly.
  motorL.setSpeed(ATTACK_SPEED);
  motorR.setSpeed(ATTACK_SPEED);
  delay(200);
}


// =============================================================================
// FUNCTION: setupPins()
// Configures all input and output pins.
// Called once at the start of setup().
// =============================================================================
void setupPins() {

  // IR Sumo Start: INPUT — the module drives D2 actively. No pullup needed.
  // ⚠️  Auto Kit Mode only. In RC Mode, D2 is used for RC throttle.
  pinMode(IR_SUMO_START_PIN, INPUT);

  // Edge and opponent sensors: INPUT_PULLUP — active-low (triggered = LOW).
  pinMode(EDGE_LEFT_PIN,             INPUT_PULLUP);
  pinMode(EDGE_RIGHT_PIN,            INPUT_PULLUP);
  pinMode(OPPONENT_SIDE_LEFT_PIN,    INPUT_PULLUP);
  pinMode(OPPONENT_SIDE_RIGHT_PIN,   INPUT_PULLUP);
  pinMode(OPPONENT_FRONT_LEFT_PIN,   INPUT_PULLUP);
  pinMode(OPPONENT_FRONT_CENTER_PIN, INPUT_PULLUP);
  pinMode(OPPONENT_FRONT_RIGHT_PIN,  INPUT_PULLUP);

  // Onboard LEDs: active-low outputs (LOW = ON, HIGH = OFF).
  // D0/D1 are also TX/RX — do not call Serial.begin() with this code.
  pinMode(LED0_PIN, OUTPUT);
  pinMode(LED1_PIN, OUTPUT);
  digitalWrite(LED0_PIN, HIGH);  // Start with both LEDs off.
  digitalWrite(LED1_PIN, HIGH);
}


// =============================================================================
// FUNCTION: setup()
// Runs once on power-up or reset.
// =============================================================================
void setup() {
  setupPins();
  stopMotors();

  // Wait for IR Sumo Start to send RUN signal (HIGH).
  // Robot stays completely still until RUN is received.
  waitForIRStartSignal();

  // Both LEDs on = RUN received, match is starting.
  digitalWrite(LED0_PIN, LOW);
  digitalWrite(LED1_PIN, LOW);

  // Run the opening sequence before entering the main loop.
  startRoutine();
}


// =============================================================================
// FUNCTION: loop()
// Main game loop — runs continuously after setup().
//
// Priority order:
//   0. IR STOP check — motors halt immediately if signal goes LOW
//   1. Edge detection — prevents driving off the ring
//   2. Opponent detection — attack if in view, search if not
// =============================================================================
void loop() {

  // Priority 0 — STOP signal check (highest priority).
  // If signal is LOW, checkIRStopSignal() stops motors and halts forever.
  // ⚠️  Do not remove or move this check.
  checkIRStopSignal();

  // Priority 1 — Edge detection.
  if (edgeLeftDetected()) {
    handleEdge(SEARCH_RIGHT);   // Left edge: turn right to face ring
    searchDir ^= 1;             // Alternate search direction
  }
  else if (edgeRightDetected()) {
    handleEdge(SEARCH_LEFT);    // Right edge: turn left to face ring
    searchDir ^= 1;
  }

  // Priority 2 — Opponent detection.
  else if (anyOpponentDetected()) {
    attackOpponent();
  }
  else {
    searchOpponent();
  }
}
