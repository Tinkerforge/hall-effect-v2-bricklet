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

	// Get current count without counter reset.
	count, _ := he.GetCounter(false)
	fmt.Printf("Count: %d\n", count)

	fmt.Print("Press enter to exit.")
	fmt.Scanln()
}
