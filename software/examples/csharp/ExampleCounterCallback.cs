using System;
using Tinkerforge;

class Example
{
	private static string HOST = "localhost";
	private static int PORT = 4223;
	private static string UID = "XYZ"; // Change XYZ to the UID of your Hall Effect Bricklet 2.0

	// Callback function for counter callback
	static void CounterCB(BrickletHallEffectV2 sender, long counter)
	{
		Console.WriteLine("Counter: " + counter);
	}

	static void Main()
	{
		IPConnection ipcon = new IPConnection(); // Create IP connection
		BrickletHallEffectV2 he = new BrickletHallEffectV2(UID, ipcon); // Create device object

		ipcon.Connect(HOST, PORT); // Connect to brickd
		// Don't use device before ipcon is connected

		// Configure counter with ±3000µT threshold and 10ms debounce
		he.SetCounterConfig(3000, -3000, 10000);

		// Register counter callback to function CounterCB
		he.CounterCallback += CounterCB;

		// Set period for counter callback to 0.1s (100ms)
		he.SetCounterCallbackConfiguration(100, true);

		Console.WriteLine("Press enter to exit");
		Console.ReadLine();
		ipcon.Disconnect();
	}
}
