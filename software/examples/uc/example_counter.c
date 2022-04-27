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

	// Get current count without counter reset
	uint32_t count;
	check(tf_hall_effect_v2_get_counter(&he, false,
	                                    &count), "get count without counter reset");

	tf_hal_printf("Count: %I32u\n", count);
}

void example_loop(TF_HAL *hal) {
	// Poll for callbacks
	tf_hal_callback_tick(hal, 0);
}
