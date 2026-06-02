#!/bin/bash
# Project Caveman 1.0: Master Ignition Sequence
# This script brings the 128-node matrix from Cold-Iron to Tidal-Flow.

echo "--- PROJECT CAVEMAN 1.0: IGNITION ---"

# 1. Apis Protocol Discovery (The Bees)
echo "[1/5] Initializing Apis Protocol (WiFi/BT Side-Channel)..."
python3 ../runtime/apis_heartbeat.py --mode=discover

# 2. Kernel Ignition
echo "[2/5] Loading VLink Zero-Copy Drivers on all nodes..."
# Distribute the kernel module to the 128-node matrix
for node in {0..127}; do
    ssh node_$node "insmod /lib/modules/caveman_vlink.ko"
done

# 3. Shatter-Load (The Ingest)
echo "[3/5] Triggering Shatter-Load: NVMe -> LPDDR5X (16.3 TB Ingest)..."
python3 ../runtime/shatter_load.py

# 4. Hydra Ingress Activation
echo "[4/5] Opening Hydra Ingress Heads..."
python3 ../runtime/hydra_ingest.py --heads=0,16,32,48,64,80,96,112

# 5. Tidal Wave Commencement
echo "[5/5] Commencing Tidal Flow Inference..."
./../schedular/tidal/engine_binary --start

echo "--- MATRIX IS LIVE ---"
