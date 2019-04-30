/* hall-effect-v2-bricklet
 * Copyright (C) 2019 Olaf Lüke <olaf@tinkerforge.com>
 *
 * communication.c: TFP protocol message handling
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#include "communication.h"

#include "bricklib2/utility/communication_callback.h"
#include "bricklib2/protocols/tfp/tfp.h"

#include "drv5053.h"

#define CALLBACK_VALUE_TYPE CALLBACK_VALUE_TYPE_INT16
#include "bricklib2/utility/callback_value.h"
CallbackValue_int16_t callback_value_magnetic_flux_density;


BootloaderHandleMessageResponse handle_message(const void *message, void *response) {
	switch(tfp_get_fid_from_message(message)) {
		case FID_GET_MAGNETIC_FLUX_DENSITY: return get_callback_value_int16_t(message, response, &callback_value_magnetic_flux_density);
		case FID_SET_MAGNETIC_FLUX_DENSITY_CALLBACK_CONFIGURATION: return set_callback_value_callback_configuration_int16_t(message, &callback_value_magnetic_flux_density);
		case FID_GET_MAGNETIC_FLUX_DENSITY_CALLBACK_CONFIGURATION: return get_callback_value_callback_configuration_int16_t(message, response, &callback_value_magnetic_flux_density);
		case FID_GET_COUNTER: return get_counter(message, response);
		case FID_SET_COUNTER_CONFIG: return set_counter_config(message);
		case FID_GET_COUNTER_CONFIG: return get_counter_config(message, response);
		case FID_SET_COUNTER_CALLBACK_CONFIGURATION: return set_counter_callback_configuration(message);
		case FID_GET_COUNTER_CALLBACK_CONFIGURATION: return get_counter_callback_configuration(message, response);
		default: return HANDLE_MESSAGE_RESPONSE_NOT_SUPPORTED;
	}
}

BootloaderHandleMessageResponse get_counter(const GetCounter *data, GetCounter_Response *response) {
	response->header.length = sizeof(GetCounter_Response);
	response->count         = drv5053_get_count(data->reset_counter);

	return HANDLE_MESSAGE_RESPONSE_NEW_MESSAGE;
}

BootloaderHandleMessageResponse set_counter_config(const SetCounterConfig *data) {
	if(data->debounce > 1000000) {
		return HANDLE_MESSAGE_RESPONSE_INVALID_PARAMETER;
	}

	drv5053.counter_threshold_high = data->high_threshold;
	drv5053.counter_threshold_low  = data->low_threshold;
	drv5053.counter_debounce       = data->debounce;
	drv5053.counter_config_new     = true;

	return HANDLE_MESSAGE_RESPONSE_EMPTY;
}

BootloaderHandleMessageResponse get_counter_config(const GetCounterConfig *data, GetCounterConfig_Response *response) {
	response->header.length  = sizeof(GetCounterConfig_Response);
	response->high_threshold = drv5053.counter_threshold_high;
	response->low_threshold  = drv5053.counter_threshold_low;
	response->debounce       = drv5053.counter_debounce;

	return HANDLE_MESSAGE_RESPONSE_NEW_MESSAGE;
}

BootloaderHandleMessageResponse set_counter_callback_configuration(const SetCounterCallbackConfiguration *data) {
	drv5053.cb_period              = data->period;
	drv5053.cb_value_has_to_change = data->value_has_to_change;

	return HANDLE_MESSAGE_RESPONSE_EMPTY;
}

BootloaderHandleMessageResponse get_counter_callback_configuration(const GetCounterCallbackConfiguration *data, GetCounterCallbackConfiguration_Response *response) {
	response->header.length       = sizeof(GetCounterCallbackConfiguration_Response);
	response->period              = drv5053.cb_period;
	response->value_has_to_change = drv5053.cb_value_has_to_change;

	return HANDLE_MESSAGE_RESPONSE_NEW_MESSAGE;
}


bool handle_magnetic_flux_density_callback(void) {
	return handle_callback_value_callback_int16_t(&callback_value_magnetic_flux_density, FID_CALLBACK_MAGNETIC_FLUX_DENSITY);
}

bool handle_counter_callback(void) {
	static bool is_buffered = false;
	static Counter_Callback cb;
	static uint32_t last_count = 0;
	static uint32_t last_time = 0;

	if(!is_buffered) {
		if(drv5053.cb_period == 0 || !system_timer_is_time_elapsed_ms(last_time, drv5053.cb_period)) {
			return false;
		}

		uint32_t new_count = drv5053_get_count(false);
		if(drv5053.cb_value_has_to_change && (last_count == new_count)) {
			return false;
		}

		tfp_make_default_header(&cb.header, bootloader_get_uid(), sizeof(Counter_Callback), FID_CALLBACK_COUNTER);
		cb.count   = new_count;
		last_count = new_count;
		last_time  = system_timer_get_ms();
	}

	if(bootloader_spitfp_is_send_possible(&bootloader_status.st)) {
		bootloader_spitfp_send_ack_and_message(&bootloader_status, (uint8_t*)&cb, sizeof(Counter_Callback));
		is_buffered = false;
		return true;
	} else {
		is_buffered = true;
	}

	return false;
}


void communication_tick(void) {
	communication_callback_tick();
}

void communication_init(void) {
	callback_value_init_int16_t(&callback_value_magnetic_flux_density, drv5053_get_magnetic_flux_density);

	communication_callback_init();
}
