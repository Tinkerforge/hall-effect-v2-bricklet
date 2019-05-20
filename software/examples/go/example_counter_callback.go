package main

import (
	"fmt"
	"github.com/Tinkerforge/go-api-bindings/hall_effect_v2_bricklet"
	"github.com/Tinkerforge/go-api-bindings/ipconnection"
)

const ADDR string = "localhost:4223"
const UID string = "XYZ" // Change XYZ to the UID of your Hall Effect Bricklet 2.0.

func main() {
	ipcon := ipconnection.New()
	defer ipcon.Close()
	he, _ := hall_effect_v2_bricklet.New(UID, &ipcon) // Create device object.

	ipcon.Connect(ADDR) // Connect to brickd.
	defer ipcon.Disconnect()
	// Don't use device before ipcon is connected.

	// Configure counter with ±3000µT threshold and 10ms debounce
	he.SetCounterConfig(3000, -3000, 10000)

	he.RegisterCounterCallback(func(counter uint32) {
		fmt.Printf("Counter: %d\n", counter)
	})

	// Set period for counter callback to 0.1s (100ms).
	he.SetCounterCallbackConfiguration(100, true)

	fmt.Print("Press enter to exit.")
	fmt.Scanln()
}
