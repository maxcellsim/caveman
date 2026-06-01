# Technical Specification: NTB Daisy-Chain and Executor Failover

## 1. Fabric Topology
The interconnect utilizes a **Broadcom PEX89144 (PCIe Gen5)** switch matrix. The 128 nodes are partitioned into 16 clusters of 8 nodes.

- **Primary Topology:** Daisy-Chain Ring (Node $n$ to $n+1$).
- **Interface:** Non-Transparent Bridging (NTB).
- **Link Speed:** 32 GT/s (PCIe Gen5 x16).

## 2. Stateless Executor Failover
Two **AMD Threadripper PRO 7995WX** units act as "Master Executors." 

### 2.1 The 10-Microsecond Takeover Logic
1. **Heartbeat:** Executor A and B exchange a 1MHz pulse over a dedicated NTB link.
2. **Detection:** If Executor A pulse drops for $>5\mu s$, Executor B triggers a Root Complex (RC) re-enumeration.
3. **Stateless Resumption:** Since weights are stored in the LPDDR5X of the Strix Halo nodes, Executor B only pulls the **Inference Instruction Pointer ($\mathcal{I}$)** and the **Activation Head Address** from the NTB-mirrored scratchpad.
4. **Resumption:** Wavefront propagation resumes in $<10\mu s$.

## 3. Daisy-Chain Router Mode (DCRM)
Each node's PCIe BAR (Base Address Register) is mapped into the memory space of the adjacent node.
- **Node $n$ Output Buffer** $\rightarrow$ **Node $n+1$ Input Buffer**.
- **DMA Engine:** Asynchronous DMA transfers are triggered via a hardware doorbell.
- **Congestion Control:** Weighted Round Robin (WRR) arbitration within the Broadcom PEX matrix prevents TLP (Transaction Layer Packet) starvation.
