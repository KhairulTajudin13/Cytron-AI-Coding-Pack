# Auto-Kit Safety Rules — 1KG Autonomous Sumo Robot Starter Kit using URC10

## Why Safety Rules Matter

This kit involves high-current lithium polymer batteries, sharp metal parts, fast-spinning motors, and powerful push forces. Following these rules protects you, your robot, and everyone nearby.

Read this entire file before powering on your robot for the first time.

---

## Rule 1 — LiPo Battery Safety

The 11.1V (3-cell) LiPo battery included in this kit is a lithium polymer chemistry battery. LiPo batteries provide high power but require careful handling.

### Charging
- **Use only a LiPo-compatible balance charger.** Never charge a LiPo battery with a regular charger, phone charger, or any charger not rated for LiPo chemistry.
- **Balance charge whenever possible.** A balance charger monitors and equalizes the voltage of each cell, extending battery life and preventing dangerous overcharge.
- **Never leave a charging LiPo unattended.** Stay nearby while charging.
- **Charge at the correct voltage and current.** For a 3S (11.1V) LiPo, charge to 4.2V per cell (12.6V total). Do not exceed this.
- **Charge on a fireproof surface.** Use a LiPo charging bag or charge on a ceramic tile, concrete floor, or metal surface — never on a wooden desk or fabric surface.

### Storage
- **Do not store at full charge.** For long-term storage (more than a few days without use), charge or discharge the battery to **storage voltage (~3.8V per cell / ~11.4V total)**. Many LiPo chargers have a "Storage" mode.
- **Do not store in a hot environment.** Avoid direct sunlight, hot cars, or enclosed spaces with no ventilation.
- **Store in a LiPo-safe bag or metal container.**

### Discharge
- **Never over-discharge a LiPo.** Discharge below 3.0V per cell (9.0V total for 3S) permanently damages the battery and creates a fire/explosion risk.
- **Use a low-voltage alarm or cutoff if available.** Some motor controllers have a low-voltage cutoff — the URC10 does not have this built in, so monitor battery voltage manually during long test sessions.

### Damage
- **Inspect the battery before every use.** Do not use a LiPo battery that is:
  - Swollen or puffy (thermal runaway risk)
  - Damaged, punctured, or has frayed wires
  - Emitting an unusual chemical smell
- **A swollen LiPo must be disposed of safely.** Do not use it. Take it to an electronics recycling facility or a hobby shop that accepts LiPo disposal.

### Fire Emergency
- If a LiPo battery catches fire or starts venting white smoke:
  - Do **not** use water — LiPo fires react violently with water
  - Use a dry powder or CO₂ fire extinguisher
  - Move the battery outdoors if safe to do so
  - Call emergency services if the fire is not immediately controllable

---

## Rule 2 — Reverse Polarity Warning

> ⚠️ **CRITICAL: Connecting the battery in reverse polarity will permanently destroy the URC10 board — instantly, with no possibility of repair.**

### How to Avoid This

- Always identify the **positive (+)** and **negative (–)** terminals before connecting
- The URC10 power input terminal is labeled **VM** (positive) and **GND** (negative)
- The Dean T connector is polarized — it should only fit one way. If it does not connect smoothly, **do not force it**
- If you use a multimeter: red probe on VM terminal, black probe on GND. It should read positive voltage (e.g., +11.1V). If it reads negative, the polarity is reversed.

### What Happens If You Reverse It
- The URC10 board will be permanently damaged
- The battery may also be damaged
- There is a risk of fire or smoke from a short circuit
- The motor driver, microcontroller, and onboard components will all be destroyed

---

## Rule 3 — Lift Wheels During Motor Testing

> ⚠️ **Every time you upload new code and test motors, lift the robot's wheels completely off the ground first.**

### Why
- If a motor direction is reversed in code, the robot will drive in an unexpected direction — potentially off a table, into a wall, or into a person
- Autonomous robots move immediately on button press — there is no time to react if the robot goes the wrong way
- Testing with wheels off the ground confirms motor direction, speed, and behavior safely before placing the robot on the floor

### How
- Hold the robot in the air, or prop it up on a box or stand so all wheels can spin freely
- Only place the robot on the floor once you have confirmed:
  - Both motors spin in the correct direction
  - The robot drives straight forward (not in a curve) when commanded
  - The IR Sumo Start module gives a RUN signal and the robot starts
  - The STOP signal stops the robot immediately

---

## Rule 4 — Sharp Front Blade / Scoop Warning

