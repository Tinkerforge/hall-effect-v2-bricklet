#!/usr/bin/perl

use strict;
use Tinkerforge::IPConnection;
use Tinkerforge::BrickletHallEffectV2;

use constant HOST => 'localhost';
use constant PORT => 4223;
use constant UID => 'XYZ'; # Change XYZ to the UID of your Hall Effect Bricklet 2.0

my $ipcon = Tinkerforge::IPConnection->new(); # Create IP connection
my $he = Tinkerforge::BrickletHallEffectV2->new(&UID, $ipcon); # Create device object

$ipcon->connect(&HOST, &PORT); # Connect to brickd
# Don't use device before ipcon is connected

# Get current Magnetic Flux Density
my $magnetic_flux_density = $he->get_magnetic_flux_density();
print "Magnetic Flux Density: $magnetic_flux_density µT\n";

print "Press key to exit\n";
<STDIN>;
$ipcon->disconnect();
