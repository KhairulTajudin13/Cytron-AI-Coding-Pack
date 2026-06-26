/*******************************************************************************
 * 04 — Application Extension: Serial Debug Mode
 * Cytron URC10 Sumo Robot Controller
 *
 * PURPOSE:
 * Extends the basic sumo behaviour from 03-basic-sumo-behavior.ino
 * by adding a Serial Debug Mode.
 *
 * When Serial Debug Mode is ON, the robot prints to the Serial Monitor
 * every loop iteration to tell you exactly what it is doing and why.
 * This is extremely useful for understanding your robot's decision-making
 * and for identifying sensor or logic problems.
 *
 * TESTING STEPS:
 * -----------------------------------------------------------------------
 * Step 1: Run 01-motor-test.ino and 02-sensor-test.ino first.
 * Step 2: Set DEBUG_MODE to true (see below).
 * Step 3: Upload this sketch.
 * Step 4: Open Serial Monitor at 9600 baud.
 * Step 5: Lift the robot off the ground and press the Start button.
 * Step 6: Trigger sensors by hand and watch the Serial Monitor
 *         report which condition was matched and what the robot did.
 * Step 7: Once you are happy, set DEBUG_MODE to false for competition use
 *         (printing to Serial Monitor adds a small delay each loop).
 * -----------------------------------------------------------------------
 *
 * LEARNING NOTE — ADJUSTABLE SEARCH SPEED:
 * This example also demonstrates how to use a named constant for search speed,
 * so you can try different values without hunting through the code.
 * Change SEARCH_SPEED below and re-upload to see the difference.
 *
 * ⚠️ D4, D5, D6, D7 are reserved for the motor driver — DO NOT reassign them.
 *
 * HARDWARE: Cytron URC10 Sumo Robot Controller
 * BOARD:    Arduino Uno (select in Arduino IDE)
 * LIBRARY:  Cytron Motor Drivers Library
 *******************************************************************************/

#include <CytronMotorDriver.h>

// --- Debug Mode ---
// Set to true to print robot state to Serial Monitor each loop.
// Set to false to disable debug output (e.g. for competition use).
#define DEBUG_MODE true

// --- Pin Definitions ---
#define LED0        0   // Onboard LED 0 (active-low: LOW = ON)
#define LED1        1   // Onboard LED 1 (active-low: LOW = ON)
#define BUTTON      13  // Start / stop button (active-low)
#define EDGE_L      12  // Left edge sensor   (active-low)
#define EDGE_R      11  // Right edge sensor  (active-low)
#define OPPONENT_FR A0  // Front-right opponent sensor (active-low)
#define OPPONENT_FC A1  // Front-center opponent sensor (active-low)
#define OPPONENT_FL A2  // Front-left opponent sensor (active-low)

// --- Speed Settings ---
// ✏️ You can change these values to tune your robot:
#define ATTACK_SPEED  200  // Speed when charging at opponent (0–255)
#define SEARCH_SPEED  120  // Speed during circular search     (0–255)
//     Try SEARCH_SPEED = 80 for a slower, wider scan arc.
//     Try SEARCH_SPEED = 160 for a faster, tighter scan arc.
#define REVERSE_SPEED 180  // Speed when reversing from edge   (0–255)

// --- Motor Objects ---
// Motor Left  (Motor 1): PWM = D5, Direction = D4
// Motor Right (Motor 2): PWM = D6, Direction = D7
CytronMD motorL(PWM_DIR, 5, 4);
CytronMD motorR(PWM_DIR, 6, 7);


/*******************************************************************************
 * debugPrint()
 * Prints a message to the Serial Monitor — but ONLY if DEBUG_MODE is true.
 * If DEBUG_MODE is false, this function does nothing.
 *
 * Parameters:
 *   message — what to print (e.g. "SEARCHING")
 *******************************************************************************/
void debugPrint(const char* message) {
  if (DEBUG_MODE) {
    Serial.println(message);
  }
}


/*******************************************************************************
 * setup()
 * Configure pins, start Serial if debug mode is on, wait for Start button.
 *******************************************************************************/
