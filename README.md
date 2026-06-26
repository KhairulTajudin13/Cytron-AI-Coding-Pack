# Cytron AI Coding Pack

This repository contains the pilot version of the **Cytron AI Coding Pack**.

The purpose of this project is to help users continue learning after completing a Cytron tutorial. Instead of only following a basic getting-started guide, users can open this pack in an AI coding tool such as **Antigravity** and ask AI to explain, modify, debug, or expand the project based on Cytron product guidance.

## Current Pilot Product

The current test product is:

**URC10 — Sumo Robot Controller**

This pack is designed to help users learn and experiment with URC10 safely while following the correct product context, pin mapping, library usage, and safety rules.

## What This Pack Helps With

Users can use this AI Coding Pack to:

* understand the original tutorial and sample code
* modify robot behavior
* debug motor or sensor issues
* learn how the code works
* build beginner-friendly project extensions
* avoid common mistakes such as wrong pins, wrong library, or unsafe motor testing

## Important Note

This pack is **not meant to replace the original Cytron tutorial**.

Users should first complete the official tutorial, make sure the basic setup works, and only then use this AI Coding Pack to explore further with AI.

## How to Use

1. Click **Code → Download ZIP**
2. Extract the ZIP file
3. Open the extracted folder in **Antigravity**
4. Start a new chat
5. Use the prompts in `TESTER-GUIDE.md`
6. Record your feedback using `FEEDBACK-FORM.md`

## Recommended Testing Flow

Testers should check whether the AI can:

* identify the correct Cytron product
* use the correct programming platform
* follow the correct URC10 pin mapping
* use the correct Cytron motor driver library
* avoid unsafe hardware advice
* explain code clearly for beginners
* help users modify and debug the project

## Current Status

**MVP Ready — Autonomous + RC Internal Testing**

This version is ready for internal testing of both Autonomous Sumo and Radio Controlled paths, but is not considered "public ready" yet. To transition to public release, testers must confirm:
* They understand the difference between Autonomous, RC, and Hybrid modes.
* They don't accidentally connect the D3 IR sensor and the RC steering signal at the same time.
* The signal-loss failsafe works correctly (robot stops when transmitter is powered off).
* A beginner can successfully follow the RC test sequence without manual instruction.

## Folder Structure

```text
cytron-ai-coding-pack-urc10/
├── README.md
├── start-here.md
├── source-audit.md
├── product-context.md
├── tutorial-summary.md
├── hardware-setup.md
├── pin-map.md
├── library-reference.md
├── code-examples/
├── ai-prompts/
├── project-ideas.md
├── troubleshooting.md
├── safety-rules.md
├── rc-validation-checklist.md
├── rc-mode/
│   ├── rc-control-context.md
│   ├── rc-pin-map.md
│   ├── rc-safety-rules.md
│   ├── rc-troubleshooting.md
│   └── code-examples/
│       ├── 05-rc-receiver-test.ino
│       ├── 06-radio-controlled-drive.ino
│       └── 07-hybrid-rc-autonomous-mode.ino
└── .agents/
    └── skills/
        └── cytron-ai-coding-coach/
```

## Testing Goal

The main goal of this test is to answer one question:

> Can the AI Coach help a beginner understand, modify, debug, and expand a Cytron tutorial safely and accurately?

If the answer is yes, this concept can be expanded to other Cytron products and tutorials.
