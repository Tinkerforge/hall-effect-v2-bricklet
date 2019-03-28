function octave_example_magnetic_flux_density()
    more off;

    HOST = "localhost";
    PORT = 4223;
    UID = "XYZ"; % Change XYZ to the UID of your Hall Effect Bricklet 2.0

    ipcon = javaObject("com.tinkerforge.IPConnection"); % Create IP connection
    he = javaObject("com.tinkerforge.BrickletHallEffectV2", UID, ipcon); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Get current Magnetic Flux Density
    magneticFluxDensity = he.getMagneticFluxDensity();
    fprintf("Magnetic Flux Density: %d µT\n", magneticFluxDensity);

    input("Press key to exit\n", "s");
    ipcon.disconnect();
end
