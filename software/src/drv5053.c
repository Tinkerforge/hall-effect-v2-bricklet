/* hall-effect-v2-bricklet
 * Copyright (C) 2018 Olaf Lüke <olaf@tinkerforge.com>
 *
 * drv5053.c: Driver for DRV5053
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

#include "drv5053.h"

#include "configs/config_drv5053.h"
#include "bricklib2/hal/system_timer/system_timer.h"
#include "bricklib2/utility/util_definitions.h"

#include "xmc_gpio.h"
#include "xmc_vadc.h"
#include "xmc_acmp.h"
#include "xmc_eru.h"
#include "xmc_ccu4.h"

#define DRV5053_ZERO_OFFSET_MV  (1020)
#define DRV5053_ZERO_OFFSET_ADC (DRV5053_ZERO_OFFSET_MV*1000/90)

DRV5053 drv5053;

#define drv5053_irq_cmp IRQ_Hdlr_3
static volatile uint32_t drv5053_count = 0;
void __attribute__((optimize("-O3"))) __attribute__ ((section (".ram_code"))) drv5053_irq_cmp(void) {
    XMC_CCU4_SLICE_StartTimer(DRV5053_TMR_CCU4_CC);
	NVIC_DisableIRQ(DRV5053_CMP_IRQ);
	NVIC_ClearPendingIRQ(DRV5053_CMP_IRQ);

	drv5053_count++;
}

#define drv5053_irq_adc IRQ_Hdlr_16
static volatile uint32_t drv5053_adc_count = 0;
static volatile uint32_t drv5053_adc_value = 0;
void __attribute__((optimize("-O3"))) __attribute__ ((section (".ram_code"))) drv5053_irq_adc(void) {
	const uint32_t result =  XMC_VADC_GROUP_GetDetailedResult(VADC_G0, 10);
	drv5053_adc_value += (result & 0xFFFF);
	drv5053_adc_count++;
}

#define drv5053_irq_tmr IRQ_Hdlr_21
void __attribute__((optimize("-O3"))) __attribute__ ((section (".ram_code"))) drv5053_irq_tmr(void) {
	NVIC_ClearPendingIRQ(DRV5053_CMP_IRQ);
	NVIC_EnableIRQ(DRV5053_CMP_IRQ);
}

void drv5053_init_adc(void) {
	const XMC_GPIO_CONFIG_t voltage_pin_config = {
		.mode             = XMC_GPIO_MODE_INPUT_TRISTATE,
		.input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_LARGE,
	};
	XMC_GPIO_Init(DRV5053_OUT0_PIN, &voltage_pin_config);

	// This structure contains the Global related Configuration.
	const XMC_VADC_GLOBAL_CONFIG_t adc_global_config = {
		.boundary0 = (uint32_t) 0, // Lower boundary value for Normal comparison mode
		.boundary1 = (uint32_t) 0, // Upper boundary value for Normal comparison mode

		.class0 = {
			.sample_time_std_conv     = 31,                      // The Sample time is (2*tadci)
			.conversion_mode_standard = XMC_VADC_CONVMODE_12BIT, // 12bit conversion Selected

		},
		.class1 = {
			.sample_time_std_conv     = 31,                      // The Sample time is (2*tadci)
			.conversion_mode_standard = XMC_VADC_CONVMODE_12BIT, // 12bit conversion Selected

		},

		.data_reduction_control         = 0b11, // Accumulate 4 result values
		.wait_for_read_mode             = 0, // GLOBRES Register will not be overwritten until the previous value is read
		.event_gen_enable               = 0, // Result Event from GLOBRES is disabled
		.disable_sleep_mode_control     = 0  // Sleep mode is enabled
	};


	// Global iclass0 configuration
	const XMC_VADC_GLOBAL_CLASS_t adc_global_iclass_config = {
		.conversion_mode_standard = XMC_VADC_CONVMODE_12BIT,
		.sample_time_std_conv	  = 31,
	};

	// Global Result Register configuration structure
	XMC_VADC_RESULT_CONFIG_t adc_global_result_config = {
		.data_reduction_control = 0b11,  // Accumulate 4 result values
		.post_processing_mode   = XMC_VADC_DMM_REDUCTION_MODE,
		.wait_for_read_mode  	= 1, // Enabled
		.part_of_fifo       	= 0, // No FIFO
		.event_gen_enable   	= 1  // Disable Result event
	};

	// LLD Background Scan Init Structure
	const XMC_VADC_BACKGROUND_CONFIG_t adc_background_config = {
		.conv_start_mode   = XMC_VADC_STARTMODE_CIR,       // Conversion start mode selected as cancel inject repeat
		.req_src_priority  = XMC_VADC_GROUP_RS_PRIORITY_1, // Priority of the Background request source in the VADC module
		.trigger_signal    = XMC_VADC_REQ_TR_A,            // If Trigger needed then this denotes the Trigger signal
		.trigger_edge      = XMC_VADC_TRIGGER_EDGE_NONE,   // If Trigger needed then this denotes Trigger edge selected
		.gate_signal       = XMC_VADC_REQ_GT_A,			   // If Gating needed then this denotes the Gating signal
		.timer_mode        = 0,							   // Timer Mode Disabled
		.external_trigger  = 0,                            // Trigger is Disabled
		.req_src_interrupt = 0,                            // Background Request source interrupt Disabled
		.enable_auto_scan  = 1,
		.load_mode         = XMC_VADC_SCAN_LOAD_OVERWRITE
	};

	const XMC_VADC_GROUP_CONFIG_t group_init_handle0 = {
		.emux_config = {
			.stce_usage                  = 0, 					           // Use STCE when the setting changes
			.emux_mode                   = XMC_VADC_GROUP_EMUXMODE_SWCTRL, // Mode for Emux conversion
			.emux_coding                 = XMC_VADC_GROUP_EMUXCODE_BINARY, // Channel progression - binary format
			.starting_external_channel   = 0,                              // Channel starts at 0 for EMUX
			.connected_channel           = 0                               // Channel connected to EMUX
		},
		.class0 = {
			.sample_time_std_conv        = 31,                             // The Sample time is (2*tadci)
			.conversion_mode_standard    = XMC_VADC_CONVMODE_12BIT,        // 12bit conversion Selected
			.sampling_phase_emux_channel = 0,                              // The Sample time is (2*tadci)
			.conversion_mode_emux        = XMC_VADC_CONVMODE_12BIT         // 12bit conversion Selected
		},
		.class1 = {
			.sample_time_std_conv        = 31,                             // The Sample time is (2*tadci)
			.conversion_mode_standard    = XMC_VADC_CONVMODE_12BIT,        // 12bit conversion Selected
			.sampling_phase_emux_channel = 0,                              // The Sample time is (2*tadci)
			.conversion_mode_emux        = XMC_VADC_CONVMODE_12BIT         // 12bit conversion Selected
		},

		.boundary0                       = 0,                              // Lower boundary value for Normal comparison mode
		.boundary1	                     = 0,                              // Upper boundary value for Normal comparison mode
		.arbitration_round_length        = 0,                              // 4 arbitration slots per round selected (tarb = 4*tadcd) */
		.arbiter_mode                    = XMC_VADC_GROUP_ARBMODE_ALWAYS,  // Determines when the arbiter should run.
	};


	XMC_VADC_CHANNEL_CONFIG_t  channel_a_config = {
		.input_class                =  XMC_VADC_CHANNEL_CONV_GLOBAL_CLASS0,    // Global ICLASS 0 selected
		.lower_boundary_select 	    =  XMC_VADC_CHANNEL_BOUNDARY_GROUP_BOUND0,
		.upper_boundary_select 	    =  XMC_VADC_CHANNEL_BOUNDARY_GROUP_BOUND0,
		.event_gen_criteria         =  XMC_VADC_CHANNEL_EVGEN_NEVER,           // Channel Event disabled
		.sync_conversion  		    =  0,                                      // Sync feature disabled
		.alternate_reference        =  XMC_VADC_CHANNEL_REF_INTREF,            // Internal reference selected
		.result_reg_number          =  10,                                     // GxRES[10] selected
		.use_global_result          =  0, 				                       // Use Group result register
		.result_alignment           =  XMC_VADC_RESULT_ALIGN_RIGHT,            // Result alignment - Right Aligned
		.broken_wire_detect_channel =  XMC_VADC_CHANNEL_BWDCH_VAGND,           // No Broken wire mode select
		.broken_wire_detect		    =  0,    		                           // No Broken wire detection
		.bfl                        =  0,                                      // No Boundary flag
		.channel_priority           =  0,                   		           // Lowest Priority 0 selected
		.alias_channel              =  -1                                      // Channel is Aliased
	};

	XMC_VADC_RESULT_CONFIG_t channel_a_result_config =
	{
		.data_reduction_control = 0b11,                         // Accumulate 4 result values
		.post_processing_mode   = XMC_VADC_DMM_REDUCTION_MODE,  // Use reduction mode
		.wait_for_read_mode  	= 1,                            // Enabled
		.part_of_fifo       	= 0 ,                           // No FIFO
		.event_gen_enable   	= 1                             // Disable Result event
	};


	XMC_VADC_GLOBAL_Init(VADC, &adc_global_config);

    XMC_VADC_GROUP_Init(VADC_G0, &group_init_handle0);
    XMC_VADC_GROUP_SetPowerMode(VADC_G0, XMC_VADC_GROUP_POWERMODE_NORMAL);

    XMC_VADC_GLOBAL_DisablePostCalibration(VADC, 0);
    XMC_VADC_GLOBAL_SHS_EnableAcceleratedMode(SHS0, XMC_VADC_GROUP_INDEX_0);
    XMC_VADC_GLOBAL_SHS_SetAnalogReference(SHS0, XMC_VADC_GLOBAL_SHS_AREF_EXTERNAL_VDD_UPPER_RANGE);

	XMC_VADC_GLOBAL_StartupCalibration(VADC);

	// Initialize the Global Conversion class 0
	XMC_VADC_GLOBAL_InputClassInit(VADC, adc_global_iclass_config, XMC_VADC_GROUP_CONV_STD, 0);

	// Initialize the Background Scan hardware
	XMC_VADC_GLOBAL_BackgroundInit(VADC, &adc_background_config);
	XMC_VADC_GLOBAL_ResultInit(VADC, &adc_global_result_config);
    XMC_VADC_GROUP_ChannelInit(VADC_G0, DRV5053_OUT0_CHANNEL, &channel_a_config);
    XMC_VADC_GROUP_ResultInit(VADC_G0, channel_a_config.result_reg_number, &channel_a_result_config);

	XMC_VADC_GLOBAL_BackgroundAddChannelToSequence(VADC, 0, DRV5053_OUT0_CHANNEL);
	XMC_VADC_GLOBAL_SetResultEventInterruptNode(VADC, XMC_VADC_SR_SHARED_SR0);

	XMC_VADC_GLOBAL_BackgroundTriggerConversion(VADC);

	// Interrupt
	NVIC_SetPriority(DRV5053_ADC_IRQ, DRV5053_ADC_IRQ_PRIORITY);
	XMC_VADC_GLOBAL_BackgroundSetReqSrcEventInterruptNode(VADC, XMC_VADC_SR_SHARED_SR1);
	XMC_VADC_GROUP_SetResultInterruptNode(VADC_G0, DRV5053_ADC_RESULT_REG, XMC_VADC_SR_SHARED_SR1);
	NVIC_EnableIRQ(DRV5053_ADC_IRQ); 
}

