# Radio Controlled (RC) Path Validation Checklist

Use this checklist to verify that the RC implementation on the Cytron URC10 Sumo Robot Controller matches all technical, safety, and architectural constraints.

---

## 📌 1. Pin Assignment Verification

- [ ] **No RC receiver input uses D4, D5, D6, or D7.**
  * *Reason:* D4–D7 are internally hardwired to the H-bridge motor driver.
  * *Check:* Verify that none of the `pulseIn()` or `digitalRead()` inputs in the sketches are assigned to 4, 5, 6, or 7.
- [ ] **D0 and D1 are avoided for GPIO when Serial is active.**
  * *Reason:* D0 and D1 are the hardware TX/RX pins. Writing to them while `Serial.begin()` is running will corrupt communication.
  * *Check:* Verify that no `digitalWrite()` or `pinMode(..., OUTPUT)` calls are performed on D0 (`LED0`) or D1 (`LED1`) in `05-rc-receiver-test.ino`, `06-radio-controlled-drive.ino`, or `07-hybrid-rc-autonomous-mode.ino`.
- [ ] **Onboard motor pins remain correct.**
  * *Reason:* Left motor must use D5 (PWM) and D4 (DIR). Right motor must use D6 (PWM) and D7 (DIR).
  * *Check:* Confirm that all motor declarations match:
    ```cpp
    CytronMD motorL(PWM_DIR, 5, 4);
    CytronMD motorR(PWM_DIR, 6, 7);
    ```
- [ ] **Throttle, Steering, and Mode Switch assignments are correctly mapped.**
  * *Check:* Confirm the definitions:
    * Throttle: D2
    * Steering: D3
    * Mode Switch: A3

---

## 💻 2. Software & Library Verification

- [ ] **All sketches use Arduino C/C++.**
  * *Check:* Ensure files are saved with the `.ino` extension and compile successfully under the Arduino IDE using the **Arduino Uno** board configuration.
- [ ] **Code uses the Cytron Motor Drivers Library.**
  * *Check:* Confirm that all motor driving is performed using:
    ```cpp
    #include <CytronMotorDriver.h>
    ```
    And that `analogWrite` / `digitalWrite` are NOT used to control motor speeds directly.
- [ ] **No unsupported motor library functions are used.**
  * *Check:* Ensure the only speed command is `setSpeed(speed)`. Verify there are no calls to `.begin()`, `.run()`, or `.stop()`.

---

## ⚡ 3. Safety and Failsafe Verification

- [ ] **Safety warning comment blocks are included.**
  * *Check:* Verify that the standard safety comment block is located at the top of every motor-moving sketch (`06` and `07`):
    ```cpp
    /*
     * SAFETY — BEFORE RUNNING THIS CODE:
     * 1. Lift the robot wheels off the ground.
     * 2. Confirm motor directions are correct before placing on the floor.
     * 3. Start at low speed (e.g. setSpeed(100)) before testing at full speed.
     * See safety-rules.md for full guidance.
     */
    ```
- [ ] **Battery polarity warning is present.**
  * *Check:* Ensure code comments or docs mention not reversing battery polarity (reversing battery polarity will damage the board permanently).
- [ ] **Common Ground (GND) is explicitly mandated.**
  * *Check:* Verify that documentation instructs the user to connect a common GND between the receiver and the URC10.
- [ ] **Signal-loss failsafe is implemented in drive code.**
  * *Check:* Confirm that `06` and `07` sketches check for signal loss (pulse reading equals 0 or is outside `[900, 2100]` µs) and immediately write `setSpeed(0)` to both motors.

---

## 📁 4. Directory and File Layout Verification

- [ ] **Directory structure matches requirement exactly:**
  * [ ] `rc-mode/rc-control-context.md`
  * [ ] `rc-mode/rc-pin-map.md`
  * [ ] `rc-mode/rc-safety-rules.md`
  * [ ] `rc-mode/rc-troubleshooting.md`
  * [ ] `rc-mode/code-examples/05-rc-receiver-test.ino`
  * [ ] `rc-mode/code-examples/06-radio-controlled-drive.ino`
  * [ ] `rc-mode/code-examples/07-hybrid-rc-autonomous-mode.ino`
- [ ] **Existing autonomous sumo robot files are left intact.**
  * *Check:* Verify `01-motor-test.ino`, `02-sensor-test.ino`, `03-basic-sumo-behavior.ino`, and `04-application-extension.ino` are untouched in their original folders.
