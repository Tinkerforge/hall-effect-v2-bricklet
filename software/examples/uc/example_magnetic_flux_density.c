// This example is not self-contained.
// It requires usage of the example driver specific to your platform.
// See the HAL documentation.

#include "src/bindings/hal_common.h"
#include "src/bindings/bricklet_hall_effect_v2.h"

void check(int rc, const char *msg);
void example_setup(TF_HAL *hal);
void example_loop(TF_HAL *hal);

static TF_HallEffectV2 he;

void example_setup(TF_HAL *hal) {
	// Create device object
	check(tf_hall_effect_v2_create(&he, NULL, hal), "create device object");

	// Get current Magnetic Flux Density
	int16_t magnetic_flux_density;
	check(tf_hall_effect_v2_get_magnetic_flux_density(&he,
	                                                  &magnetic_flux_density), "get Magnetic Flux Density");

	tf_hal_printf("Magnetic Flux Density: %I16d µT\n", magnetic_flux_density);
}

void example_loop(TF_HAL *hal) {
	// Poll for callbacks
	tf_hal_callback_tick(hal, 0);
}
