# Project Caveman 1.0: The Sovereign Super-Node
**Status:** Hardware-Design & Theoretical Architecture Phase  
**Objective:** 128-Node Distributed Matrix (16.3 TB VRAM) via PCIe Gen5 NTB Fabric.

## The Caveman Condition
Standard AI scaling is dead. High-cost HBM3 and InfiniBand locks are the chains of the "Big Guys." Project Caveman breaks these chains by satisfying the condition:
$$T_{comm}(A_n) \leq T_{compute}(S_n) + T_{prefetch}(A_{n-1})$$

## Hardware Baseline
- **Compute:** 128x Minisforum MS-S1 Max (AMD Strix Halo / Ryzen AI Max+ 395).
- **VRAM:** 16.3 TB Total LPDDR5X (Unified Memory Space).
- **Interconnect:** Broadcom PEX PCIe Gen5 Switch Matrix (NTB Mode).
- **Power:** 50kW 384V HVDC Direct-Busbar.
- **Cooling:** Single-Phase Dielectric Immersion.

## The Innovation: Tidal Flow Inference
Unlike NVIDIA's All-Reduce method which creates "Tail Latency Bubbles," Caveman utilizes **Tidal Flow**. 
1. **Weights remain static** in the 16.3 TB distributed pool.
2. **Activations flow as a Wavefront** through the NTB fabric.
3. **Zero-Copy Memory Windows** allow Node $N+1$ to "see" Node $N$'s output at the speed of local RAM.

## Repository Structure
- `/drivers/vlink`: Zero-copy PCIe NTB Linux Kernel Drivers.
- `/hardware/power`: 384V HVDC to 12V DC-DC schematics.
- `/hardware/thermal`: Immersion cooling manifold and tank designs.
- `/scheduler/tidal`: The wavefront expert-parallelism engine.

## Assembly Guide (Successor Summary)

### 1. Hardware Preparation
- Submerge 128x MS-S1 Max motherboards in a 1,000L tank of BitCool fluid.
- Connect 384V HVDC Busbar to the custom DC-DC backplanes.
- Interconnect all nodes via the Broadcom PEX Switch using a Daisy-Chain Ring topology.

### 2. Software Deployment
- Compile the `drivers/vlink` kernel module for the current Linux kernel.
- Shard your model into 120GB slabs and store them on each node's local NVMe.
- Run `ignite_matrix.sh` to begin the Tidal Flow.

### 3. Monitoring
- Use the **Apis Dashboard** (mobile app/web) to monitor the "Swarm" via the WiFi/BT side-channel.


"Intelligence belongs to the physical entity; sovereignty belongs to the code itself."