> ⚠️ **The front blade attached to this robot is a sharpened metal part. It can cause cuts or injuries if handled carelessly.**

### During Assembly
- Handle the blade by the back edge or the mounting holes — not the sharpened front edge
- Use gloves if available when handling or adjusting the blade
- Tighten all mounting screws fully — a loose blade that detaches during a match is a safety hazard

### During Use
- Do not allow anyone to put their hands or fingers near the front of the robot while it is powered and autonomous mode is active
- The robot can move suddenly without warning after button press — keep all hands clear
- Transport the assembled robot with the blade covered or protected (a cardboard sleeve works)

### During Competition
- Follow all competition safety rules regarding blade dimensions and height
- Ensure the blade cannot be deployed as a weapon beyond the competition specifications

---

## Rule 5 — Do Not Test at Full Speed Immediately

> ⚠️ **Do not run the robot at full speed (setSpeed(255)) during your first test. Always start at low speed.**

### Why
- If motor direction is wrong, a low-speed error is easy to catch. A full-speed error can damage the robot, the environment, or injure someone.
- At full speed, the robot can travel across a table in under 0.5 seconds.
- High current draw at full speed can reveal wiring faults that cause sparks or heat.

### Recommended First Test Sequence
1. Start with speed `100` (about 40% power)
2. Confirm all motors spin in the correct direction
3. Confirm the robot drives straight forward and turns as expected
4. Gradually increase to `200` (about 80% power)
5. Confirm behavior is still correct
6. Only then test at `255` (full power)

---

## Rule 6 — Never Run the Robot Unattended

- Do not leave a powered autonomous robot unattended
- The robot will start moving on button press — ensure all observers are clear of the robot's path
- After testing, power off the robot fully and disconnect the battery if leaving the area

---

## Rule 7 — Safe Working Environment

- **Clear the floor** of obstacles before floor testing — cables, power strips, and feet should all be clear of the robot's path
- **Test in a bounded area** — use the competition ring, or surround the test area with cardboard walls to contain the robot
- **Disconnect battery when wiring** — never adjust wiring or plug in sensors while the battery is connected

---

## Rule 8 — IR Sumo Start Module Safety

The **Cytron IR Sumo Start Module** is the standard start method for Auto Kit Mode competitions.
It allows the judge to start and stop all robots simultaneously via an IR remote control.

### Why This Improves Safety

- **Wireless stop control:** If a robot malfunctions or escapes the ring, the judge can send an immediate STOP signal without needing to physically touch the robot.
- **Synchronized start:** All robots on the ring start at exactly the same time, eliminating false starts.
- **No physical contact with running robot:** The robot does not need to be touched to stop it during a match.

### Code Requirement

The robot **must** stop all motors immediately when the IR signal goes LOW (STOP). This is not optional — it is a safety and competition rule.

The `08-auto-kit-standard.ino` code checks the IR signal at the **top of every loop iteration**:
```cpp
if (!irRunSignalActive()) {
  stopMotors();   // Halt immediately on STOP signal
  while (1);      // Stay stopped until reset
}
```

> ⚠️ **Never remove or bypass the IR STOP check from the code.** Doing so means the robot cannot be stopped wirelessly during a match, which is a competition rules violation and a safety hazard.

### Mounting Requirement

The IR Sumo Start module must have a clear, unobstructed line of sight to the judge's transmitter.
- Do not mount it inside the chassis body or behind the front blade
- Mount it on top, front, or side of the robot where the receiver window faces outward
- Test the stop/start function from competition distance before the match begins

### No Module? — Testing Fallback Only

If you do not have an IR Sumo Start module, you can use a physical button on D2 for **bench testing only**.
Change `INPUT` to `INPUT_PULLUP` in code and invert the start logic.
Do not use a physical button in a competition that requires the IR Sumo Start module.

---

## Summary Checklist — Before Every Power-On

- [ ] Battery is charged and not swollen
- [ ] Battery polarity verified (VM = +, GND = –) before connecting
- [ ] Wheels lifted off the ground
- [ ] Test speed set to low (not 255) for first test
- [ ] All people and hands clear of the front blade
- [ ] No cables or obstacles in the robot's path
- [ ] Power switch is accessible for emergency off
- [ ] IR Sumo Start module is connected: + to 5V, − to GND, S to D2
- [ ] IR Sumo Start module has clear line of sight to judge's transmitter
- [ ] STOP signal test: send STOP, confirm robot halts before placing on ring
