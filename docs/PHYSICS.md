# Engineering Physics: Power and Thermal Management

## 1. 384V HVDC Implementation
To eliminate I2R losses and PSU bulk, Caveman 1.0 utilizes an **OCP-standard 384V DC Busbar**.
- **Conversion Efficiency:** 98.5% (Eliminating AC-to-DC internal node transformers).
- **Node Delivery:** Each MS-S1 cluster uses a custom DC-DC Buck-Converter plate to step 384V down to 12V/5V at the point of load.
- **Safety:** Independent optical isolation for each 32-node rack segment.

## 2. Dielectric Immersion Cooling
Air-cooling 128 NPUs at full load is physically impossible in a standard room.
- **Fluid:** BitCool or ElectroCool (Single-Phase Dielectric).
- **Mechanism:** Nodes are stripped of fans and submerged in a reinforced HDPE tank.
- **Heat Rejection:** A 60kW plate heat exchanger connected to an external dry-cooler.
- **Overclocking:** Immersion allows the AMD Strix Halo to run at 120W+ peak TDP with 0% thermal throttling, as delta-T is maintained <15°C across the board.

## 3. Aggregate Bandwidth
- **Per Node:** ~500 GB/s (LPDDR5X).
- **Cluster Total:** 128 * 500 GB/s = **64,000 GB/s (64 TB/s) Aggregate Bandwidth.**
- This exceeds the memory bandwidth of a 64-GPU H100 cluster by 4.5x, at a fraction of the cost.
