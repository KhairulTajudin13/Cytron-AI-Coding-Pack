# Auto-Kit Hardware List — 1KG Autonomous Sumo Robot Starter Kit using URC10

## Source

Official Cytron Tutorial:
https://my.cytron.io/tutorial/1-kg-autonomous-sumo-robot-starter-kit-user-guide-using-urc10

Full Kit product page:
https://my.cytron.io/p-sumo-robot-1kg-auto-kits

---

## Complete Hardware List

| # | Component | Quantity | Notes |
|---|---|---|---|
| 1 | **URC10 Sumo Robot Controller** | 1 | Arduino-compatible (ATmega328P), onboard dual-channel motor driver, up to 10A continuous per channel |
| 2 | **Maker Object Sensor** | 5 | IR-based object/opponent detection sensor. Plug-and-play GVS connector |
| 3 | **Maker Reflect Sensor** | 2 | IR reflectance sensor for edge/boundary line detection. Plug-and-play GVS connector |
| 4 | **12V 580RPM 3.5kgfcm High Power Brushed DC Geared Motor** | 2 | High-torque brushed DC motors. One left, one right |
| 5 | **G25T1 Silicone Wheel Set (43mm × 30mm)** | 2 (pair) | Silicone tyre with G25 rim. Provides grip on the ring surface |
| 6 | **11.1V LiPo Battery** | 1 | 3-cell lithium polymer battery. Provides power to motors and logic. Requires LiPo-safe charging and handling |
| 7 | **Copper Base** | 2 | Low-friction copper plates installed at the bottom of the chassis to help the robot slide under the opponent |
| 8 | **Dean T LiPo Battery Wire Extension (20cm with Pin Type Cable Lug)** | 1 | Battery connector extension wire. Connects LiPo battery to the URC10 power input |
| 9 | **GVS Female-to-Female Extension Wire** | 7 | 3-wire (Ground, Voltage, Signal) sensor extension cables for connecting Maker Object and Maker Reflect sensors to the URC10 |

---

## Component Roles in the Robot

### URC10
The brain and motor driver of the robot. It runs your Arduino code and drives both DC motors using its onboard high-current motor driver. It also provides power rails (5V, 3.3V) and signal ports for all sensors.

### Maker Object Sensors (×5)
These are **opponent detection sensors**. They use infrared light to detect objects (the opposing robot) in the ring. The kit uses five of them — positioned to cover front, front-left, front-right, and side angles — so the robot can sense where the opponent is and attack.

### Maker Reflect Sensors (×2)
These are **edge detection sensors**. They detect the white boundary line on the sumo ring by measuring how much infrared light reflects back from the floor. When a sensor detects the white line (high reflectance), the robot knows it is near the ring edge and must back away.

### 12V 580RPM Brushed DC Geared Motors (×2)
These are the **drive motors**. One motor powers each wheel. The gearbox reduces speed and increases torque, giving the robot strong pushing force.

### G25T1 Silicone Wheel Set (×2)
The **wheels and tyres** of the robot. Silicone tyres provide friction and grip on the ring surface, which is important for pushing force.

### 11.1V LiPo Battery
The **power source** for the entire robot. This is a 3-cell lithium polymer (LiPo) battery. It provides the high current needed for the DC motors. Requires careful handling — see `auto-kit-safety-rules.md`.

### Copper Base (×2)
The **underside sled plates**. Copper plates are installed flush with the bottom of the chassis. Being smooth and low, they help the robot's front blade slide under the opponent and reduce resistance when being pushed.

### Dean T LiPo Battery Wire Extension
The **battery connection cable**. This 20cm Dean T plug wire with cable lug connects the LiPo battery's Dean T connector to the URC10's screw terminal power input.

### GVS Female-to-Female Extension Wires (×7)
**Sensor cables**. GVS = Ground, Voltage, Signal. These 3-wire cables connect the Maker Object and Maker Reflect sensors to the URC10's sensor ports. Each cable carries power, ground, and the sensor signal to the board.

---

## What Is NOT Included in the Kit

- **Chassis / Frame** — The physical body of the robot is a 3D-printed or custom chassis. STL files are available at the link provided in the official tutorial.
- **Front Blade / Scoop** — The front shovel is also a 3D-printed or machined part, included in the full kit assembly but not a commercially purchased sensor or electronic component.
- **Screws and standoffs** — Typically included in the full kit package. Use self-tapping screws as instructed in the assembly guide.
- **RC transmitter/receiver** — Not used in Autonomous Mode. No RC components are required for this learning path.

---

## Important Notes

> ⚠️ **LiPo Safety:** The 11.1V LiPo battery is a lithium polymer chemistry battery. It must never be over-discharged, short-circuited, or charged with a non-LiPo charger. See `auto-kit-safety-rules.md` for full LiPo handling rules.

> ⚠️ **Motor Current:** The 12V motors can draw significant current during stall or hard push situations. The URC10 handles up to 10A continuous per channel — but always test with wheels lifted before placing on the floor.

> ⚠️ **Front Blade:** The front scoop/blade is a sharpened metal part. Handle with care during assembly and competition. See `auto-kit-safety-rules.md`.
