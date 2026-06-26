# Start Here — Using This Pack with an AI Coding Assistant

This guide explains **how to get the most out of this Cytron AI Coding Pack** when using Antigravity (or any AI coding assistant).

---

## Step 1: Complete the Official Tutorial First

Before using this pack, make sure you have:

- [x] Installed the **Arduino IDE**
- [x] Installed the **CH340 USB driver**
- [x] Installed the **Cytron Motor Drivers Library**
- [x] Successfully **uploaded the sample code** to your URC10
- [x] Verified your robot responds to the start button

> If you have not done these steps yet, refer to `tutorial-summary.md` for a quick recap.

---

## Step 2: Open This Folder with Antigravity

1. Open **Antigravity** on your computer.
2. Open the **`cytron-ai-coding-pack-urc10/`** folder as your workspace.
3. The AI will automatically load all reference files in this pack as context.

The AI now knows:
- Your hardware (URC10 with ATmega328P)
- Your pin mapping
- Your motor library
- Your safety rules
- Your existing sample code logic

---

## Step 3: Ask the AI to Help You

Here are the types of things you can ask the AI to do:

### 🔍 Understand the Code
> *"Explain what the `attack()` function does in the sample code."*

### ✏️ Modify the Code
> *"Change the sumo robot so it searches clockwise first instead of left."*

### 🐛 Debug Your Code
> *"My robot keeps reversing off the ring even when the edge is not detected. What could be wrong?"*

### 🚀 Expand the Project
> *"Add a 5-second countdown using the onboard LEDs before the robot starts moving."*

### 🧪 Build a New Application
> *"Help me turn this sumo robot into a line-following robot using the edge sensors."*

> 💡 **Tip:** Ready-made prompts are available in the `ai-prompts/` folder. Just open them and paste into the AI chat.

---

## Step 4: Test Safely Before Running the Real Robot

- Always **lift the robot's wheels off the ground** when testing motor code for the first time.
- Start at **low speed** (e.g., `setSpeed(100)`) before testing at full speed.
- Do not run full-speed tests near edges of a table.
- Refer to `safety-rules.md` before every new test session.

---

## Folder Navigation

| File | What to Open First |
|---|---|
| `safety-rules.md` | Before every test session |
| `pin-map.md` | When wiring up sensors or motors |
| `library-reference.md` | When writing or modifying motor code |
| `code-examples/` | When you want a working starting point |
| `ai-prompts/` | When you want a quick AI task |
| `project-ideas.md` | When you want inspiration |
| `troubleshooting.md` | When something is not working |
