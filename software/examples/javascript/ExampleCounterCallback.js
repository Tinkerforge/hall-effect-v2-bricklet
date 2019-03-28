var Tinkerforge = require('tinkerforge');

var HOST = 'localhost';
var PORT = 4223;
var UID = 'XYZ'; // Change XYZ to the UID of your Hall Effect Bricklet 2.0

var ipcon = new Tinkerforge.IPConnection(); // Create IP connection
var he = new Tinkerforge.BrickletHallEffectV2(UID, ipcon); // Create device object

ipcon.connect(HOST, PORT,
    function (error) {
        console.log('Error: ' + error);
    }
); // Connect to brickd
// Don't use device before ipcon is connected

ipcon.on(Tinkerforge.IPConnection.CALLBACK_CONNECTED,
    function (connectReason) {
        // Configure counter with ±3000µT threshold and 10ms debounce
        he.setCounterConfig(3000, -3000, 10000);

        // Set period for counter callback to 0.1s (100ms)
        he.setCounterCallbackConfiguration(100, true);
    }
);

// Register counter callback
he.on(Tinkerforge.BrickletHallEffectV2.CALLBACK_COUNTER,
    // Callback function for counter callback
    function (counter) {
        console.log('Counter: ' + counter);
    }
);

console.log('Press key to exit');
process.stdin.on('data',
    function (data) {
        ipcon.disconnect();
        process.exit(0);
    }
);
