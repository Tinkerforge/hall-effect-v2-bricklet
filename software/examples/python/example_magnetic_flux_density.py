#!/usr/bin/env python
# -*- coding: utf-8 -*-

HOST = "localhost"
PORT = 4223
UID = "XYZ" # Change XYZ to the UID of your Hall Effect Bricklet 2.0

from tinkerforge.ip_connection import IPConnection
from tinkerforge.bricklet_hall_effect_v2 import BrickletHallEffectV2

if __name__ == "__main__":
    ipcon = IPConnection() # Create IP connection
    he = BrickletHallEffectV2(UID, ipcon) # Create device object

    ipcon.connect(HOST, PORT) # Connect to brickd
    # Don't use device before ipcon is connected

    # Get current Magnetic Flux Density
    magnetic_flux_density = he.get_magnetic_flux_density()
    print("Magnetic Flux Density: " + str(magnetic_flux_density) + " µT")

    raw_input("Press key to exit\n") # Use input() in Python 3
    ipcon.disconnect()