void drv5053_init_comperator(void) {
	// Initialize and enable comperator
	XMC_ACMP_ClearLowPowerMode();

	const XMC_ACMP_CONFIG_t comperator_config = {
		.filter_disable             = false,
		.output_invert              = false,
		.hysteresis                 = XMC_ACMP_HYSTERESIS_20
	};

	XMC_ACMP_Init((XMC_ACMP_t*)COMPARATOR, DRV5053_REF0_CMP_INSTANCE, &comperator_config);
	XMC_ACMP_Init((XMC_ACMP_t*)COMPARATOR, DRV5053_REF1_CMP_INSTANCE, &comperator_config);
	XMC_ACMP_EnableComparator((XMC_ACMP_t*)COMPARATOR, DRV5053_REF0_CMP_INSTANCE);
	XMC_ACMP_EnableComparator((XMC_ACMP_t*)COMPARATOR, DRV5053_REF1_CMP_INSTANCE);

	// Initialize interrupt for comperator through ERU
	XMC_ERU_ETL_CONFIG_t eru_etl_config = {
		.input_a                    = XMC_ERU_ETL_INPUT_A0, // Event input selection for A(0-3)
		.input_b                    = XMC_ERU_ETL_INPUT_B0, // Event input selection for B(0-3)
		.enable_output_trigger      = 1,
		.status_flag_mode           = XMC_ERU_ETL_STATUS_FLAG_MODE_HWCTRL, // enable the status flag auto clear for opposite edge
		.edge_detection             = XMC_ERU_ETL_EDGE_DETECTION_FALLING,  // Select the edge/s to convert as event
		.output_trigger_channel     = XMC_ERU_ETL_OUTPUT_TRIGGER_CHANNEL0, // Select the source for event
		.source                     = XMC_ERU_ETL_SOURCE_A
	};

	XMC_ERU_ETL_Init(XMC_ERU0, DRV5053_CMP0_ETL_CHANNEL, &eru_etl_config);
	eru_etl_config.edge_detection = XMC_ERU_ETL_EDGE_DETECTION_RISING;
	XMC_ERU_ETL_Init(XMC_ERU0, DRV5053_CMP1_ETL_CHANNEL, &eru_etl_config);

	XMC_ERU_OGU_SetServiceRequestMode(XMC_ERU0, DRV5053_CMP0_OGU_CHANNEL, XMC_ERU_OGU_SERVICE_REQUEST_ON_TRIGGER);
	XMC_ERU_OGU_SetServiceRequestMode(XMC_ERU0, DRV5053_CMP1_OGU_CHANNEL, XMC_ERU_OGU_SERVICE_REQUEST_ON_TRIGGER);

	// Configure NVIC node and priority
	NVIC_SetPriority(DRV5053_CMP_IRQ, DRV5053_CMP_IRQ_PRIORITY);

	// Clear pending interrupt before enabling it
	NVIC_ClearPendingIRQ(DRV5053_CMP_IRQ);

	// Enable NVIC node
	NVIC_EnableIRQ(DRV5053_CMP_IRQ);

	// Initialize reference voltage (through CCU4 with external filter)
	const XMC_GPIO_CONFIG_t ref_source_output_pin_config = {
		.mode                       = DRV5053_REF_CCU4_PIN_MODE,
		.input_hysteresis           = XMC_GPIO_INPUT_HYSTERESIS_STANDARD,
		.output_level               = XMC_GPIO_OUTPUT_LEVEL_LOW
	};
	XMC_GPIO_Init(DRV5053_REF0_CCU4_PIN, &ref_source_output_pin_config);
	XMC_GPIO_Init(DRV5053_REF1_CCU4_PIN, &ref_source_output_pin_config);

	XMC_CCU4_SLICE_COMPARE_CONFIG_t compare_config = {
		.timer_mode                 = XMC_CCU4_SLICE_TIMER_COUNT_MODE_EA,
		.monoshot                   = XMC_CCU4_SLICE_TIMER_REPEAT_MODE_REPEAT,
		.shadow_xfer_clear          = 0,
		.dither_timer_period        = 0,
		.dither_duty_cycle          = 1,
		.prescaler_mode             = XMC_CCU4_SLICE_PRESCALER_MODE_NORMAL,
		.mcm_enable                 = 0,
		.prescaler_initval          = 0,
		.dither_limit               = 8,
		.timer_concatenation        = 0,
		.passive_level              = XMC_CCU4_SLICE_OUTPUT_PASSIVE_LEVEL_LOW,
	};

	XMC_CCU4_Init(CCU40, XMC_CCU4_SLICE_MCMS_ACTION_TRANSFER_PR_CR);
	XMC_CCU4_StartPrescaler(CCU40);
	XMC_CCU4_SLICE_CompareInit(DRV5053_REF0_CCU4_CC, &compare_config);
	XMC_CCU4_SLICE_CompareInit(DRV5053_REF1_CCU4_CC, &compare_config);
	XMC_CCU4_SLICE_SetTimerPeriodMatch(DRV5053_REF0_CCU4_CC, 3300-1);
	XMC_CCU4_SLICE_SetTimerPeriodMatch(DRV5053_REF1_CCU4_CC, 3300-1);
	XMC_CCU4_SLICE_SetTimerCompareMatch(DRV5053_REF0_CCU4_CC, 0);
	XMC_CCU4_SLICE_SetTimerCompareMatch(DRV5053_REF1_CCU4_CC, 3300);
	XMC_CCU4_EnableShadowTransfer(CCU40, DRV5053_REF0_CCU4_SLICE);
	XMC_CCU4_EnableShadowTransfer(CCU40, DRV5053_REF1_CCU4_SLICE);
	XMC_CCU4_EnableClock(CCU40, DRV5053_REF0_CCU4_SLICE_NUM);
	XMC_CCU4_EnableClock(CCU40, DRV5053_REF1_CCU4_SLICE_NUM);
	XMC_CCU4_SLICE_StartTimer(DRV5053_REF0_CCU4_CC);
	XMC_CCU4_SLICE_StartTimer(DRV5053_REF1_CCU4_CC);
}

