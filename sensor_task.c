/*
 * sensor_task.c
 *
 *  Created on: 07 Oct 2018
 *      Author: Jaco
 */

#include "sensor_task.h"

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"

#include <stdio.h>
#include <stdlib.h>



/**************************************************************************/
/* Driver Includes */
/**************************************************************************/

#include "../drivers/mss_ace/mss_ace.h"

float convert_lm35_result_to_temp(ace_channel_handle_t ext_temp_channel ,uint16_t adc_result){
	 float real_temp;
	 real_temp = ((float)ACE_convert_to_mV( ext_temp_channel,adc_result )/(float)10)-1;
	 return real_temp;
}

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

float get_external_temp(void)
{
		 uint16_t adc_result;
		 ace_channel_handle_t ext_temp_channel;
		 ext_temp_channel = (ace_channel_handle_t) 3;
		 adc_result = ACE_get_ppe_sample( ext_temp_channel );
		 float real_temp;
		 real_temp = convert_lm35_result_to_temp(ext_temp_channel,adc_result);

		 return real_temp;
}

float get_avg_external_temp(void)
{
	float short_avg_temp;
	 int a;
	   /* for loop execution */
	   for( a = 0; a < 5; a = a + 1 ){
		   short_avg_temp = short_avg_temp + get_external_temp();
		   vTaskDelay(5); //configTICK_RATE_HZ	=1000 (5ms delay)
	   }
	   short_avg_temp=short_avg_temp/5.0;

	return short_avg_temp;
}


