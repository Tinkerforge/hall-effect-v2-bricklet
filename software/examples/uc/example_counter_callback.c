// This example is not self-contained.
// It requres usage of the example driver specific to your platform.
// See the HAL documentation.

#include "bindings/hal_common.h"
#include "bindings/bricklet_hall_effect_v2.h"

#define UID "XYZ" // Change XYZ to the UID of your Hall Effect Bricklet 2.0

void check(int rc, const char* msg);

void example_setup(TF_HalContext *hal);
void example_loop(TF_HalContext *hal);


// Callback function for counter callback
static void counter_handler(TF_HallEffectV2 *device, uint32_t counter, void *user_data) {
	(void)device; (void)user_data; // avoid unused parameter warning

	tf_hal_printf("Counter: %I32u\n", counter);
}

static TF_HallEffectV2 he;

void example_setup(TF_HalContext *hal) {
	// Create device object
	check(tf_hall_effect_v2_create(&he, UID, hal), "create device object");

	// Configure counter with ±3000µT threshold and 10ms debounce
	check(tf_hall_effect_v2_set_counter_config(&he, 3000, -3000,
	                                           10000), "call set_counter_config");

	// Register counter callback to function counter_handler
	tf_hall_effect_v2_register_counter_callback(&he,
	                                            counter_handler,
	                                            NULL);

	// Set period for counter callback to 0.1s (100ms)
	tf_hall_effect_v2_set_counter_callback_configuration(&he, 100, true);
}

void example_loop(TF_HalContext *hal) {
	// Poll for callbacks
	tf_hal_callback_tick(hal, 0);
}
