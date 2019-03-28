import com.tinkerforge.IPConnection;
import com.tinkerforge.BrickletHallEffectV2;

public class ExampleCounterCallback {
	private static final String HOST = "localhost";
	private static final int PORT = 4223;

	// Change XYZ to the UID of your Hall Effect Bricklet 2.0
	private static final String UID = "XYZ";

	// Note: To make the example code cleaner we do not handle exceptions. Exceptions
	//       you might normally want to catch are described in the documentation
	public static void main(String args[]) throws Exception {
		IPConnection ipcon = new IPConnection(); // Create IP connection
		BrickletHallEffectV2 he = new BrickletHallEffectV2(UID, ipcon); // Create device object

		ipcon.connect(HOST, PORT); // Connect to brickd
		// Don't use device before ipcon is connected

		// Configure counter with ±3000µT threshold and 10ms debounce
		he.setCounterConfig(3000, -3000, 10000);

		// Add counter listener
		he.addCounterListener(new BrickletHallEffectV2.CounterListener() {
			public void counter(int counter) {
				System.out.println("Counter: " + counter);
			}
		});

		// Set period for counter callback to 0.1s (100ms)
		he.setCounterCallbackConfiguration(100, true);

		System.out.println("Press key to exit"); System.in.read();
		ipcon.disconnect();
	}
}
