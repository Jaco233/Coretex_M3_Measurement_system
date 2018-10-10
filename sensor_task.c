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
#include <math.h>



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
		 ext_temp_channel = (ace_channel_handle_t) 2;
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
	   for( a = 0; a < 1000; a = a + 1 ){
		   short_avg_temp = short_avg_temp + get_external_temp();
		   //vTaskDelay(50); //configTICK_RATE_HZ	=1000 (5ms delay)
	   }
	   short_avg_temp=short_avg_temp/1000;

	return short_avg_temp;
}

float get_humidity(void)
{
		 uint16_t adc_result;
		 ace_channel_handle_t ext_humid_channel;
		 ext_humid_channel = (ace_channel_handle_t)3;
		 adc_result = ACE_get_ppe_sample( ext_humid_channel );
		 float real_humid_val;
		 real_humid_val = (float)ACE_convert_to_mV( ext_humid_channel,adc_result )/(float)1000;

		 return 30*real_humid_val*pow(1.015,real_humid_val);
}

float get_uv_index(void)
{
		 uint16_t adc_result;
		 ace_channel_handle_t ext_uv_channel;
		 ext_uv_channel = (ace_channel_handle_t)5;
		 adc_result = ACE_get_ppe_sample( ext_uv_channel );
		 float real_uv_val;
		 real_uv_val = (float)ACE_convert_to_mV( ext_uv_channel,adc_result )/(float)1000;

		 return ((7.2*real_uv_val)-7);
}


