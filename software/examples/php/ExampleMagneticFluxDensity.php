<?php

require_once('Tinkerforge/IPConnection.php');
require_once('Tinkerforge/BrickletHallEffectV2.php');

use Tinkerforge\IPConnection;
use Tinkerforge\BrickletHallEffectV2;

const HOST = 'localhost';
const PORT = 4223;
const UID = 'XYZ'; // Change XYZ to the UID of your Hall Effect Bricklet 2.0

$ipcon = new IPConnection(); // Create IP connection
$he = new BrickletHallEffectV2(UID, $ipcon); // Create device object

$ipcon->connect(HOST, PORT); // Connect to brickd
// Don't use device before ipcon is connected

// Get current Magnetic Flux Density
$magnetic_flux_density = $he->getMagneticFluxDensity();
echo "Magnetic Flux Density: $magnetic_flux_density µT\n";

echo "Press key to exit\n";
fgetc(fopen('php://stdin', 'r'));
$ipcon->disconnect();

?>
