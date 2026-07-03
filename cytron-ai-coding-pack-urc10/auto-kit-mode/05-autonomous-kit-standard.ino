/*******************************************************************************
 * 05 — 1KG Autonomous Sumo Robot Starter Kit (Standard Code)
 * Cytron URC10 Sumo Robot Controller
 *
 * PURPOSE:
 * This is the standard autonomous sumo code for the 1KG Autonomous Sumo
 * Robot Starter Kit. It uses the kit's official pin layout and is the
 * recommended starting point for all autonomous kit users.
 *
 * START BUTTON PIN: A4
 * A4 is used because it matches the 1KG Autonomous Sumo Robot Starter Kit
 * assembly and wiring guide. If you wired the button to D13 (legacy Cytron
 * sample code) or D2 (some tutorial versions), change START_BUTTON_PIN below.
 *
 * SENSOR PINS (do not change — these are fixed by the kit assembly):
 *   EDGE_L     (D12) — Left Maker Reflect sensor  (edge/boundary detection)
 *   EDGE_R     (D11) — Right Maker Reflect sensor (edge/boundary detection)
 *   OPPONENT_L  (D3) — Side-Left Maker Object sensor (opponent detection)
 *   OPPONENT_R (D10) — Side-Right Maker Object sensor (opponent detection)
 *   OPPONENT_FR (A0) — Front-Right Maker Object sensor (opponent detection)
 *   OPPONENT_FC (A1) — Front-Center Maker Object sensor (opponent detection)
 *   OPPONENT_FL (A2) — Front-Left Maker Object sensor (opponent detection)
 *
 * MOTOR DRIVER PINS (internally wired on URC10 — do not change):
 *   Motor Left  (Motor 1): PWM = D5, DIR = D4
 *   Motor Right (Motor 2): PWM = D6, DIR = D7
 *   ⚠️ D4, D5, D6, D7 are RESERVED — never reassign them.
 *
 * ACTIVE-LOW SENSORS:
 * All sensors and the button use INPUT_PULLUP mode.
 *   - Not triggered = HIGH (1)
 *   - Triggered     = LOW  (0)
 * Detect a trigger with: digitalRead(PIN) == LOW
 *
 * TESTING STEPS:
 * -----------------------------------------------------------------------
 * Step 1: Run 01-motor-test.ino — confirm motor directions are correct.
 * Step 2: Run 02-sensor-test.ino — confirm all sensors trigger correctly.
 * Step 3: Upload this sketch.
 * Step 4: ** LIFT THE ROBOT WHEELS OFF THE GROUND **
 * Step 5: Press the Start button (A4). Release it. Match starts after delay.
 * Step 6: Wave hand in front of sensors, check robot steers toward it.
 * Step 7: Hold white paper under edge sensors, check robot reverses.
 * Step 8: Lower onto the ring only after all tests pass with wheels lifted.
 * -----------------------------------------------------------------------
 *
 * COMPETITION NOTE:
 * Most 1KG sumo competitions require a 5-second delay after the start signal.
 * Change delay(1000) to delay(5000) in setup() before competition.
 *
 * HARDWARE: Cytron URC10 + 1KG Autonomous Sumo Robot Starter Kit
 * BOARD:    Arduino Uno (select in Arduino IDE)
 * LIBRARY:  Cytron Motor Drivers Library
 *******************************************************************************/

/*
 * SAFETY — BEFORE RUNNING THIS CODE:
 * 1. Lift the robot wheels off the ground.
 * 2. Confirm motor directions are correct before placing on the floor.
 * 3. Start at low speed (e.g. setSpeed(100)) before testing at full speed.
 * 4. Never connect the battery with reversed polarity — it will permanently
 *    destroy the URC10 board.
 * 5. The front blade is SHARP — keep fingers away during testing.
 * See auto-kit-safety-rules.md for full guidance.
 */

#include <CytronMotorDriver.h>

// =============================================================================
// PIN DEFINITIONS
// =============================================================================

// --- LEDs (onboard, active-low) ---
#define LED0   0  // Onboard LED 0 (LOW = ON, HIGH = OFF). Also TX.
#define LED1   1  // Onboard LED 1 (LOW = ON, HIGH = OFF). Also RX.

// --- Start Button ---
//
// START_BUTTON_PIN = A4
// A4 is the standard for the 1KG Autonomous Sumo Robot Starter Kit wiring guide.
// If you wired the button to D13 (legacy Cytron sample code) or D2 (some tutorial
// versions), change the value below to match your actual wiring.
#define START_BUTTON_PIN  A4  // Start / emergency-stop button (active-low)

// --- Edge / Boundary Sensors (Maker Reflect) ---
// Installed on the underside of the chassis, facing the ring floor.
// LOW = white boundary line detected = edge of the ring.
#define EDGE_L  12  // Left edge sensor  (Maker Reflect — LEFT)
#define EDGE_R  11  // Right edge sensor (Maker Reflect — RIGHT)