void drv5053_init_timer(void) {
	XMC_CCU4_SLICE_COMPARE_CONFIG_t timer_config = {
		.timer_mode          = XMC_CCU4_SLICE_TIMER_COUNT_MODE_EA,
		.monoshot            = XMC_CCU4_SLICE_TIMER_REPEAT_MODE_SINGLE,
		.shadow_xfer_clear   = false,
		.dither_timer_period = false,
		.dither_duty_cycle   = false,
		.prescaler_mode      = XMC_CCU4_SLICE_PRESCALER_MODE_NORMAL,
		.mcm_enable          = false,
		.prescaler_initval   = XMC_CCU4_SLICE_PRESCALER_1024,
		.float_limit         = 0U,
		.dither_limit        = 0U,
		.passive_level       = XMC_CCU4_SLICE_OUTPUT_PASSIVE_LEVEL_LOW,
		.timer_concatenation = false
	};

    XMC_CCU4_EnableClock(DRV5053_TMR_CCU4, DRV5053_TMR_CCU4_SLICE_NUM);
    XMC_CCU4_SLICE_CompareInit(DRV5053_TMR_CCU4_CC, &timer_config);
    XMC_CCU4_SLICE_SetTimerPeriodMatch(DRV5053_TMR_CCU4_CC, UINT16_MAX);
    XMC_CCU4_SLICE_SetTimerCompareMatch(DRV5053_TMR_CCU4_CC, 0);
    XMC_CCU4_EnableShadowTransfer(DRV5053_TMR_CCU4, DRV5053_TMR_CCU4_SLICE | DRV5053_TMR_CCU4_SLICE_PRE);

    XMC_CCU4_SLICE_EnableEvent(DRV5053_TMR_CCU4_CC, XMC_CCU4_SLICE_IRQ_ID_PERIOD_MATCH);
    XMC_CCU4_SLICE_SetInterruptNode(DRV5053_TMR_CCU4_CC, XMC_CCU4_SLICE_IRQ_ID_PERIOD_MATCH, DRV5053_TMR_SR_ID);
    NVIC_SetPriority(DRV5053_TMR_IRQ, DRV5053_TMR_IRQ_PRIORITY);
    NVIC_EnableIRQ(DRV5053_TMR_IRQ);
}

