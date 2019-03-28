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
        // Get current Magnetic Flux Density
        he.getMagneticFluxDensity(
            function (magneticFluxDensity) {
                console.log('Magnetic Flux Density: ' + magneticFluxDensity + ' µT');
            },
            function (error) {
                console.log('Error: ' + error);
            }
        );
    }
);

console.log('Press key to exit');
process.stdin.on('data',
    function (data) {
        ipcon.disconnect();
        process.exit(0);
    }
);
