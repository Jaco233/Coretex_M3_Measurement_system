/*
 * sensor_task.h
 *
 *  Created on: 07 Oct 2018
 *      Author: Jaco
 */

#ifndef SENSOR_TASK_H_
#define SENSOR_TASK_H_

	float get_internal_temp(void);
	float get_pot_voltage(void);
	float get_external_temp(void);
	//float convert_lm35_result_to_temp(uint16_t adc_result);
	float get_avg_external_temp(void);
	float get_humidity(void);
	float get_uv_index(void);
	float get_avg_lux(void);
	float get_lux_voltage(void);

#endif /* SENSOR_TASK_H_ */
