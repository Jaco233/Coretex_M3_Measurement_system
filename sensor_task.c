/*
 * sensor_task.c
 *
 *  Created on: 07 Oct 2018
 *      Author: Jaco
 */

#include "sensor_task.h"
#include <stdio.h>



/**************************************************************************/
/* Driver Includes */
/**************************************************************************/

#include "../drivers/mss_ace/mss_ace.h"

float get_internal_temp(void)
{
		 uint16_t adc_result;
		 ace_channel_handle_t internal_temp_channel;
		 internal_temp_channel = (ace_channel_handle_t)2;
		 adc_result = ACE_get_ppe_sample( internal_temp_channel );
		 float real_temperature_value_tc;
		 real_temperature_value_tc = (float)ACE_convert_to_Celsius( internal_temp_channel,adc_result )/(float)10;

		 return real_temperature_value_tc;
}

float get_pot_voltage(void)
{
		 uint16_t adc_result;
		 ace_channel_handle_t pot_voltage_channel;
		 pot_voltage_channel = (ace_channel_handle_t) 1;
		 adc_result = ACE_get_ppe_sample( pot_voltage_channel );
		 float real_voltage_uv;
		 real_voltage_uv = (float)ACE_convert_to_mV( pot_voltage_channel,adc_result )/(float)1000;

		 return real_voltage_uv;
}
