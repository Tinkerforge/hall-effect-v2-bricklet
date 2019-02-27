/* hall-effect-v2-bricklet
 * Copyright (C) 2019 Olaf Lüke <olaf@tinkerforge.com>
 *
 * communication.h: TFP protocol message handling
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

#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <stdint.h>
#include <stdbool.h>

#include "bricklib2/protocols/tfp/tfp.h"
#include "bricklib2/bootloader/bootloader.h"

// Default functions
BootloaderHandleMessageResponse handle_message(const void *data, void *response);
void communication_tick(void);
void communication_init(void);

// Constants
#define HALL_EFFECT_V2_THRESHOLD_OPTION_OFF 'x'
#define HALL_EFFECT_V2_THRESHOLD_OPTION_OUTSIDE 'o'
#define HALL_EFFECT_V2_THRESHOLD_OPTION_INSIDE 'i'
#define HALL_EFFECT_V2_THRESHOLD_OPTION_SMALLER '<'
#define HALL_EFFECT_V2_THRESHOLD_OPTION_GREATER '>'

#define HALL_EFFECT_V2_BOOTLOADER_MODE_BOOTLOADER 0
#define HALL_EFFECT_V2_BOOTLOADER_MODE_FIRMWARE 1
#define HALL_EFFECT_V2_BOOTLOADER_MODE_BOOTLOADER_WAIT_FOR_REBOOT 2
#define HALL_EFFECT_V2_BOOTLOADER_MODE_FIRMWARE_WAIT_FOR_REBOOT 3
#define HALL_EFFECT_V2_BOOTLOADER_MODE_FIRMWARE_WAIT_FOR_ERASE_AND_REBOOT 4

#define HALL_EFFECT_V2_BOOTLOADER_STATUS_OK 0
#define HALL_EFFECT_V2_BOOTLOADER_STATUS_INVALID_MODE 1
#define HALL_EFFECT_V2_BOOTLOADER_STATUS_NO_CHANGE 2
#define HALL_EFFECT_V2_BOOTLOADER_STATUS_ENTRY_FUNCTION_NOT_PRESENT 3
#define HALL_EFFECT_V2_BOOTLOADER_STATUS_DEVICE_IDENTIFIER_INCORRECT 4
#define HALL_EFFECT_V2_BOOTLOADER_STATUS_CRC_MISMATCH 5

#define HALL_EFFECT_V2_STATUS_LED_CONFIG_OFF 0
#define HALL_EFFECT_V2_STATUS_LED_CONFIG_ON 1
#define HALL_EFFECT_V2_STATUS_LED_CONFIG_SHOW_HEARTBEAT 2
#define HALL_EFFECT_V2_STATUS_LED_CONFIG_SHOW_STATUS 3

// Function and callback IDs and structs
#define FID_GET_MAGNETIC_FLUX_DENSITY 1
#define FID_SET_MAGNETIC_FLUX_DENSITY_CALLBACK_CONFIGURATION 2
#define FID_GET_MAGNETIC_FLUX_DENSITY_CALLBACK_CONFIGURATION 3
#define FID_GET_COUNTER 5
#define FID_SET_COUNTER_CONFIG 6
#define FID_GET_COUNTER_CONFIG 7
#define FID_SET_COUNTER_CALLBACK_CONFIGURATION 8
#define FID_GET_COUNTER_CALLBACK_CONFIGURATION 9

#define FID_CALLBACK_MAGNETIC_FLUX_DENSITY 4
#define FID_CALLBACK_COUNTER 10

typedef struct {
	TFPMessageHeader header;
	bool reset_counter;
} __attribute__((__packed__)) GetCounter;

typedef struct {
	TFPMessageHeader header;
	uint32_t count;
} __attribute__((__packed__)) GetCounter_Response;

typedef struct {
	TFPMessageHeader header;
	int16_t high_threshold;
	int16_t low_threshold;
	uint32_t debounce;
} __attribute__((__packed__)) SetCounterConfig;

typedef struct {
	TFPMessageHeader header;
} __attribute__((__packed__)) GetCounterConfig;

typedef struct {
	TFPMessageHeader header;
	int16_t high_threshold;
	int16_t low_threshold;
	uint32_t debounce;
} __attribute__((__packed__)) GetCounterConfig_Response;

typedef struct {
	TFPMessageHeader header;
	uint32_t period;
	bool value_has_to_change;
} __attribute__((__packed__)) SetCounterCallbackConfiguration;

typedef struct {
	TFPMessageHeader header;
} __attribute__((__packed__)) GetCounterCallbackConfiguration;

typedef struct {
	TFPMessageHeader header;
	uint32_t period;
	bool value_has_to_change;
} __attribute__((__packed__)) GetCounterCallbackConfiguration_Response;

typedef struct {
	TFPMessageHeader header;
	uint32_t count;
} __attribute__((__packed__)) Counter_Callback;


// Function prototypes
BootloaderHandleMessageResponse get_counter(const GetCounter *data, GetCounter_Response *response);
BootloaderHandleMessageResponse set_counter_config(const SetCounterConfig *data);
BootloaderHandleMessageResponse get_counter_config(const GetCounterConfig *data, GetCounterConfig_Response *response);
BootloaderHandleMessageResponse set_counter_callback_configuration(const SetCounterCallbackConfiguration *data);
BootloaderHandleMessageResponse get_counter_callback_configuration(const GetCounterCallbackConfiguration *data, GetCounterCallbackConfiguration_Response *response);

// Callbacks
bool handle_magnetic_flux_density_callback(void);
bool handle_counter_callback(void);

#define COMMUNICATION_CALLBACK_TICK_WAIT_MS 1
#define COMMUNICATION_CALLBACK_HANDLER_NUM 2
#define COMMUNICATION_CALLBACK_LIST_INIT \
	handle_magnetic_flux_density_callback, \
	handle_counter_callback, \


#endif
