# Troubleshooting Radio Controlled (RC) Mode — URC10

This document covers common problems encountered when connecting, calibrating, and programming an RC receiver with the Cytron URC10.

---

## 📶 Receiver Signal Issues

### ❌ Serial Monitor prints 0 or very erratic pulse values in receiver test

**Symptoms:** The `05-rc-receiver-test.ino` sketch prints `0` continuously, or values fluctuate wildly (e.g. jumping from 500 to 3000) when the stick is stationary.

**Causes and fixes:**
1. **Missing Common Ground** — You forgot to connect the GND pin of the receiver to the GND pin of the URC10. Connect them with a jumper wire.
2. **Receiver is not Bound** — The transmitter is off or the receiver is not bound to it (indicated by a blinking red LED on the receiver). Bind the transmitter and receiver first according to the manufacturer's manual.
3. **Incorrect Pin Mapping** — Ensure Throttle is connected to **D2** and Steering to **D3**. Check your wiring.
4. **Incorrect pulseIn() Timeout** — If the timeout is too short, `pulseIn()` returns 0. Ensure the timeout is set to at least 25000 µs (25ms) to catch the 50Hz RC pulse frame.
5. **No Power to Receiver** — Ensure the receiver's power light is on. Confirm it is connected to the 5V terminal of the URC10.

---

## 🤖 Motor Response Issues

### ❌ Motors hum or twitch when transmitter sticks are in neutral

**Symptom:** The robot makes a high-pitched noise or slightly rotates its wheels when you are not touching the transmitter sticks.

**Causes and fixes:**
1. **Deadband is Too Small** — All transmitters have slight neutral stick variations (jitter). In the code (e.g., `06-radio-controlled-drive.ino`), increase the deadband setting. For example, if the neutral reading is 1495 µs, a deadband of `50` (ignoring 1450–1550 µs) will resolve the issue.
2. **Center Calibration is Off** — Some transmitters do not center exactly at 1500 µs. Upload `05-rc-receiver-test.ino`, write down your exact neutral stick readings, and adjust the center offset value in the code. Alternatively, adjust the trim dials on your transmitter until the values read 1500 µs in the Serial Monitor.

---

### ❌ Robot moves backward when pushing throttle forward, or steering is reversed

**Symptom:** Pushing the throttle stick forward makes the robot drive backward, or steering left makes the robot turn right.

**Causes and fixes:**
1. **Transmitter Channels Reversed** — Most RC transmitters have small reverse switches (or settings menus) for each channel. Toggle the REV switch for the throttle or steering channel on your transmitter.
2. **Motor Wires Swapped** — If only one side is going the wrong way, swap the wires on that motor's terminal (flip the VM+ and VM- connections on the screw terminal block).
3. **Sign Inversion in Code** — In the motor speed mixing math, ensure you are adding/subtracting steering and throttle correctly.

---

### ❌ Robot spins in a circle when pushing the throttle stick straight forward

**Symptom:** When pushing the throttle forward, one wheel goes forward and the other goes backward.

**Causes and fixes:**
1. **Differential Direction Difference** — Because the left and right motors are mirrored physically on the chassis, one motor must spin clockwise and the other counter-clockwise for the robot to move straight. If your motor wiring is not set up for this, swap the wires on one of the motor terminal blocks to correct the rotation direction of that motor.
2. **Steering and Throttle Mixed Up** — You may have plugged the Throttle signal into the Steering pin and vice versa. Swap the signal wires on D2 and D3, or swap their definitions in your code.

---

## ⚡ Power and Reset Issues

### ❌ Board resets or connection drops when applying throttle

**Symptom:** When you push the throttle stick, the URC10 LEDs blink, the Serial connection drops, and the motors stop.

**Causes and fixes:**
1. **Low Battery / Sag** — When the motors draw power, they cause the battery voltage to drop (sag). If the battery is nearly discharged, the voltage drops below the threshold needed to keep the URC10's 5V regulator running, triggering a brownout reset. Charge the battery.
2. **Short Circuit** — Inspect your wiring to ensure there are no stray strands of wire shorting the motor outputs or the power input terminal.
3. **Current Overload** — If the motors are stalled (blocked from spinning), they will draw maximum current and cause a voltage sag. Ensure the wheels can spin freely.
