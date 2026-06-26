# Hardware Setup — Cytron URC10 Sumo Robot Controller

This document covers the physical hardware setup for the URC10, including power, motors, sensors, and USB upload.

---

## Required Hardware

| Item | Details |
|---|---|
| URC10 Sumo Robot Controller | The main board |
| DC Gear Motors (x2) | For left and right drive wheels |
| Edge/Line Sensors (x2) | Detect the white ring edge (active-low digital output) |
| Opponent Sensors — Front (x3) | IR sensors for front detection (FL, FC, FR) |
| Opponent Sensors — Side (x2) | IR sensors for left and right (active-low digital) |
| Battery Pack | 8V–25V DC (e.g., 2S or 3S LiPo) |
| Micro USB Cable | Data-capable cable for programming |
| Robot Chassis/Frame | Built separately — the URC10 mounts on or within it |

---

## Power Input

| Spec | Value |
|---|---|
| Input Voltage | **8V to 25V DC** |
| Connector Type | Screw terminals (marked VM+ and GND) |
| Polarity | **Observe carefully — reversed polarity instantly damages the board** |

> ⚠️ **Critical:** Always double-check the positive (+) and negative (–) terminals before connecting the battery. Use a multimeter if unsure.

---

## Motor Terminals

The URC10 has two motor output terminal pairs:

| Terminal | Connects to |
|---|---|
| Motor Left (MOTA) | Left drive motor |
| Motor Right (MOTB) | Right drive motor |

- Motor terminals are driven by the onboard dual motor driver rated at **10A continuous, 30A peak per channel**.
- **Do NOT connect motors directly to Arduino GPIO pins** — always use the motor terminals.
- The motor driver is controlled via pins D4, D5, D6, D7 which are **internally wired** — do not use these pins for other peripherals.

> 💡 **Beginner safety note:** Even though the board supports high current (10A continuous, 30A peak per channel), beginners should always test with wheels lifted and start at low speed first. High current only flows when the motors are under load — but it is still important to test safely.

---

## Uploading Code (USB)

1. Connect the URC10 to your PC using a **Micro USB cable** (data-capable).
2. The board uses a **CH340 USB-to-UART chip** — ensure the driver is installed.
3. In Arduino IDE, select **Board: Arduino Uno** and the correct **COM port**.
4. Click **Upload**.

> ⚠️ **Safety during upload:** Disconnect or disable the battery before uploading if the robot is fully assembled. Unexpected motor movement can occur when the MCU resets during upload.

---

## CH340 Driver Installation

The URC10 uses a **CH340 USB-to-UART chip**. Your PC needs this driver to detect the board as a COM port.

**Some operating systems (macOS, Linux) may install the CH340 driver automatically.** On Windows, you may need to install it manually if the COM port does not appear.

**Recommended driver source (official WCH manufacturer):**
> [https://www.wch-ic.com/downloads/CH341SER_EXE.html](https://www.wch-ic.com/downloads/CH341SER_EXE.html)

**Installation steps:**
1. Download `CH341SER.EXE` from the link above.
2. Run the installer and click **Install**.
3. Unplug and re-plug the URC10 Micro USB cable.
4. Open **Device Manager** on Windows — you should see a COM port appear (e.g., `COM3`).
5. Select that COM port in Arduino IDE under **Tools → Port**.

> If the COM port still does not appear after driver installation, try a different USB cable — many phone charger cables are **charge-only** and do not carry data.

---

## Sensor Connections

### Edge Sensors (Floor Sensors)
- Placed **underneath the robot** facing the floor.
- Detect the white edge of the sumo ring.
- Connect to the dedicated **EDGE_L** and **EDGE_R** ports on the board.

### Opponent Sensors (IR Sensors)
- Placed around the robot to detect the opponent.
- Five sensors total: Front Left, Front Center, Front Right, Side Left, Side Right.
- Connect to the designated sensor ports on the board.

### Ultrasonic Sensors (Optional)
- The board provides two HC-SR04 ports.
- Sensor 2 shares pins with Edge Right (D11) and Opponent Right (D10) — **do not use both simultaneously** without remapping.

---

## Logic Output Pins

| Output | Maximum Current |
|---|---|
| +5V | 1000mA |
| +3.3V | 500mA |
| Any single I/O pin | 20mA |

---

## Safe Testing Reminders

- 🔼 **Lift the robot off the ground** when testing motors for the first time.
- 🐢 **Start at low speed** (e.g., `setSpeed(100)`) before running at full power.
- 🌡️ **Stop immediately** if the board feels hot, smells unusual, or behaves unexpectedly.
- 🔋 **Disconnect the battery** when not testing or programming.
- 🧲 **Keep loose wires clear** of spinning wheels and moving parts.
