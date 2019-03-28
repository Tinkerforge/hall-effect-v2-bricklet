<?php

require_once('Tinkerforge/IPConnection.php');
require_once('Tinkerforge/BrickletHallEffectV2.php');

use Tinkerforge\IPConnection;
use Tinkerforge\BrickletHallEffectV2;

const HOST = 'localhost';
const PORT = 4223;
const UID = 'XYZ'; // Change XYZ to the UID of your Hall Effect Bricklet 2.0

// Callback function for counter callback
function cb_counter($counter)
{
    echo "Counter: $counter\n";
}

$ipcon = new IPConnection(); // Create IP connection
$he = new BrickletHallEffectV2(UID, $ipcon); // Create device object

$ipcon->connect(HOST, PORT); // Connect to brickd
// Don't use device before ipcon is connected

// Configure counter with ±3000µT threshold and 10ms debounce
$he->setCounterConfig(3000, -3000, 10000);

// Register counter callback to function cb_counter
$he->registerCallback(BrickletHallEffectV2::CALLBACK_COUNTER, 'cb_counter');

// Set period for counter callback to 0.1s (100ms)
$he->setCounterCallbackConfiguration(100, TRUE);

echo "Press ctrl+c to exit\n";
$ipcon->dispatchCallbacks(-1); // Dispatch callbacks forever

?>
