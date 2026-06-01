# Project Caveman 1.0: The 16.3TB Cognitive Fortress

> **"Intelligence belongs to the physical entity; sovereignty belongs to the code itself."**

Project Caveman 1.0 is a decentralized AI inference fabric designed to break the HBM-monopoly. By aggregating **128x Bare-form AMD Strix Halo nodes** via a Non-Transparent Bridging (NTB) PCIe Gen5 matrix, we achieve civilization-scale local inference without the "Silicon Rentier" tax.

## ⚡ The Core Breakthrough
- **Total VRAM:** 16,384 GB (16.3 TB) LPDDR5X.
- **Interconnect:** Asynchronous Daisy-Chain Router Mode (PCIe Gen5 NTB).
- **Cost Efficiency:** **$24.16 per GB** (vs. ~$350/GB on NVIDIA H200).
- **Paradigm:** Eliminates "All-Reduce" synchronization locks; hides communication latency behind compute wavefronts.

## 🛠 Hardware Architecture
| Component | Specification |
| :--- | :--- |
| **Compute** | 128x Minisforum MS-S1 Max (AMD Ryzen AI Max+ 395) |
| **Executor** | 2x AMD Threadripper PRO 7995WX (10μs Fail-safe) |
| **Fabric** | Broadcom PEX89000 Series PCIe Gen5 Matrix |
| **Power** | 50kW 384V HVDC Direct-Busbar |

## 📐 The Caveman Condition
We achieve zero-latency interconnect overhead by satisfying:
$$T_{comm}(A_n) \leq T_{compute}(S_{n}) + T_{prefetch}(A_{n-1})$$
By treating nodes as hardware routers, the "slow" PCIe bus becomes a continuous-flow pipeline for unquantized Llama-3 405B weights.

## 📂 Repository Structure
- `/hardware`: Chassis CAD, 384V HVDC schematics, and Megtron 7 backplane files.
- `/software`: NTB-Daisy-Chain drivers and Wavefront Pipelining engine.
- `/docs`: Full technical white paper and the Cognitive Autonomy Manifesto.

## ⚖️ Licensing
- **Hardware:** CERN-OHL-W-2.0 (Weakly Reciprocal)
- **Software:** GNU GPLv3
- **Weights:** CC-BY-NC-SA 4.0

---
**Operate at your own risk. This is a garage-scale operation. Sovereignty requires responsibility.**
