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

	// Get current count without counter reset
	uint32_t count;
	check(tf_hall_effect_v2_get_counter(&he, false,
	                                    &count), "get count without counter reset");

	tf_hal_printf("Count: %u\n", count);
}

void example_loop(TF_HalContext *hal) {
	// Poll for callbacks
	tf_hal_callback_tick(hal, 0);
}
