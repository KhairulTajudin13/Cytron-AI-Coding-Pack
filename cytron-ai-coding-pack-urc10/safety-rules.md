# Safety Rules — Cytron URC10 Sumo Robot Controller

> **Read this before powering on your robot.**
> These rules protect both you and your board from damage or injury.

---

## ⚡ Electrical Safety

### 1. Never Reverse Battery Polarity
Connecting the battery the wrong way — even briefly — will **instantly and permanently damage the board**. There is no protection against reverse polarity.

- Always verify positive (+) and negative (–) terminals before connecting.
- Use a multimeter to confirm polarity if you are unsure.
- Mark your battery connector clearly to avoid mistakes.

### 2. Do Not Exceed Voltage Limits
- **Motor supply voltage:** 8V–25V only.
- Using a higher voltage may destroy the motor driver permanently.
- Using a voltage below 8V may cause the board to behave unpredictably.

### 3. Do Not Exceed Current Limits
- Motor driver: **10A continuous, 30A peak per channel**.
- Logic pins: Maximum **20mA per I/O pin**.
- +5V output: Maximum **1000mA**.
- +3.3V output: Maximum **500mA**.
- Exceeding these limits will damage the board or shorten its life.

> 💡 **Beginner safety note:** Even though the board supports high current (10A continuous, 30A peak per channel), beginners should always test with wheels lifted and start at low speed first. High current only flows when the motors are under load — but it is still important to test safely.

### 4. Do Not Connect Motors to GPIO Pins
The onboard motors **must only connect to the motor terminals** on the board. Connecting motors directly to Arduino I/O pins will permanently damage the microcontroller.

---

## 🤖 Testing Safety

### 5. Lift the Robot During First Motor Test
Always test motor code with the **wheels lifted off the ground**. An unexpected motor command at full power can throw the robot off the table.

### 6. Test at Low Speed First
Start with a low speed value (e.g., `setSpeed(100)`) before moving to full speed (`setSpeed(255)`). This lets you confirm direction and wiring before applying full power.

### 7. Stay Clear of Moving Parts
- Keep fingers, loose wires, and cables away from spinning wheels and drive shafts.
- Wear eye protection if running high-speed tests in an enclosed space.
- Secure all wiring before powering on.

### 8. Stop Immediately If the Board Overheats
If the board feels hot to the touch, smells unusual (burning plastic or electrical smell), or the robot behaves unexpectedly:
1. Press the **Stop button** (Start button while running) immediately.
2. Disconnect the battery.
3. Allow the board to cool before inspecting.

---

## 🔋 Battery Handling

### 9. Disconnect Battery When Not in Use
Never leave the battery connected to the board when not actively testing. This drains the battery and can cause unexpected behavior.

### 10. Handle LiPo Batteries With Care
If using a LiPo battery:
- Do not over-discharge (stop use when the robot slows significantly).
- Do not puncture, crush, or expose to heat.
- Use a battery bag for storage and charging.
- Use a LiPo-compatible charger.

---

## 🏆 Competition and Handling

### 11. Follow Competition Rules
- Most sumo competitions require a **mandatory 5-second delay** after the start signal before the robot may move. The default sample code only has 1 second — **update this before competition use**.
- Always follow the event organizer's safety and handling procedures.

### 12. Safe Handling Practices
- Do not pick up the robot by the motors or sensor wires.
- Ensure all screws and mounts are tight before each run.
- Inspect wiring for pinched or frayed cables before powering on.
- Never run the robot unattended.
