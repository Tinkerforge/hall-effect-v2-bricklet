#include "bindings/hal_common.h"
#include "bindings/bricklet_hall_effect_v2.h"

#define UID "XYZ" // Change XYZ to the UID of your Hall Effect Bricklet 2.0

void check(int rc, const char* msg);

void example_setup(TF_HalContext *hal);
void example_loop(TF_HalContext *hal);


static TF_HallEffectV2 he;

void example_setup(TF_HalContext *hal) {
	// Create device object
	check(tf_hall_effect_v2_create(&he, UID, hal), "create device object");

	// Get current Magnetic Flux Density
	int16_t magnetic_flux_density;
	check(tf_hall_effect_v2_get_magnetic_flux_density(&he,
	                                                  &magnetic_flux_density), "get Magnetic Flux Density");

	tf_hal_printf("Magnetic Flux Density: %d µT\n", magnetic_flux_density);
}

void example_loop(TF_HalContext *hal) {
	// Poll for callbacks
	tf_hal_callback_tick(hal, 0);
}
