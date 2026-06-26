/*******************************************************************************
 * 01 — Motor Test
 * Cytron URC10 Sumo Robot Controller
 *
 * PURPOSE:
 * Test that Motor 1 (Left) and Motor 2 (Right) are connected correctly
 * and spinning in the expected direction BEFORE using the full sumo code.
 *
 * TESTING STEPS:
 * -----------------------------------------------------------------------
 * Step 1: Connect the URC10 to your PC via Micro USB.
 * Step 2: Select Board: Arduino Uno | Port: your COM port.
 * Step 3: Upload this sketch.
 * Step 4: ** LIFT THE ROBOT WHEELS OFF THE GROUND BEFORE PRESSING START **
 * Step 5: Press the Start button (D13) on the board.
 * Step 6: Watch the wheels spin and confirm:
 *           - Both wheels spin FORWARD (outward from the robot body)
 *           - Both wheels spin BACKWARD (inward)
 *           - The robot halts after the test sequence
 * Step 7: If one wheel spins the wrong way, swap its two wires on the
 *           motor terminal for that motor (flip + and –).
 * -----------------------------------------------------------------------
 *
 * MOTOR PINS (internally wired on the URC10 — do not change):
 *   Motor Left  (Motor 1): PWM = D5, Direction = D4
 *   Motor Right (Motor 2): PWM = D6, Direction = D7
 *   D4, D5, D6, D7 are RESERVED — never use them for sensors or LEDs.
 *
 * HARDWARE: Cytron URC10 Sumo Robot Controller
 * BOARD:    Arduino Uno (select in Arduino IDE)
 * LIBRARY:  Cytron Motor Drivers Library
 *******************************************************************************/

#include <CytronMotorDriver.h>

// --- Pin Definitions ---
#define LED0   0   // Onboard LED 0 (active-low: LOW = ON, HIGH = OFF)
#define LED1   1   // Onboard LED 1 (active-low: LOW = ON, HIGH = OFF)
#define BUTTON 13  // Start button  (active-low: pressed = LOW)

// --- Motor Objects ---
// CytronMD(mode, pwmPin, dirPin)
// Motor Left  (Motor 1): PWM on D5, Direction on D4
// Motor Right (Motor 2): PWM on D6, Direction on D7
// ⚠️ D4, D5, D6, D7 are internally wired to the motor driver on the URC10.
//    Do NOT use them for anything else in your sketch.
CytronMD motorL(PWM_DIR, 5, 4);
CytronMD motorR(PWM_DIR, 6, 7);


/*******************************************************************************
 * setup()
 * Runs once on power-up. Configures pins and waits for the Start button.
 *******************************************************************************/
void setup() {
  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(LED0,   OUTPUT);
  pinMode(LED1,   OUTPUT);

  // Turn both LEDs off on startup.
  // Active-low: write HIGH to turn OFF.
  digitalWrite(LED0, HIGH);
  digitalWrite(LED1, HIGH);

  // Stop both motors immediately on startup — safety first.
  motorL.setSpeed(0);
  motorR.setSpeed(0);

  // Blink LED0 slowly while waiting for the Start button.
  // This confirms the board is powered and ready.
  while (digitalRead(BUTTON) == HIGH) {  // BUTTON reads HIGH when NOT pressed
    digitalWrite(LED0, LOW);   // LED on
    delay(300);
    digitalWrite(LED0, HIGH);  // LED off
    delay(300);
  }

  // Wait for the button to be fully released before starting the test.
  while (digitalRead(BUTTON) == LOW);

  // Both LEDs on = test is about to begin.
  digitalWrite(LED0, LOW);
  digitalWrite(LED1, LOW);
  delay(500);  // Short pause before first movement
}


/*******************************************************************************
 * loop()
 * Runs the motor test sequence once, then stops.
 *
 * Sequence:
 *   1. Forward at low speed  → stop
 *   2. Reverse at low speed  → stop
 *   3. Test complete — LEDs blink and halt
 *******************************************************************************/
void loop() {

  // -----------------------------------------------------------------------
  // Step 1: FORWARD at low safe speed (150 out of 255 max)
  // setSpeed(positive) = forward direction
  // Expected: both wheels spin forward
  // -----------------------------------------------------------------------
  motorL.setSpeed(150);
  motorR.setSpeed(150);
  delay(1500);  // Run for 1.5 seconds

  // Stop both motors.
  motorL.setSpeed(0);
  motorR.setSpeed(0);
  delay(700);  // Pause before next step

  // -----------------------------------------------------------------------
  // Step 2: REVERSE at low safe speed
  // setSpeed(negative) = reverse direction
  // Expected: both wheels spin backward
  // -----------------------------------------------------------------------
  motorL.setSpeed(-150);
  motorR.setSpeed(-150);
  delay(1500);  // Run for 1.5 seconds

  // Stop both motors.
  motorL.setSpeed(0);
  motorR.setSpeed(0);
  delay(500);

  // -----------------------------------------------------------------------
  // Test complete — blink both LEDs to signal done.
  // -----------------------------------------------------------------------
  for (int i = 0; i < 6; i++) {
    digitalWrite(LED0, LOW);
    digitalWrite(LED1, HIGH);
    delay(200);
    digitalWrite(LED0, HIGH);
    digitalWrite(LED1, LOW);
    delay(200);
  }

  // Turn LEDs off and halt here permanently.
  // Upload new code or press the reset button to run the test again.
  digitalWrite(LED0, HIGH);
  digitalWrite(LED1, HIGH);
  while (1);
}