void setup() {
  pinMode(BUTTON,      INPUT_PULLUP);
  pinMode(EDGE_L,      INPUT_PULLUP);
  pinMode(EDGE_R,      INPUT_PULLUP);
  pinMode(OPPONENT_FL, INPUT_PULLUP);
  pinMode(OPPONENT_FC, INPUT_PULLUP);
  pinMode(OPPONENT_FR, INPUT_PULLUP);
  pinMode(LED0, OUTPUT);
  pinMode(LED1, OUTPUT);

  digitalWrite(LED0, HIGH);
  digitalWrite(LED1, HIGH);

  motorL.setSpeed(0);
  motorR.setSpeed(0);

  // Start Serial Monitor only if debug mode is enabled.
  if (DEBUG_MODE) {
    Serial.begin(9600);
    Serial.println("=== URC10 Serial Debug Mode ON ===");
    Serial.println("Waiting for Start button...");
    Serial.println();
  }

  // --- Wait for Start Button ---
  while (digitalRead(BUTTON) == HIGH) {
    digitalWrite(LED1, digitalRead(EDGE_L));
    digitalWrite(LED0, digitalRead(EDGE_R));
  }
  while (digitalRead(BUTTON) == LOW);

  // LEDs on = match starting.
  digitalWrite(LED0, LOW);
  digitalWrite(LED1, LOW);

  debugPrint("Button pressed. Starting in 1 second...");

  // Start delay — change to 5000 for competitions.
  delay(1000);

  debugPrint("GO!");
  debugPrint("------------------------------------------");
}


/*******************************************************************************
 * loop()
 * Main game loop with Serial debug output on every decision.
 *******************************************************************************/
void loop() {

  // =========================================================================
  // PRIORITY 1: Edge Detection
  // =========================================================================

  if (digitalRead(EDGE_L) == LOW) {
    debugPrint("[EDGE LEFT]  Reversing and turning RIGHT.");

    motorL.setSpeed(0);
    motorR.setSpeed(0);
    delay(80);

    motorL.setSpeed(-REVERSE_SPEED);
    motorR.setSpeed(-REVERSE_SPEED);
    delay(300);

    motorL.setSpeed(150);
    motorR.setSpeed(-150);
    delay(350);

    motorL.setSpeed(0);
    motorR.setSpeed(0);
    delay(80);
  }

  else if (digitalRead(EDGE_R) == LOW) {
    debugPrint("[EDGE RIGHT] Reversing and turning LEFT.");

    motorL.setSpeed(0);
    motorR.setSpeed(0);
    delay(80);

    motorL.setSpeed(-REVERSE_SPEED);
    motorR.setSpeed(-REVERSE_SPEED);
    delay(300);

    motorL.setSpeed(-150);
    motorR.setSpeed(150);
    delay(350);

    motorL.setSpeed(0);
    motorR.setSpeed(0);
    delay(80);
  }

  // =========================================================================
  // PRIORITY 2: Opponent Detection
  // Debug mode also tells you WHICH sensor fired.
  // =========================================================================

  else if (digitalRead(OPPONENT_FC) == LOW) {
    debugPrint("[ATTACK FC]  Opponent FRONT CENTER — charging straight!");
    motorL.setSpeed(ATTACK_SPEED);
    motorR.setSpeed(ATTACK_SPEED);
  }

  else if (digitalRead(OPPONENT_FL) == LOW) {
    debugPrint("[ATTACK FL]  Opponent FRONT LEFT — curving left.");
    motorL.setSpeed(ATTACK_SPEED / 2);
    motorR.setSpeed(ATTACK_SPEED);
  }

  else if (digitalRead(OPPONENT_FR) == LOW) {
    debugPrint("[ATTACK FR]  Opponent FRONT RIGHT — curving right.");
    motorL.setSpeed(ATTACK_SPEED);
    motorR.setSpeed(ATTACK_SPEED / 2);
  }

  // =========================================================================
  // PRIORITY 3: Search
  // =========================================================================

  else {
    debugPrint("[SEARCH]     No opponent. Scanning...");
    // Arc slowly clockwise: left motor faster than right.
    motorL.setSpeed(SEARCH_SPEED);
    motorR.setSpeed(SEARCH_SPEED / 2);
  }

  // =========================================================================
  // EMERGENCY STOP
  // =========================================================================

  if (digitalRead(BUTTON) == LOW) {
    debugPrint("[STOP]  Button pressed. Halting.");
    motorL.setSpeed(0);
    motorR.setSpeed(0);
    digitalWrite(LED0, HIGH);
    digitalWrite(LED1, HIGH);
    while (1);
  }
}
