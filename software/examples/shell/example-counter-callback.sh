#!/bin/sh
# Connects to localhost:4223 by default, use --host and --port to change this

uid=XYZ # Change XYZ to the UID of your Hall Effect Bricklet 2.0

# Configure counter with ±3000µT threshold and 10ms debounce
tinkerforge call hall-effect-v2-bricklet $uid set-counter-config 3000 -3000 10000

# Handle incoming counter callbacks
tinkerforge dispatch hall-effect-v2-bricklet $uid counter &

# Set period for counter callback to 0.1s (100ms)
tinkerforge call hall-effect-v2-bricklet $uid set-counter-callback-configuration 100 true

echo "Press key to exit"; read dummy

kill -- -$$ # Stop callback dispatch in background
