# Radio Controlled (RC) Mode Context — URC10

This document explains the concepts, signals, and layout of Radio Controlled (RC) mode on the Cytron URC10.

---

## 1. Autonomous Sumo vs. Radio Controlled (RC) Mode

The default Cytron URC10 sample code and tutorials are designed for **autonomous sumo robot behavior**. 
* **Autonomous Behavior:** The microcontroller (`ATmega328P`) acts as the "brain". It reads onboard sensors (like the IR edge and opponent sensors) and runs predefined algorithms to search for and push opponents out of the ring without human intervention.
* **Radio Controlled (RC) Mode:** In RC mode, decision-making is shifted to a **human pilot**. The pilot controls the robot's movement (speed, direction, steering) using a handheld RC transmitter. The transmitter sends commands wirelessly to an RC receiver mounted on the robot, which passes the commands to the URC10 microcontroller to drive the motors.

---

## 2. RC Transmitter and Receiver Mechanics

An RC system consists of two main hardware components:
1. **Transmitter (Tx):** The handheld controller with joysticks, switches, and dials.
2. **Receiver (Rx):** The small device mounted on the robot that receives signals wirelessly and outputs standard hobby servo PWM signals on individual channel pins.

### PWM (Pulse Width Modulation) Control Signals
Standard RC receivers communicate channel positions using PWM signals. Unlike the high-frequency PWM used to control motor speed, RC servo PWM is a low-frequency pulse train (typically 50Hz, or one pulse every 20ms). The *width* (duration) of the active-high pulse determines the stick position:

* **1000 µs (microseconds) Minimum:** Full reverse / full left / minimum channel value.
* **1500 µs Center/Neutral:** Center stick / motor stop / neutral position.
* **2000 µs Microseconds Maximum:** Full forward / full right / maximum channel value.

The Arduino reads these pulses using the built-in `pulseIn()` function, which measures the length of the pulse in microseconds.

---

## 3. Power and Ground Requirements

Connecting a receiver to the URC10 requires careful attention to electrical specifications:

> **Important Power and Ground Rules:**
> 1. **Confirm Receiver Input Voltage:** Most RC receivers operate at **5V**. Verify your receiver's voltage specification in its manual before connecting it. The URC10 provides a regulated 5V output that can power most standard receivers.
> 2. **Connect Common GND (Ground):** You **must** connect a ground wire from the receiver's GND terminal to the URC10's GND terminal. Without a common ground, the reference voltage for the PWM signals will float, leading to jittery motor behavior, false signal-loss triggers, or no signal detection at all.

---

## 4. Learning Path Progression

Moving from autonomous sumo to RC control introduces several programming concepts:
* **Pulse Measurement:** Reading variable-width digital pulses in real time.
* **Signal Calibration & Scaling:** Mapping raw microsecond pulse widths (1000–2000 µs) into motor speed values (-255 to 255).
* **Failsafe Implementation:** Safely shutting down motors if the receiver loses signal or the transmitter is powered off.
* **Mixing (Arcade Drive):** Combining throttle and steering inputs into individual left and right wheel speeds.
* **Hybrid Systems:** Designing a robot that can switch between manual RC control and autonomous routines at the flip of a switch.
