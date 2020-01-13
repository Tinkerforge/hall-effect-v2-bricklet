#!/usr/bin/env python
# -*- coding: utf-8 -*-

HOST = "localhost"
PORT = 4223
UID = "XYZ" # Change XYZ to the UID of your Hall Effect Bricklet 2.0

from tinkerforge.ip_connection import IPConnection
from tinkerforge.bricklet_hall_effect_v2 import BrickletHallEffectV2

# Callback function for counter callback
def cb_counter(counter):
    print("Counter: " + str(counter))

if __name__ == "__main__":
    ipcon = IPConnection() # Create IP connection
    he = BrickletHallEffectV2(UID, ipcon) # Create device object

    ipcon.connect(HOST, PORT) # Connect to brickd
    # Don't use device before ipcon is connected

    # Configure counter with ±3000µT threshold and 10ms debounce
    he.set_counter_config(3000, -3000, 10000)

    # Register counter callback to function cb_counter
    he.register_callback(he.CALLBACK_COUNTER, cb_counter)

    # Set period for counter callback to 0.1s (100ms)
    he.set_counter_callback_configuration(100, True)

    input("Press key to exit\n") # Use raw_input() in Python 2
    ipcon.disconnect()
