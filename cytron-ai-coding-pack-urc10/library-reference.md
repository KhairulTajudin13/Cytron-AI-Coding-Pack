# Library Reference — Cytron Motor Drivers Library

The URC10 uses the official **Cytron Motor Drivers Library** to control the onboard dual motor driver. This document explains how to install, set up, and use the library correctly.

---

## Installation

1. Open **Arduino IDE**.
2. Go to **Sketch → Include Library → Manage Libraries...**
3. Search for: `Cytron Motor Drivers`
4. Install **"Cytron Motor Drivers Library"** by Cytron Technologies.

---

## Import Statement

Add this at the top of every sketch that drives the motors:

```cpp
#include <CytronMotorDriver.h>
```

---

## Motor Object Declaration

Declare motor objects **globally** (outside any function), using the `PWM_DIR` control mode and the correct URC10 pins:

```cpp
// Motor Left:  PWM on D5, DIR on D4
// Motor Right: PWM on D6, DIR on D7
CytronMD motorL(PWM_DIR, 5, 4);
CytronMD motorR(PWM_DIR, 6, 7);
```

> ⚠️ These pin numbers match the URC10's internal wiring. Do not change them unless you have modified the hardware.

**Constructor syntax:**
```cpp
CytronMD motorName(PWM_DIR, pwmPin, dirPin);
```

| Parameter | Description |
|---|---|
| `PWM_DIR` | Control mode used by URC10 |
| `pwmPin` | PWM speed pin |
| `dirPin` | Direction pin |

---

## Setting Motor Speed

Use `setSpeed()` to control speed and direction:

```cpp
motorL.setSpeed(speed);
motorR.setSpeed(speed);
```

| Value | Effect |
|---|---|
| `255` | Full speed forward |
| `100` | Partial speed forward |
| `0` | Stop |
| `-100` | Partial speed reverse |
| `-255` | Full speed reverse |

**Range:** `-255` to `255`

---

## Common Usage Patterns

### Drive Forward at Full Speed
```cpp
motorL.setSpeed(255);
motorR.setSpeed(255);
```

### Drive Backward
```cpp
motorL.setSpeed(-255);
motorR.setSpeed(-255);
```

### Stop Both Motors
```cpp
motorL.setSpeed(0);
motorR.setSpeed(0);
```

### Turn Left (Spin in Place)
```cpp
motorL.setSpeed(-150);
motorR.setSpeed(150);
```

### Turn Right (Spin in Place)
```cpp
motorL.setSpeed(150);
motorR.setSpeed(-150);
```

### Gentle Curve Left (Arc)
```cpp
motorL.setSpeed(100);
motorR.setSpeed(255);
```

### Gentle Curve Right (Arc)
```cpp
motorL.setSpeed(255);
motorR.setSpeed(100);
```

---

## Setup in `setup()` Function

It is good practice to explicitly stop both motors at the start of `setup()`:

```cpp
void setup() {
  motorL.setSpeed(0);
  motorR.setSpeed(0);
  // ... rest of your setup code
}
```

---

## Notes and Limitations

- The library does **not** require `begin()` or `init()` — motor objects are ready as soon as they are declared.
- Only functions observed in the official sample code are documented here: **`setSpeed()`**.
- Do not use motor driver pins (D4, D5, D6, D7) for any other purpose — they are internally wired.
- Do not connect external loads directly to these pins.

---

*Library by Cytron Technologies | Available at: Arduino Library Manager | www.cytron.io*
