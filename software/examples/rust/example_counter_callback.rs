use std::thread;
use std::{error::Error, io};
use tinkerforge::{hall_effect_v2_bricklet::*, ip_connection::IpConnection};

const HOST: &str = "localhost";
const PORT: u16 = 4223;
const UID: &str = "XYZ"; // Change XYZ to the UID of your Hall Effect Bricklet 2.0.

fn main() -> Result<(), Box<dyn Error>> {
    let ipcon = IpConnection::new(); // Create IP connection.
    let he = HallEffectV2Bricklet::new(UID, &ipcon); // Create device object.

    ipcon.connect((HOST, PORT)).recv()??; // Connect to brickd.
                                          // Don't use device before ipcon is connected.

    // Configure counter with ±3000µT threshold and 10ms debounce
    he.set_counter_config(3000, -3000, 10000);

    let counter_receiver = he.get_counter_callback_receiver();

    // Spawn thread to handle received callback messages.
    // This thread ends when the `he` object
    // is dropped, so there is no need for manual cleanup.
    thread::spawn(move || {
        for counter in counter_receiver {
            println!("Counter: {}", counter);
        }
    });

    // Set period for counter callback to 0.1s (100ms).
    he.set_counter_callback_configuration(100, true);

    println!("Press enter to exit.");
    let mut _input = String::new();
    io::stdin().read_line(&mut _input)?;
    ipcon.disconnect();
    Ok(())
}
