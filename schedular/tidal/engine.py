# Project Caveman: Tidal Flow Inference Engine
# Logic: Asynchronous Wavefront Propagation via NTB Doorbeling

import time
import numpy as np

class TidalNode:
    def __init__(self, node_id, local_weights):
        self.node_id = node_id
        self.weights = local_weights # Already resident in LPDDR5X
        self.in_window = self.map_ntb_window(node_id - 1) # Peer Memory
        self.out_window = self.map_ntb_window(node_id + 1) # Peer Memory

    def map_ntb_window(self, peer_id):
        # Maps the /dev/caveman_vlink BAR into a numpy-accessible buffer
        # This is a zero-copy mapping to the remote node's RAM
        return np.memmap(f'/dev/vlink{peer_id}', dtype='float16', mode='w+', shape=(4096, 12288))

    def wait_for_wavefront(self):
        # The Doorbell: We poll a single memory address. 
        # No CPU interrupts. Low-latency spinning.
        while self.in_window[0, 0] == 0: 
            pass # Spinning until Node N-1 writes the 'Go' signal
        return self.in_window[1:] # The actual activation tensor

    def push_wavefront(self, activation):
        # Write results directly to Node N+1's memory
        self.out_window[1:] = activation
        self.out_window[0, 0] = 1 # Ring the Doorbell for the next node
        
        # Reset local doorbell for the next token
        self.in_window[0, 0] = 0

    def compute_cycle(self):
        while True:
            # 1. Wait for input activation from previous node
            x = self.wait_for_wavefront()
            
            # 2. Compute locally on Strix Halo NPU
            # T_compute starts here
            y = self.npu_compute(x, self.weights)
            
            # 3. Push to next node (T_comm happens here)
            # Because of NTB, T_comm is just a memory write.
            self.push_wavefront(y)

# THE CAVE MAN CONDITION CHECK:
# If NPU_Compute(Layer_N) takes 2ms, and NTB_Write takes 0.1ms,
# the cluster never stalls. The wave moves at the speed of the slowest NPU.