void drv5053_init(void) {
	memset(&drv5053, 0, sizeof(DRV5053));

	drv5053_init_comperator();
	drv5053_init_timer();
	drv5053_init_adc();

	drv5053.counter_threshold_high = 5000;   // 5mT
	drv5053.counter_threshold_low  = -5000;  // -5mT
	drv5053.counter_debounce       = 100000; // 100ms
	drv5053.counter_config_new     = true;
}

void drv5053_update_counter_config(void) {
	// Note: A high threhold in uT is a low voltage
	int32_t mv_low  = (-drv5053.counter_threshold_high*90/1000) + DRV5053_ZERO_OFFSET_MV;
	int32_t mv_high = (-drv5053.counter_threshold_low*90/1000)  + DRV5053_ZERO_OFFSET_MV;

	mv_low  = 3300 - BETWEEN(0, mv_low,  3300);
	mv_high = 3300 - BETWEEN(0, mv_high, 3300);

	XMC_CCU4_SLICE_SetTimerCompareMatch(DRV5053_REF0_CCU4_CC, mv_low);
	XMC_CCU4_SLICE_SetTimerCompareMatch(DRV5053_REF1_CCU4_CC, mv_high);
	XMC_CCU4_EnableShadowTransfer(CCU40, DRV5053_REF0_CCU4_SLICE);
	XMC_CCU4_EnableShadowTransfer(CCU40, DRV5053_REF1_CCU4_SLICE);

    XMC_CCU4_SLICE_SetTimerPeriodMatch(DRV5053_TMR_CCU4_CC, MAX(1, drv5053.counter_debounce/16));
    XMC_CCU4_EnableShadowTransfer(DRV5053_TMR_CCU4, DRV5053_TMR_CCU4_SLICE | DRV5053_TMR_CCU4_SLICE_PRE);
}

void drv5053_tick(void) {
	static uint32_t last_time = 0;
	if(drv5053.counter_config_new) {
		drv5053_update_counter_config();
		drv5053.counter_config_new = false;
	}

	if(system_timer_is_time_elapsed_ms(last_time, 1)) {
		last_time = system_timer_get_ms();

		NVIC_DisableIRQ(DRV5053_ADC_IRQ);
		uint32_t value = drv5053_adc_value/drv5053_adc_count;
		drv5053_adc_count = 0;
		drv5053_adc_value = 0;
		NVIC_EnableIRQ(DRV5053_ADC_IRQ);

//		uint32_t mv = voltage*3300/(4095*4);
//		uint32_t ut = mv*1000/90;
//		uint32_t ut = voltage*3300*1000/(4095*4*90);
		int32_t ut = -(value*5500/2457 - DRV5053_ZERO_OFFSET_ADC);
		drv5053.magnetic_flux_density = ut;
	}
}

int16_t drv5053_get_magnetic_flux_density(void) {
	return drv5053.magnetic_flux_density;
}

uint32_t drv5053_get_count(void) {
	return drv5053_count;
}