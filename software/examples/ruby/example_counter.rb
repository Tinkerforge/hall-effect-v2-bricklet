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

# Get current count without counter reset
count = he.get_counter false
puts "Count: #{count}"

puts 'Press key to exit'
$stdin.gets
ipcon.disconnect
