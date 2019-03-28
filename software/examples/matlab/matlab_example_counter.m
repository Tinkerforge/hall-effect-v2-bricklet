function matlab_example_counter()
    import com.tinkerforge.IPConnection;
    import com.tinkerforge.BrickletHallEffectV2;

    HOST = 'localhost';
    PORT = 4223;
    UID = 'XYZ'; % Change XYZ to the UID of your Hall Effect Bricklet 2.0

    ipcon = IPConnection(); % Create IP connection
    he = handle(BrickletHallEffectV2(UID, ipcon), 'CallbackProperties'); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Get current count without counter reset
    count = he.getCounter(false);
    fprintf('Count: %i\n', count);

    input('Press key to exit\n', 's');
    ipcon.disconnect();
end
