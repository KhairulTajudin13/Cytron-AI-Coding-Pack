# Safety Rules for Radio Controlled (RC) Mode — URC10

> **Read this before powering on your RC receiver and robot.**
> Operating a radio-controlled robot introduces new safety concerns, such as unexpected wireless commands, radio interference, and high-speed motion.

---

## ⚡ Wiring and Power Safety

### 1. Never Reverse Battery Polarity
Connecting the battery backwards to the URC10 power terminals (VM+ and GND) — even for a split second — will **permanently destroy the board**. There is no reverse polarity protection. 
* Double-check polarity with a multimeter before plugging in.
* Ensure your connectors are polarized and keyed to prevent backward connection.

### 2. Confirm Receiver Operating Voltage
Most standard hobby RC receivers operate at **5.0V**.
* Connect the receiver's power pin (VCC/5V) to the URC10 **5V** header.
* Do not connect the receiver directly to the battery supply (VM+) unless the receiver is explicitly rated for that voltage (e.g., high voltage receivers). Doing so will destroy the receiver.

### 3. Connect a Common Ground (GND)
You **must** connect a GND pin from your RC receiver to a GND pin on the URC10. 
* Without a common ground connection, the PWM signals will have no return path.
* This will cause float voltages, causing erratic motor movements, servo twitching, or absolute control failure.

---

## 🤖 Testing and Control Safety

### 4. Lift the Wheels Off the Ground for Initial Tests
Always prop up the robot (place it on a block or stand) so that its wheels can spin freely in the air.
* During your first test of the receiver or drive sketch, a software mistake or inverted channels could make the robot fly off your workbench.
* Verify throttle, steering, and failsafe behavior in the air first.

### 5. Test at Low Speed First
* Start your tests by slowly moving the transmitter joysticks.
* In the Arduino sketches, start with lower speed scaling or test in a restricted space before driving at full speed (`setSpeed(255)`).

### 6. Stop Immediately on Unexpected Behavior
If the motors spin when you release the joysticks, or if the robot twitches:
1. Turn off power to the URC10 board immediately.
2. Check your transmitter binding and deadband settings in the code.
3. Verify that your battery is fully charged (low battery can cause receiver resets).

---

## 📶 Radio Signal and Failsafe Rules

### 7. Power Order Rule: Transmitter ON First, OFF Last
To prevent the receiver from picking up stray radio noise and interpreting it as motor commands:
* **Powering Up:** Turn on the transmitter (Tx) **first**, then turn on the robot (Rx).
* **Powering Down:** Turn off the robot (Rx) **first**, then turn off the transmitter (Tx).

### 8. Implement a Failsafe in Code
If the transmitter loses power, goes out of range, or suffers from signal interference, the receiver may output invalid pulses.
* Your code must monitor the incoming PWM signals.
* If no signal is detected (pulse length reads 0 or falls outside the standard 900–2100 µs range), the sketch must instantly command both motors to stop (`setSpeed(0)`).
* Do not rely solely on the receiver's built-in failsafe; write software failsafes as a secondary protection.
