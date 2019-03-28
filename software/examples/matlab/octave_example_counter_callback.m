function octave_example_counter_callback()
    more off;

    HOST = "localhost";
    PORT = 4223;
    UID = "XYZ"; % Change XYZ to the UID of your Hall Effect Bricklet 2.0

    ipcon = javaObject("com.tinkerforge.IPConnection"); % Create IP connection
    he = javaObject("com.tinkerforge.BrickletHallEffectV2", UID, ipcon); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Configure counter with ±3000µT threshold and 10ms debounce
    he.setCounterConfig(3000, -3000, 10000);

    % Register counter callback to function cb_counter
    he.addCounterCallback(@cb_counter);

    % Set period for counter callback to 0.1s (100ms)
    he.setCounterCallbackConfiguration(100, true);

    input("Press key to exit\n", "s");
    ipcon.disconnect();
end

% Callback function for counter callback
function cb_counter(e)
    fprintf("Counter: %d\n", e.counter);
end
