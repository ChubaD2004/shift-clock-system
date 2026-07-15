# Shift-Clock System

An autonomous, bare-metal AVR-based digital clock showing time in a specific `HH.M` format on a 3-digit 7-segment common-anode display, driven by an SN74HC595N shift register.

## Project Goal
To display hours and tens of minutes in the `HH.M` format (e.g., `15:54` is shown as `15.5`).
- **Left digit:** Tens of hours.
- **Middle digit:** Units of hours + Decimal Point (always ON to separate hours and minutes).
- **Right digit:** Tens of minutes.

## Core Architectural Principles
1. **Serial-to-Parallel:** Minimizing pin count. A 74HC595 shift register controls 8 segments using only 3 MCU pins (DS, SHCP, STCP).
2. **Hybrid Multiplexing:**
   - **Cathodes (Segments):** Driven by the shift register (Active-LOW: `0` = Segment ON).
   - **Anodes (Digits):** Driven directly by ATmega328P GPIO pins (Active-HIGH: `1` = Digit ON).
3. **Non-blocking Design:** Entire multiplexing and timekeeping logic runs inside the ATmega328P `Timer1` Interrupt Service Routine (ISR) to ensure precise timing and zero-jitter display updates.
4. **No Arduino HAL:** Developed in pure bare-metal C++ using direct register access (DDR, PORT, PIN, Timer registers) for maximum performance and educational value.

---

## Hardware Stack

| Component | Part/Specification | Description |
|---|---|---|
| **MCU** | ATmega328P (Arduino Uno board) | Main controller |
| **Shift Register** | SN74HC595N (Texas Instruments) | Serial-to-parallel converter for segments |
| **Display** | GNT-5631BUE | 3-digit, 7-segment, Common Anode display |
| **Resistors** | Various values | Current limiting for LED segments |
| **Debug Tools** | 8CH 24MHz Logic Analyzer | Signal tracing (PulseView/Sigrok) & UART debugging |

---

## Roadmap

### Stage 1: The Serial Bridge ⛓️
*Pushing data through the 74HC595 shift register.*
- [x] **Step 1.1:** 74HC595 theory & timing — DS (Data), SHCP (Clock), STCP (Latch)
- [x] **Step 1.2:** Segment Lookup Table for Common Anode (inverted logic: `0` = ON)
- [x] **Step 1.3:** `shift_out.cpp` driver development (byte transmission function)

### Stage 2: 3-Digit Multiplexing 💓
*Achieving a stable, flicker-free display using Timer ISR.*
- [ ] **Step 2.1:** Hardware wiring of the 12-pin display to the shift register & MCU
- [ ] **Step 2.2:** Timer1 ISR multiplexing: cyclic anode switching (0 -> 1 -> 2 -> 0)
- [ ] **Step 2.3:** Test: static output of a preset value (e.g., "12.3")

### Stage 3: Time Engine 🕒
*Precise timekeeping and time formatting.*
- [ ] **Step 3.1:** Formatting math to translate raw seconds (`uint32_t`) into `HH.M` format
- [ ] **Step 3.2:** Software long-term clock engine inside the Timer ISR
- [ ] **Step 3.3:** Decimal Point (DP) bit manipulation in the output byte stream

### Stage 4: Finalization 🚀
- [ ] **Step 4.1:** Complete system schematic in KiCad
- [ ] **Step 4.2:** Long-term test run of the autonomous clock