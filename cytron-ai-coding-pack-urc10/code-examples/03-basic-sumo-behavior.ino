/*******************************************************************************
 * 03 — Basic Sumo Behaviour (Beginner Version)
 * Cytron URC10 Sumo Robot Controller
 *
 * ⚠️ SIMPLIFIED BEGINNER EXAMPLE
 * This is a simplified beginner example. It does not use every sensor from
 * the original sample code. Specifically, the two side opponent sensors
 * (OPPONENT_L on D3 and OPPONENT_R on D10) are intentionally omitted to
 * keep the logic easy to read and understand.
 * To add side sensor support later, see project-ideas.md (Idea 2 — Smarter
 * Search Strategy) and build-application-prompt.md.
 *
 * PURPOSE:
 * A simplified sumo robot sketch designed for beginners.
 * This is intentionally simpler than the original sample code —
 * it uses straight-line logic with no complex sub-functions,
 * so every step is easy to read and understand.
 *
 * TESTING STEPS:
 * -----------------------------------------------------------------------
 * Step 1: Run 01-motor-test.ino first — confirm motor directions are correct.
 * Step 2: Run 02-sensor-test.ino — confirm all sensors trigger correctly.
 * Step 3: Upload this sketch.
 * Step 4: Place the robot on the sumo ring with WHEELS LIFTED OFF THE GROUND.
 * Step 5: Press the Start button. Release it. The robot will wait 1 second.
 * Step 6: Confirm wheels spin at the expected speed before lowering.
 * Step 7: Lower the robot gently onto the ring and test the behaviour.
 * -----------------------------------------------------------------------
 *
 * FIRST TESTING TIP:
 * Start with ATTACK_SPEED set to 100 or 120 for your very first test.
 * This gives you time to confirm the robot behaves correctly before
 * increasing speed. You can increase to 150 or higher once you are happy
 * with the direction and sensor response.
 *
 * BEHAVIOUR (simplified, beginner-friendly):
 * 1. Wait for Start button press.
 * 2. Delay 1 second (change to 5000 for competition — see note below).
 * 3. Loop forever:
 *    A. Edge detected (left or right) → stop → reverse → turn away.
 *    B. Opponent detected (any front sensor) → drive forward to attack.
 *    C. No edge, no opponent → search slowly in a circular arc.
 *    D. Button pressed during match → stop immediately.
 *
 * COMPETITION NOTE:
 * Most sumo competitions require a 5-second delay after the start signal.
 * Change the number in: delay(1000);   ← in setup() below
 * To:                   delay(5000);   ← for competition
 *
 * HARDWARE: Cytron URC10 Sumo Robot Controller
 * BOARD:    Arduino Uno (select in Arduino IDE)
 * LIBRARY:  Cytron Motor Drivers Library
 *******************************************************************************/

#include <CytronMotorDriver.h>

// --- Pin Definitions ---
#define LED0        0   // Onboard LED 0 (active-low: LOW = ON)
#define LED1        1   // Onboard LED 1 (active-low: LOW = ON)
#define BUTTON      13  // Start / stop button (active-low: LOW = pressed)
#define EDGE_L      12  // Left edge sensor   (active-low: LOW = edge detected)
#define EDGE_R      11  // Right edge sensor  (active-low: LOW = edge detected)
#define OPPONENT_FR A0  // Front-right opponent sensor (active-low)
#define OPPONENT_FC A1  // Front-center opponent sensor (active-low)
#define OPPONENT_FL A2  // Front-left opponent sensor (active-low)

// ⚠️ D4, D5, D6, D7 are reserved for the motor driver — DO NOT use them
//    for sensors, LEDs, or any other purpose.

// --- Motor Objects ---
// Motor Left  (Motor 1): PWM = D5, Direction = D4
// Motor Right (Motor 2): PWM = D6, Direction = D7
CytronMD motorL(PWM_DIR, 5, 4);
CytronMD motorR(PWM_DIR, 6, 7);

// --- Speed Settings ---
// Adjust these values to tune your robot's behaviour.
// Range: 0 (stopped) to 255 (full speed).
//
// BEGINNER TIP: Start your first test with ATTACK_SPEED at 100 or 120.
// Increase to 150 once you confirm correct direction and sensor response.
// For competition tuning, experienced users may increase up to 200–255,
// but always test with wheels lifted first at any new speed value.
#define ATTACK_SPEED  150  // Beginner-safe attack speed (advanced: up to 200–255)
#define SEARCH_SPEED  120  // Speed during circular search
#define REVERSE_SPEED 180  // Speed when reversing away from edge


/*******************************************************************************
 * setup()
 * Runs once on power-up. Configures all pins and waits for the Start button.
 *******************************************************************************/