// --- Opponent Sensors (Maker Object) ---
// Detect the opposing robot. LOW = opponent in range.
#define OPPONENT_L   3  // Side-Left opponent sensor  (Maker Object)
#define OPPONENT_R  10  // Side-Right opponent sensor (Maker Object)
#define OPPONENT_FR A0  // Front-Right opponent sensor (Maker Object)
#define OPPONENT_FC A1  // Front-Center opponent sensor (Maker Object)
#define OPPONENT_FL A2  // Front-Left opponent sensor (Maker Object)

// ⚠️ D4, D5, D6, D7 are RESERVED for the onboard motor driver.
//    Never use them for sensors, buttons, LEDs, or any other purpose.


// =============================================================================
// MOTOR OBJECTS
// =============================================================================
// Motor Left  (Motor 1): PWM = D5, Direction = D4
// Motor Right (Motor 2): PWM = D6, Direction = D7
CytronMD motorL(PWM_DIR, 5, 4);
CytronMD motorR(PWM_DIR, 6, 7);

// NOTE: "Forward" assumes default kit motor wiring.
// If a motor spins the wrong way, swap its two wires on the motor terminal.


// =============================================================================
// TUNING CONSTANTS
// =============================================================================
// Adjust these to tune robot performance.
// Use named constants — never use raw numbers in motor speed calls.
// Range: 0 (stopped) to 255 (full speed).

#define ATTACK_SPEED   200  // Speed during opponent attack charge
                            // Beginner tip: start at 100–120 for first tests
#define SEARCH_SPEED    90  // Speed during circular search rotation
#define BACKOFF_SPEED  160  // Speed when reversing away from the edge
#define BACKOFF_DELAY  300  // Time (ms) to reverse after edge detection
#define TURN_DELAY     380  // Time (ms) to turn after backoff
#define START_DELAY   1000  // Delay (ms) after button press before match starts
                            // Change to 5000 for competition (5-second rule)

// Search turn direction toggle — alternates each time an edge is detected.
bool searchClockwise = true;


// =============================================================================
// setup()
// Runs once on power-up. Configures all pins and waits for the Start button.
// =============================================================================
void setup() {

  // Configure button and sensor pins as INPUT_PULLUP.
  // Not triggered = HIGH. Triggered = LOW (active-low).
  pinMode(START_BUTTON_PIN, INPUT_PULLUP);
  pinMode(EDGE_L,           INPUT_PULLUP);
  pinMode(EDGE_R,           INPUT_PULLUP);
  pinMode(OPPONENT_L,       INPUT_PULLUP);
  pinMode(OPPONENT_R,       INPUT_PULLUP);
  pinMode(OPPONENT_FL,      INPUT_PULLUP);
  pinMode(OPPONENT_FC,      INPUT_PULLUP);
  pinMode(OPPONENT_FR,      INPUT_PULLUP);

  // Configure LED pins as outputs.
  pinMode(LED0, OUTPUT);
  pinMode(LED1, OUTPUT);

  // Start with both LEDs off (active-low: HIGH = OFF).
  digitalWrite(LED0, HIGH);
  digitalWrite(LED1, HIGH);

  // Stop both motors immediately on startup — safety first.
  motorL.setSpeed(0);
  motorR.setSpeed(0);

  // -------------------------------------------------------------------------
  // WAIT STATE: blink LED and wait for Start button press.
  // While waiting, LED1 mirrors the left edge sensor and
  // LED0 mirrors the right edge sensor — useful for checking sensor placement.
  // -------------------------------------------------------------------------
  while (digitalRead(START_BUTTON_PIN) == HIGH) {
    digitalWrite(LED1, digitalRead(EDGE_L));  // LOW = edge detected = LED on
    digitalWrite(LED0, digitalRead(EDGE_R));
  }

  // Wait for button to be fully released before starting.
  while (digitalRead(START_BUTTON_PIN) == LOW);

  // Both LEDs on = match starting.
  digitalWrite(LED0, LOW);
  digitalWrite(LED1, LOW);

  // -------------------------------------------------------------------------
  // START DELAY
  // Change to delay(5000) for competitions that require a 5-second delay.
  // -------------------------------------------------------------------------
  delay(START_DELAY);

  // Initial launch: brief forward surge, then enter main loop.
  motorL.setSpeed(ATTACK_SPEED);
  motorR.setSpeed(ATTACK_SPEED);
  delay(200);
}


