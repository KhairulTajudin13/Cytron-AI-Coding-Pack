# Auto-Kit Assembly Notes — 1KG Autonomous Sumo Robot Starter Kit using URC10

## Source

Official Cytron Tutorial:
https://my.cytron.io/tutorial/1-kg-autonomous-sumo-robot-starter-kit-user-guide-using-urc10

STL / 3D Print Files:
https://drive.google.com/drive/folders/1C24gRaOpLt65HX802DUl1U-ghOlVaMhv

---

## ⚠️ Safety Warning — Read Before Assembling

> ⚠️ **Front Blade / Scoop:** The front blade attached in the final step is **sharp**. Handle it carefully at all times. Keep fingers away from the blade edge during installation, adjustment, and transport. Do not allow children to handle the assembled robot unsupervised.

> ⚠️ **LiPo Battery:** Do not connect the battery until all wiring is complete and verified. Never reverse the polarity of the LiPo battery — doing so will damage the URC10 board instantly and may cause the battery to vent or catch fire. Always verify positive (+) and negative (–) terminals before connecting.

> ⚠️ **Reverse Polarity:** Connecting the URC10 power terminal with reversed polarity will permanently damage the board with no possibility of repair. Double-check before every power connection.

---

## Assembly Steps (Based on Official Tutorial)

### Step 1 — Insert Wires into Maker Object and Maker Reflect Sensors

Before installing any sensors to the chassis, insert the GVS extension wires into the connectors on each Maker Object and Maker Reflect sensor.

- Use GVS Female-to-Female Extension Wires
- Match: G = Ground, V = Voltage (3.3V or 5V), S = Signal
- The Maker sensors have GVS-format 3-pin connectors — plug in carefully, noting pin order

**Why:** Pre-attaching wires makes it much easier to route cables after the chassis is assembled.

---

### Step 2 — Install Maker Reflect Sensors Underneath the Chassis

Mount both **Maker Reflect sensors** on the **underside** of the robot chassis, facing downward toward the ring floor.

- Use the **black self-tapping screws** included in the kit
- Position sensors near the front underside so they can read the ring boundary line early enough for the robot to react

**Why:** The Maker Reflect sensors must face the floor to detect the white boundary line. They must be close enough to the floor that the sensor can reliably differentiate between the dark ring surface and the white edge line.

---

### Step 3 — Route and Position Sensor Wires

After mounting the Maker Reflect sensors, route the attached wires so they follow the inside of the chassis and do not interfere with moving parts (wheels, motor shafts).

- Refer to the tutorial photo at Step 3 for correct wire routing
- Wires should be kept away from the wheels and motor shafts
- Leave enough slack to connect to the URC10 board in later steps

---

### Step 4 — Insert Maker Object Sensors into Sensor Slots

Insert each **Maker Object sensor** into its dedicated sensor slot on the chassis.

- The chassis has moulded or printed slots that hold the sensors in the correct orientation
- Insert sensors so the IR emitter and receiver face outward (toward the opponent)
- Secure the sensors in position if required by the chassis design

**Why:** Correct sensor orientation ensures the robot can detect opponents. If a sensor is reversed or misaligned, detection will be unreliable.

---

### Step 5 — Assemble Wheels onto Motors

1. **Attach the rim** (G25 hub) to the motor shaft and tighten it securely
2. **Slide the silicone tyre** onto the rim
3. **Insert the motor** into the motor bracket

- Make sure the rim is tight on the shaft — a loose rim will cause wheel slipping during pushing
- The silicone tyre should be seated fully on the rim with no gaps

---

### Step 6 — Attach Motor Brackets to Chassis

Attach both motor brackets (with motors and wheels assembled) to the chassis using screws.

- Left motor on left side, right motor on right side
- Ensure both wheels are parallel and aligned — misaligned wheels will cause the robot to drive in a curve instead of straight

---

### Step 7 — Install Copper Plates at the Bottom of the Chassis

Insert the **copper base plates** at the bottom of the chassis and screw them in place.

- The copper plates form the underside sled of the robot
- They should sit flush with the bottom of the chassis with no gaps or protrusions
- The flat, low-friction copper surface helps the front blade slide under the opponent during a push

---

### Step 8 — Place the Battery Inside the Chassis

**Before connecting any wires**, place the LiPo battery inside the chassis battery compartment.

- Place the battery first before mounting the URC10 board — the battery often must go in from the top or a specific direction that is blocked once the board is installed
- Do not connect the battery connector to anything yet

> ⚠️ **Battery polarity:** Before connecting the battery connector later, always verify which terminal is positive (+) and which is negative (–). Reversing polarity will permanently destroy the URC10 board.

---

### Step 9 — Screw the URC10 Board onto the Chassis

Mount the **URC10 board** onto the top of the chassis using the provided screws and standoffs.

- Use standoffs to raise the board off the chassis surface and prevent electrical shorts
- Ensure the USB port and power input terminal are accessible after mounting
- Do not over-tighten screws — the PCB can crack or the standoff can stress the board

