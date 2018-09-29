/*
 * uart_helper.c
 *
 *  Created on: 29 Sep 2018
 *      Author: Jaco
 */

#include "uart_helper.h"

#include "mss_uart.h"
//#include "FreeRTOS.h"

//Only uart 0 will be used in this project

mss_uart_instance_t * const uart_instance = &g_mss_uart0;


void uart_string_print(uint8_t * uart_string){
	MSS_UART_polled_tx_string(uart_instance, uart_string);
}
