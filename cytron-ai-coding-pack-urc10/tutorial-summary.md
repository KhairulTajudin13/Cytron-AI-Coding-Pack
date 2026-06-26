# Tutorial Summary — URC10 Getting Started Flow

This is a quick recap of the official URC10 getting-started process. If you have already completed this, you can skip to `start-here.md` and begin using this AI Coding Pack.

---

## Step 1: Install the Arduino IDE

1. Go to [https://www.arduino.cc/en/software](https://www.arduino.cc/en/software).
2. Download and install **Arduino IDE** (version 1.8.x or 2.x).
3. Open the Arduino IDE after installation.

---

## Step 2: Install the CH340 USB Driver

The URC10 uses a **CH340 USB-to-UART chip** to communicate with your PC. Your PC needs this driver to recognize the board.

**Some operating systems (macOS, Linux) may install the CH340 driver automatically.** On Windows, you will likely need to install it manually.

**Recommended driver source (official WCH manufacturer):**
> [https://www.wch-ic.com/downloads/CH341SER_EXE.html](https://www.wch-ic.com/downloads/CH341SER_EXE.html)

1. Download `CH341SER.EXE` from the link above.
2. Run the installer and click **Install**.
3. After installation, plug in your URC10 via **Micro USB**.
4. Open **Device Manager** on Windows — you should see a COM port appear (e.g., `COM3`).

> **Note:** If no COM port appears, the driver is not installed correctly or the USB cable does not support data transfer (some cables are charge-only). Try a different cable or re-run the installer.

---

## Step 3: Install the Cytron Motor Drivers Library

1. In the Arduino IDE, go to **Sketch → Include Library → Manage Libraries...**.
2. In the search box, type: `Cytron Motor Drivers`.
3. Find **"Cytron Motor Drivers Library"** by Cytron Technologies.
4. Click **Install**.

---

## Step 4: Configure the Arduino IDE for URC10

1. Go to **Tools → Board** and select **"Arduino Uno"**.
2. Go to **Tools → Port** and select the COM port that appeared when you plugged in the URC10.

---

## Step 5: Upload the Sample Code

1. Open the provided `URC10SumoRobot.ino` sample sketch.
2. Click the **Upload** button (right arrow icon).
3. The IDE will compile and upload the code to the board.
4. The onboard LEDs will indicate the board is ready.

---

## Step 6: Connect the Robot Hardware Separately

The software is now on the board. The next step is building and connecting the physical robot:

- Connect your **DC motors** to the motor terminals (Motor L and Motor R).
- Connect your **edge sensors** (line sensors) to the designated ports.
- Connect your **opponent sensors** (IR sensors) to the designated ports.
- Connect a **LiPo or suitable battery pack** (8V–25V) to the power terminals — **observe polarity!**

> ⚠️ **Safety reminder:** Connect and verify all hardware BEFORE connecting the battery. Double-check polarity before powering on.

---

## What Happens When You Power On

1. The robot waits for the **Start Button** to be pressed.
2. While waiting, the **onboard LEDs reflect the edge sensor status** (useful for calibration).
3. When the button is pressed and released, the robot executes a **start routine** (turn, move forward, scan), then enters the main sumo loop.

---

## Expanding the Beginner Code — Side Sensors

The beginner code example (`03-basic-sumo-behavior.ino`) intentionally omits the two side opponent sensors (`OPPONENT_L` on D3 and `OPPONENT_R` on D10) to keep the logic simple.

Once you are comfortable with the basic sumo behaviour, you can expand the code to include side sensors. The original `URC10SumoRobot.ino` in `source-docs/` shows how to use all five opponent sensors together, including tracking logic that spins the robot to face the opponent when it is detected on the side.

See `project-ideas.md` — **Idea 2: Smarter Search Strategy** — for suggestions on how to expand your robot's sensing and attack logic step by step.

---

*For more details, refer to the official URC10 User's Manual by Cytron Technologies.*