---

### Step 10 — Connect Sensor Wires to the URC10

Connect the GVS extension wires from the Maker Object and Maker Reflect sensors to the appropriate sensor ports on the URC10 board.

- Match the GVS pin order: G = GND, V = 5V (or 3.3V), S = Signal
- Refer to `auto-kit-sensor-map.md` for which pins each sensor connects to
- Ensure each connector is fully seated and oriented correctly

> ℹ️ **Start signal:** For this AI Coding Pack, the Auto Kit Mode standard start method is the **IR Sumo Start Module on D2**. Connect the IR Sumo Start `S` terminal to D2. See `auto-kit-sensor-map.md` for full wiring details.

---

### Step 11 — Connect Motor and Battery Connector Wires

Connect the motor wires to the URC10 motor terminals (M1 and M2), and connect the Dean T LiPo battery extension wire to the URC10 power input terminal.

- **Motor 1 (Left):** M1 terminal on URC10
- **Motor 2 (Right):** M2 terminal on URC10
- **Battery:** VM (+) and GND (–) terminals on the URC10 power input

> ⚠️ **Polarity check:** Before connecting the battery, verify VM = positive and GND = negative. A multimeter can be used to check the Dean T connector polarity. Reversing this connection will permanently destroy the board.

---

### Step 12 — Connect the IR Sumo Start Module

The IR Sumo Start Module replaces the physical start button. It allows the judge to start and stop the robot wirelessly using an IR remote control during a competition.

**Wiring:**

| IR Sumo Start Terminal | URC10 Connection |
|---|---|
| + (Power) | 5V |
| − (Ground) | GND |
| S (Signal) | D2 |

Connect the three wires from the IR Sumo Start module to the URC10 board:
1. **+ wire** to any 5V pin on the URC10
2. **− wire** to any GND pin on the URC10
3. **S wire** to digital pin **D2** on the URC10

**Important — pin mode:**

Do **not** use `INPUT_PULLUP` for D2 when using the IR Sumo Start module.
The module actively drives the D2 signal line. The code configures it as plain `INPUT`:
```cpp
pinMode(IR_SUMO_START_PIN, INPUT);  // Module drives D2 — no pullup needed
```

**Signal logic:**

| IR Sumo Start Signal | Meaning | Robot behaviour |
|---|---|---|
| **D2 = HIGH** | RUN — judge started the match | Robot runs normally |
| **D2 = LOW** | READY / STOP — judge stopped or no signal | Robot stops immediately |

> ℹ️ **Fallback:** If you do not have an IR Sumo Start Module, a physical button can be used on D2 as a temporary test method. Change `INPUT` to `INPUT_PULLUP` and use the `waitForStartButton()` logic instead. This is for bench testing only — competitions require the IR module.

---

### Step 12b — Mount the IR Sumo Start Module

Mount the IR Sumo Start module on the robot chassis so that the **IR receiver window faces outward** toward the judge's transmitter.

**Mounting recommendations:**
- Mount on the front, top, or side of the chassis — anywhere with a clear line of sight to the judge's position
- Do not mount it underneath the chassis or inside an enclosed bay
- Secure the module with a cable tie, double-sided tape, or a small bracket
- Route the wiring neatly away from the front blade and wheel shafts

> ⚠️ The IR Sumo Start module must have a **clear, unobstructed view** of the judge's IR transmitter. If the receiver is blocked by the chassis body or other components, the robot may not receive the START or STOP signal.

---

### Step 13 — Attach the Front Blade

> ⚠️ **SHARP BLADE WARNING:** The front blade/scoop is a sharpened metal part. Handle it with extreme care. Keep fingers away from the blade edge at all times. Never allow unsupervised handling by children.

Attach the front blade at the front of the chassis. The blade should sit low to the ground — its purpose is to slide under the opponent's chassis during a push, giving your robot a leverage advantage.

- Ensure the blade is securely fastened — a loose blade is a safety hazard
- After attaching, verify the blade clears the floor slightly — it should not drag but should be as close to the ring surface as possible

---

### Step 14 — Final Assembly Check

Before powering on for the first time:

- [ ] All sensor wires are connected and fully seated
- [ ] Motor wires are connected to the correct terminals (M1 = left, M2 = right)
- [ ] Battery connector polarity is verified (VM = +, GND = –)
- [ ] No wires or cables are near the wheel shafts
- [ ] The front blade is secure
- [ ] The URC10 is screwed down with no shorts underneath
- [ ] The robot is **lifted off the ground** before connecting power for the first time

---

## After Assembly — What to Do Next

1. Read `auto-kit-sensor-map.md` to verify your pin connections
2. Read `auto-kit-safety-rules.md` before powering on
3. Upload `08-auto-kit-standard.ino` and confirm it compiles before connecting power
4. Test the IR Sumo Start module — verify the onboard LED changes when you press the module’s test button or point the remote at it
5. Lift wheels, power on, send RUN signal — confirm motors spin and stop on STOP signal before placing on the ring
