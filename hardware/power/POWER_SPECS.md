# Technical Specification: 50kW 384V HVDC Direct-Busbar System

## 1. Overview
Project Caveman 1.0 rejects the inefficiency of 12V/48V AC-DC distribution. To sustain 128x Strix Halo nodes at peak TFLOPS, we utilize a 384V HVDC (High Voltage Direct Current) busbar architecture. This reduces copper weight by 8x and eliminates multiple conversion stages.

## 2. Electrical Characteristics
- **Input:** 3-Phase 480V AC (Industrial Grade).
- **Rectification:** Dual-active bridge (DAB) converters yielding a stabilized 384V DC rail.
- **Busbar Material:** C11000 Oxygen-Free Copper (OFC), 5mm x 50mm cross-section.
- **Current Density:** Maintained at < 2A/mm² for passive thermal stability.

## 3. Point-of-Load (PoL) Conversion
Each MS-S1 Max blade is modified with a custom GaN (Gallium Nitride) Buck stage:
- **Input:** 384V DC.
- **Output:** 12V DC (Intermediate) and 0.8V - 1.2V (Vcore/VDD_MEM).
- **Efficiency:** η = 96.4% at full load (500W per blade).
- **Switching Frequency:** 1.2 MHz (to minimize EMI footprint).

## 4. Safety and Grounding
- **Isolation:** Galvanic isolation between HVDC rail and logic circuits.
- **Grounding:** Star-point grounding to prevent ground loops across the 128-node fabric.
- **Protection:** 10ms Fast-Blow Solid State Circuit Breakers (SSCB) per 8-node cluster.

**WARNING:** 384V DC is lethal. Ensure the air-gap interlock is active before servicing the busbar.
