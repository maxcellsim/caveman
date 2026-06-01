# Mathematical Proof: Wavefront Dynamics and Latency Invisibility

## 1. The Failure of Bulk Synchronous Parallel (BSP)
Traditional distributed AI relies on the **BSP model**, where $N$ nodes must reach a synchronization barrier (All-Reduce) before proceeding to layer $L+1$. 

The global latency $L_{total}$ is defined by the "Slowest Member" rule:
$$L_{total} = \sum_{i=1}^{Layers} (\max(T_{compute, i}) + T_{sync, i})$$

As $N \to 128$, the probability of $T_{sync}$ being degraded by a single TLP (Transaction Layer Packet) retry or thermal throttle approaches 1.0, leading to "Tail Latency Collapse."

## 2. The Caveman Paradigm: Asynchronous Wavefront Propagation (AWP)
Project Caveman 1.0 treats the 128-node array as a **Spatial Pipelined Ring**. The model is partitioned into $K$ sequential slices $\{S_1, S_2, \dots, S_K\}$.

### 2.1 The Inequality of Invisibility
We define the **Caveman Condition** for zero-latency interconnect overhead. Let:
- $T_{compute}(S_n)$: Time to execute the tensor operations for slice $n$.
- $T_{comm}(A_n)$: Time to transfer activation tensor $A_n$ to Node $n+1$.
- $T_{prefetch}(W_n)$: Time to pull weights from local LPDDR5X into the Strix Halo APU cache.

For the interconnect to become "invisible," we must satisfy:
$$T_{comm}(A_n) \ll T_{compute}(S_n) + T_{prefetch}(W_{n+1})$$

### 2.2 Empirical Derivation (Llama-3 405B Baseline)
Given a 128-node cluster running Llama-3 405B (unquantized BF16):
- **Model Size per Node:** $\approx 3.16$ Billion Parameters.
- **Compute Load ($T_{comp}$):** To process one token, the node must perform $\approx 6.32$ GFLOPs of matmul operations. 
  - At 500 TFLOPS (Strix Halo peak), $T_{comp} \approx 12.64\mu s$.
- **Communication Load ($T_{comm}$):** The hidden dimension of Llama-3 405B is 16,384. At FP16, the activation vector $A_n$ is 32 KB.
  - Over PCIe Gen5 x16 (64 GB/s), $T_{comm} = \frac{32 \text{ KB}}{64 \text{ GB/s}} = 0.5\mu s$.

**Result:**
$$0.5\mu s \text{ (Comm)} \ll 12.64\mu s \text{ (Compute)}$$
The interconnect utilizes only **3.9%** of the available compute window. This provides a safety margin of over 20x for PCIe jitter and TLP overhead.

## 3. Eliminating Advanced Error Reporting (AER) Degradation
Traditional star topologies suffer from AER cascades when a single root complex manages 128 end-points. Project Caveman 1.0 utilizes **Localized AER Isolation**:

1. **NTB Segmentation:** Each PCIe link is a private electrical and logical domain between two Broadcom PEX ports.
2. **Stateless Forwarding:** Node $n$ performs a Peer-to-Peer (P2P) DMA write into the BAR (Base Address Register) of Node $n+1$.
3. **The Semaphore Doorbell:** Instead of a CPU interrupt (which incurs $>2\mu s$ of context-switch jitter), Node $n+1$ polls a cache-aligned "Doorbell" memory address. When the DMA engine of $n$ flips the bit, $n+1$ immediately begins execution.

## 4. Conclusion of Proof
By satisfying the Caveman Condition, we prove that **interconnect bandwidth is not the bottleneck** for unquantized 400B+ models, provided the weights are locally resident. The "HBM Wall" is a marketing construct; at the 128-node scale, LPDDR5X bandwidth is effectively aggregated into a 16.3 TB virtual pool with near-zero transit cost.
