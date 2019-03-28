function matlab_example_magnetic_flux_density()
    import com.tinkerforge.IPConnection;
    import com.tinkerforge.BrickletHallEffectV2;

    HOST = 'localhost';
    PORT = 4223;
    UID = 'XYZ'; % Change XYZ to the UID of your Hall Effect Bricklet 2.0

    ipcon = IPConnection(); % Create IP connection
    he = handle(BrickletHallEffectV2(UID, ipcon), 'CallbackProperties'); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Get current Magnetic Flux Density
    magneticFluxDensity = he.getMagneticFluxDensity();
    fprintf('Magnetic Flux Density: %i µT\n', magneticFluxDensity);

    input('Press key to exit\n', 's');
    ipcon.disconnect();
end