// =============================================================================
// opponentDetected()
// Returns true if any opponent sensor reads LOW (object in range).
// =============================================================================
bool opponentDetected() {
  return (digitalRead(OPPONENT_FC) == LOW ||
          digitalRead(OPPONENT_FL) == LOW ||
          digitalRead(OPPONENT_FR) == LOW ||
          digitalRead(OPPONENT_L)  == LOW ||
          digitalRead(OPPONENT_R)  == LOW);
}


// =============================================================================
// loop()
// Main game loop. Priorities:
//   1. Edge detection   — always runs first, overrides everything else
//   2. Opponent attack  — charge at detected opponent
//   3. Search           — rotate slowly to scan for opponent
//   4. Emergency stop   — button halts the robot at any time
// =============================================================================
void loop() {

  // ===========================================================================
  // PRIORITY 1 — EDGE DETECTION
  // If the robot reaches the ring boundary, back off and turn immediately.
  // This must always run first to prevent the robot from driving off the ring.
  // ===========================================================================

  bool edgeLeft  = (digitalRead(EDGE_L) == LOW);
  bool edgeRight = (digitalRead(EDGE_R) == LOW);

  if (edgeLeft || edgeRight) {

    // Immediately stop, then reverse.
    motorL.setSpeed(0);
    motorR.setSpeed(0);
    delay(50);

    motorL.setSpeed(-BACKOFF_SPEED);
    motorR.setSpeed(-BACKOFF_SPEED);
    delay(BACKOFF_DELAY);

    // Turn away from the detected edge.
    // Left edge → turn right. Right edge → turn left. Both → alternate.
    if (edgeLeft && !edgeRight) {
      // Turn right (clockwise).
      motorL.setSpeed(BACKOFF_SPEED);
      motorR.setSpeed(-BACKOFF_SPEED);
    } else if (edgeRight && !edgeLeft) {
      // Turn left (counter-clockwise).
      motorL.setSpeed(-BACKOFF_SPEED);
      motorR.setSpeed(BACKOFF_SPEED);
    } else {
      // Both edges: alternate turn direction each time.
      if (searchClockwise) {
        motorL.setSpeed(BACKOFF_SPEED);
        motorR.setSpeed(-BACKOFF_SPEED);
      } else {
        motorL.setSpeed(-BACKOFF_SPEED);
        motorR.setSpeed(BACKOFF_SPEED);
      }
      searchClockwise = !searchClockwise;
    }
    delay(TURN_DELAY);

    motorL.setSpeed(0);
    motorR.setSpeed(0);
    delay(50);

    return;  // Restart loop from the top immediately after backoff.
  }

  // ===========================================================================
  // PRIORITY 2 — ATTACK
  // Steer toward the opponent based on which sensor(s) are triggered.
  // ===========================================================================

  if (digitalRead(OPPONENT_FC) == LOW) {
    // Opponent directly ahead — charge straight.
    motorL.setSpeed(ATTACK_SPEED);
    motorR.setSpeed(ATTACK_SPEED);
  }
  else if (digitalRead(OPPONENT_FL) == LOW) {
    // Opponent front-left — curve left.
    motorL.setSpeed(ATTACK_SPEED / 2);
    motorR.setSpeed(ATTACK_SPEED);
  }
  else if (digitalRead(OPPONENT_FR) == LOW) {
    // Opponent front-right — curve right.
    motorL.setSpeed(ATTACK_SPEED);
    motorR.setSpeed(ATTACK_SPEED / 2);
  }
  else if (digitalRead(OPPONENT_L) == LOW) {
    // Opponent on side-left — spin left to face.
    motorL.setSpeed(-SEARCH_SPEED);
    motorR.setSpeed(SEARCH_SPEED);
  }
  else if (digitalRead(OPPONENT_R) == LOW) {
    // Opponent on side-right — spin right to face.
    motorL.setSpeed(SEARCH_SPEED);
    motorR.setSpeed(-SEARCH_SPEED);
  }

  // ===========================================================================
  // PRIORITY 3 — SEARCH
  // No opponent detected — rotate slowly to scan the ring.
  // ===========================================================================

  else {
    // Circular arc search. Alternates direction after each edge backoff.
    if (searchClockwise) {
      motorL.setSpeed(SEARCH_SPEED);
      motorR.setSpeed(SEARCH_SPEED / 2);
    } else {
      motorL.setSpeed(SEARCH_SPEED / 2);
      motorR.setSpeed(SEARCH_SPEED);
    }
  }

  // ===========================================================================
  // PRIORITY 4 — EMERGENCY STOP
  // If Start button is pressed during the match, stop and halt immediately.
  // ===========================================================================

  if (digitalRead(START_BUTTON_PIN) == LOW) {
    motorL.setSpeed(0);
    motorR.setSpeed(0);
    digitalWrite(LED0, HIGH);  // LEDs off
    digitalWrite(LED1, HIGH);
    while (1);  // Halt — press reset or upload new code to restart.
  }
}
