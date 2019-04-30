/* hall-effect-v2-bricklet
 * Copyright (C) 2018 Olaf Lüke <olaf@tinkerforge.com>
 *
 * drv5053.h: Driver for DRV5053
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

#ifndef DRV5053_H
#define DRV5053_H

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    int16_t magnetic_flux_density;

    int16_t counter_threshold_high;
    int16_t counter_threshold_low;
    uint32_t counter_debounce;
    bool counter_config_new;

    uint32_t cb_period;
    uint32_t cb_value_has_to_change;
} DRV5053;

extern DRV5053 drv5053;

void drv5053_init(void);
void drv5053_tick(void);
int16_t drv5053_get_magnetic_flux_density(void);
uint32_t drv5053_get_count(bool reset);

#endif