void setup() {
  // Configure all sensor and button pins.
  // INPUT_PULLUP means: not triggered = HIGH, triggered = LOW.
  pinMode(BUTTON,      INPUT_PULLUP);
  pinMode(EDGE_L,      INPUT_PULLUP);
  pinMode(EDGE_R,      INPUT_PULLUP);
  pinMode(OPPONENT_FL, INPUT_PULLUP);
  pinMode(OPPONENT_FC, INPUT_PULLUP);
  pinMode(OPPONENT_FR, INPUT_PULLUP);

  // Configure LED pins as outputs.
  pinMode(LED0, OUTPUT);
  pinMode(LED1, OUTPUT);

  // Turn both LEDs off on startup (active-low: HIGH = OFF).
  digitalWrite(LED0, HIGH);
  digitalWrite(LED1, HIGH);

  // Stop both motors before anything else.
  motorL.setSpeed(0);
  motorR.setSpeed(0);

  // --- Wait for Start Button ---
  // The robot will not move until the button is pressed.
  // While waiting, LED1 mirrors the LEFT edge sensor
  // and LED0 mirrors the RIGHT edge sensor — useful for placing the robot.
  while (digitalRead(BUTTON) == HIGH) {
    // Show edge sensor state on LEDs for easy placement calibration.
    digitalWrite(LED1, digitalRead(EDGE_L));  // LOW = triggered = LED on
    digitalWrite(LED0, digitalRead(EDGE_R));  // LOW = triggered = LED on
  }

  // Wait until the button is released.
  while (digitalRead(BUTTON) == LOW);

  // Signal that the match is starting — turn both LEDs on.
  digitalWrite(LED0, LOW);
  digitalWrite(LED1, LOW);

  // --- Start Delay ---
  // Change to delay(5000) for competitions that require 5 seconds.
  delay(1000);
}


/*******************************************************************************
 * loop()
 * The main game loop. Checks edge sensors, opponent sensors, and button.
 *******************************************************************************/
void loop() {

  // =========================================================================
  // PRIORITY 1: Edge Detection
  // If the robot reaches the edge of the ring, back off immediately.
  // This always runs first to prevent the robot from falling off.
  // =========================================================================

  if (digitalRead(EDGE_L) == LOW) {
    // --- Left edge detected: reverse, then turn RIGHT ---

    // Stop first (brief pause before reversing).
    motorL.setSpeed(0);
    motorR.setSpeed(0);
    delay(80);

    // Reverse away from edge.
    motorL.setSpeed(-REVERSE_SPEED);
    motorR.setSpeed(-REVERSE_SPEED);
    delay(300);

    // Turn right to face back into the ring.
    // Left motor forward, right motor backward = clockwise spin.
    motorL.setSpeed(150);
    motorR.setSpeed(-150);
    delay(350);

    // Stop briefly before returning to main loop.
    motorL.setSpeed(0);
    motorR.setSpeed(0);
    delay(80);
  }

  else if (digitalRead(EDGE_R) == LOW) {
    // --- Right edge detected: reverse, then turn LEFT ---

    motorL.setSpeed(0);
    motorR.setSpeed(0);
    delay(80);

    motorL.setSpeed(-REVERSE_SPEED);
    motorR.setSpeed(-REVERSE_SPEED);
    delay(300);

    // Turn left: right motor forward, left motor backward = counter-clockwise spin.
    motorL.setSpeed(-150);
    motorR.setSpeed(150);
    delay(350);

    motorL.setSpeed(0);
    motorR.setSpeed(0);
    delay(80);
  }

  // =========================================================================
  // PRIORITY 2: Opponent Detection
  // If any front sensor sees the opponent, drive straight forward to attack.
  // =========================================================================

  else if (digitalRead(OPPONENT_FC) == LOW ||
           digitalRead(OPPONENT_FL) == LOW ||
           digitalRead(OPPONENT_FR) == LOW) {
    // At least one front sensor is triggered — charge forward!
    motorL.setSpeed(ATTACK_SPEED);
    motorR.setSpeed(ATTACK_SPEED);
  }

  // =========================================================================
  // PRIORITY 3: Search
  // No edge, no opponent detected — move in a gentle arc to scan for opponent.
  // =========================================================================

  else {
    // Arc slowly to the right: left motor slightly faster than right.
    // This traces a clockwise circle to scan the ring.
    motorL.setSpeed(SEARCH_SPEED);
    motorR.setSpeed(SEARCH_SPEED / 2);
  }

  // =========================================================================
  // EMERGENCY STOP
  // If the Start button is pressed during a match, stop immediately and halt.
  // =========================================================================

  if (digitalRead(BUTTON) == LOW) {
    motorL.setSpeed(0);
    motorR.setSpeed(0);
    digitalWrite(LED0, HIGH);  // LEDs off
    digitalWrite(LED1, HIGH);
    while (1);  // Halt here — press reset or upload new code to restart.
  }
}
