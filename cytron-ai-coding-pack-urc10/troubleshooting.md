# Troubleshooting — Cytron URC10 Sumo Robot Controller

This document covers the most common problems encountered when setting up and programming the URC10.

---

## Upload / Arduino IDE Issues

### ❌ COM port not appearing in Arduino IDE

**Symptom:** The URC10 is plugged in via USB but no COM port appears under `Tools → Port`.

**Causes and fixes:**
1. **CH340 driver not installed** — Download and install the CH340 driver, then replug the USB cable.
2. **USB cable does not support data** — Many phone charger cables are charge-only. Replace with a known good data cable.
3. **Wrong USB port** — Try a different USB port on your computer.
4. **Board not powered** — If using a USB-only connection for upload, ensure the Micro USB cable is properly seated.

---

### ❌ Upload fails with "avrdude: stk500_recv() timeout"

**Causes and fixes:**
1. **Wrong board selected** — Go to `Tools → Board` and select **Arduino Uno**.
2. **Wrong COM port** — Select the correct COM port under `Tools → Port`.
3. **Board is resetting during upload** — This is usually a driver or cable issue. Reinstall the CH340 driver.

---

### ❌ Compilation error: `CytronMotorDriver.h: No such file`

**Cause:** The Cytron Motor Drivers Library is not installed.

**Fix:**
1. Go to `Sketch → Include Library → Manage Libraries...`
2. Search for `Cytron Motor Drivers`.
3. Install **"Cytron Motor Drivers Library"** by Cytron Technologies.
4. Re-upload the sketch.

---

## Motor Issues

### ❌ Motors don't spin at all

**Check these in order:**
1. **Battery not connected** — Ensure the battery is plugged into the power terminals (VM+ and GND).
2. **Voltage too low** — Verify battery voltage is between 8V and 25V.
3. **Motor terminals not connected** — Check that motor wires are in the correct screw terminals.
4. **`setSpeed(0)` still active** — Check your code — the robot waits for button press in `setup()`. Press the button to start.
5. **Wrong pins** — Confirm your motor objects use `CytronMD motorL(PWM_DIR, 5, 4);` and `CytronMD motorR(PWM_DIR, 6, 7);`.

---

### ❌ One motor spins, the other doesn't

**Causes and fixes:**
1. **Wiring issue** — Check the motor terminal connections for the non-working motor.
2. **Motor is faulty** — Test the motor wire directly with a known working terminal.
3. **Pin conflict** — Check that D4–D7 are not used for anything else in your sketch.

---

### ❌ Robots drives in the wrong direction (left/right swapped)

**Cause:** Motor wires are connected in reverse on one or both terminals.

**Fix:** Swap the two wires on the motor terminal that is going backwards (flip the +/– connection for that motor's terminal).

---

### ❌ Robot spins in a circle and doesn't go straight

**Cause:** Both motors are being driven but in opposite directions.

**Fix:** Swap the wires on one of the motor terminals to reverse its direction.

---

## Sensor Issues

### ❌ Robot doesn't detect the ring edge and drives off

**Check these:**
1. **Sensor wiring** — Confirm the left edge sensor is on D12 and right edge sensor is on D11.
2. **Sensor placement** — Edge sensors must face the floor and be close enough to detect the white line.
3. **Active-low logic** — The sensor outputs LOW when it detects the edge. In the code, the condition is `!digitalRead(EDGE_L)`. If you accidentally removed the `!`, the logic is inverted.
4. **Sensor calibration** — Use `02-sensor-test.ino` and observe the onboard LED feedback to confirm the sensor fires correctly.

---

### ❌ Robot attacks phantom opponents (attacks when nothing is there)

**Causes and fixes:**
1. **Sensor receives too much ambient IR** — IR sensors can be triggered by sunlight, fluorescent lighting, or reflective surfaces. Test in a different environment.
2. **Sensitivity too high** — Some IR sensors have a sensitivity adjustment potentiometer. Turn it to reduce sensitivity.
3. **Wiring issue** — Check that sensor ground wire is properly connected.

---

### ❌ Robot ignores the opponent (doesn't attack when it should)

**Causes and fixes:**
1. **Sensor not triggered** — Use `02-sensor-test.ino` to confirm sensors are detecting before debugging code.
2. **Logical error** — Sensors are active-low. Triggered = LOW. Make sure the attack condition checks `!digitalRead(OPPONENT_FC)` (not `digitalRead(OPPONENT_FC)`).
3. **Sensor not facing the opponent** — Check the physical orientation of the sensor module.

---

## Button Issues

### ❌ Robot never starts (start button press has no effect)

**Check these:**
1. **Button is on D13 with `INPUT_PULLUP`** — When pressed, it reads LOW. The code waits for `!digitalRead(BUTTON)` to be true.
2. **Button wiring** — If using an external button, confirm it connects D13 to GND when pressed.
3. **Loop stuck elsewhere** — Are the edge sensors or opponent sensors stuck triggered? This could prevent the start button from being reached.

---

## LED Issues

### ❌ LEDs are on when they should be off, or vice versa

**Cause:** LEDs on the URC10 are **active-low** — writing `LOW` turns them ON, writing `HIGH` turns them OFF.

**Fix:** Swap your `HIGH`/`LOW` values in `digitalWrite()` for LED pins.

---

## General Tips

- **When in doubt, upload `01-motor-test.ino` first.** This isolates motor issues from code logic issues.
- **Use `02-sensor-test.ino` to verify all sensors before writing complex logic.**
- **Check `pin-map.md`** to confirm all your wiring matches the expected pin assignments.
- **Post on the Cytron community forum** at [www.cytron.io](https://www.cytron.io) if you are stuck — include your code and a photo of your wiring.
