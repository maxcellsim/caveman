import smbus2 # Accessing the I2C/PMBus directly

BUS_VOLTAGE_TARGET = 384.0
MAX_AMP_PER_NODE = 4.2 # ~500W per Strix Halo node max load

def check_thermal_and_power():
    # Read from the HVDC Busbar Controller
    bus_v = read_pmbus_voltage(0x58) 
    
    if bus_v > 400.0 or bus_v < 360.0:
        emergency_shutdown("VOLTAGE_INSTABILITY_DETECTED")
        
    # Check the 128 nodes via the management backplane
    for node_id in range(128):
        temp = get_node_temp(node_id)
        if temp > 95: # Celsius
            throttle_node(node_id)
            print(f"CRITICAL: Node {node_id} overheating. Backing off.")

# This runs in a 10ms loop on the Master Controller (Node 0)
