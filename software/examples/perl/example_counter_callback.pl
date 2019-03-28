#!/usr/bin/perl

use strict;
use Tinkerforge::IPConnection;
use Tinkerforge::BrickletHallEffectV2;

use constant HOST => 'localhost';
use constant PORT => 4223;
use constant UID => 'XYZ'; # Change XYZ to the UID of your Hall Effect Bricklet 2.0

# Callback subroutine for counter callback
sub cb_counter
{
    my ($counter) = @_;

    print "Counter: $counter\n";
}

my $ipcon = Tinkerforge::IPConnection->new(); # Create IP connection
my $he = Tinkerforge::BrickletHallEffectV2->new(&UID, $ipcon); # Create device object

$ipcon->connect(&HOST, &PORT); # Connect to brickd
# Don't use device before ipcon is connected

# Configure counter with ±3000µT threshold and 10ms debounce
$he->set_counter_config(3000, -3000, 10000);

# Register counter callback to subroutine cb_counter
$he->register_callback($he->CALLBACK_COUNTER, 'cb_counter');

# Set period for counter callback to 0.1s (100ms)
$he->set_counter_callback_configuration(100, 1);

print "Press key to exit\n";
<STDIN>;
$ipcon->disconnect();
