/*
 * Caveman: Asynchronous Stepping Engine
 * This prevents the "All-Reduce" lock.
 */

#include <stdio.h>
#include <stdatomic.h>

typedef struct {
    atomic_int doorbell;
    float activation_data[4096 * 12288]; 
} CavemanWindow;

void process_stepping_chain(CavemanWindow *in_mw, CavemanWindow *out_mw, float *weights) {
    while(1) {
        // 1. ASYNCHRONOUS WAIT
        // We don't call a 'sync' function. We spin on the hardware atomic.
        while (atomic_load(&in_mw->doorbell) == 0) {
            // Low-power 'hint' to the CPU while spinning
            __builtin_ia32_pause(); 
        }

        // 2. COMPUTE PHASE (T_compute)
        // Immediately start NPU execution as soon as the first byte arrives.
        // We use 'Stepping' to overlap the next node's transfer with this math.
        npu_compute_async(in_mw->activation_data, weights, out_mw->activation_data);

        // 3. ASYNCHRONOUS STEP
        // Clear our doorbell and ring the next one.
        atomic_store(&in_mw->doorbell, 0);
        atomic_store(&out_mw->doorbell, 1);
        
        // This node is now ready for the NEXT token while the 
        // next node is still calculating the current one.
    }
}
