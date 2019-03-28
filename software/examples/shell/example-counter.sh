#!/bin/sh
# Connects to localhost:4223 by default, use --host and --port to change this

uid=XYZ # Change XYZ to the UID of your Hall Effect Bricklet 2.0

# Get current count without counter reset
tinkerforge call hall-effect-v2-bricklet $uid get-counter false
