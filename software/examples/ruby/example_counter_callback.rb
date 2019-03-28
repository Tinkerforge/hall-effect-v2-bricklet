#!/usr/bin/env ruby
# -*- ruby encoding: utf-8 -*-

require 'tinkerforge/ip_connection'
require 'tinkerforge/bricklet_hall_effect_v2'

include Tinkerforge

HOST = 'localhost'
PORT = 4223
UID = 'XYZ' # Change XYZ to the UID of your Hall Effect Bricklet 2.0

ipcon = IPConnection.new # Create IP connection
he = BrickletHallEffectV2.new UID, ipcon # Create device object

ipcon.connect HOST, PORT # Connect to brickd
# Don't use device before ipcon is connected

# Configure counter with ±3000µT threshold and 10ms debounce
he.set_counter_config 3000, -3000, 10000

# Register counter callback
he.register_callback(BrickletHallEffectV2::CALLBACK_COUNTER) do |counter|
  puts "Counter: #{counter}"
end

# Set period for counter callback to 0.1s (100ms)
he.set_counter_callback_configuration 100, true

puts 'Press key to exit'
$stdin.gets
ipcon.disconnect
