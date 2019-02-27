/* hall-effect-v2-bricklet
 * Copyright (C) 2018 Olaf Lüke <olaf@tinkerforge.com>
 *
 * config_drv5053.h: Config for DRV5053
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

#ifndef CONFIG_DRV5053_H
#define CONFIG_DRV5053_H


#define DRV5053_OUT0_PIN             P2_9
#define DRV5053_OUT0_CHANNEL         2

#define DRV5053_OUT1_PIN             P2_1
// #define DRV5053_OUT1_CHANNEL         2 // ?

#define DRV5053_REF_CCU4_PIN_MODE    XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT2

#define DRV5053_REF0_CCU4_PIN        P1_1
#define DRV5053_REF0_CCU4_CC         CCU40_CC41
#define DRV5053_REF0_CCU4_SLICE      XMC_CCU4_SHADOW_TRANSFER_SLICE_1
#define DRV5053_REF0_CCU4_SLICE_NUM  1
#define DRV5053_REF0_CMP_INSTANCE    0

#define DRV5053_REF1_CCU4_PIN        P1_0
#define DRV5053_REF1_CCU4_CC         CCU40_CC40
#define DRV5053_REF1_CCU4_SLICE      XMC_CCU4_SHADOW_TRANSFER_SLICE_0
#define DRV5053_REF1_CCU4_SLICE_NUM  0
#define DRV5053_REF1_CMP_INSTANCE    2


#define DRV5053_CMP_IRQ              3
#define DRV5053_CMP_IRQ_PRIORITY     0

#define DRV5053_CMP0_ETL_CHANNEL     0
#define DRV5053_CMP0_OGU_CHANNEL     0

#define DRV5053_CMP1_ETL_CHANNEL     2
#define DRV5053_CMP1_OGU_CHANNEL     1

#define DRV5053_TMR_CCU4             CCU40
#define DRV5053_TMR_IRQ_PRIORITY     0

#define DRV5053_TMR_CCU4_CC          CCU40_CC42
#define DRV5053_TMR_CCU4_SLICE       XMC_CCU4_SHADOW_TRANSFER_SLICE_2
#define DRV5053_TMR_CCU4_SLICE_PRE   XMC_CCU4_SHADOW_TRANSFER_PRESCALER_SLICE_2
#define DRV5053_TMR_SR_ID            XMC_CCU4_SLICE_SR_ID_0
#define DRV5053_TMR_IRQ              21
#define DRV5053_TMR_CCU4_SLICE_NUM   2

#define DRV5053_ADC_RESULT_REG       10
#define DRV5053_ADC_IRQ              16
#define DRV5053_ADC_IRQ_PRIORITY     1

#endif