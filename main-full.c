/*
 * FreeRTOS Kernel V10.1.1
 * Copyright (C) 2018 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://www.FreeRTOS.org
 * http://aws.amazon.com/freertos
 *
 * 1 tab == 4 spaces!
 */

/*
 * This project runs on the SmartFusion A2F-EVAL-KIT evaluation board, which
 * is populated with an A2F200M3F SmartFusion mixed signal FPGA.  The A2F200M3F
 * incorporates a Cortex-M3 microcontroller.
 *
 * The main() Function:
 * main() creates two demo specific software timers, one demo specific queue,
 * and three demo specific tasks.  Then stars the scheduler.  The demo
 * specific tasks and timers are described in the comments here.
 *
 * The Demo Specific Queue Send Task:
 * The queue send task is implemented by the prvQueueSendTask() function in
 * this file.  prvQueueSendTask() sits in a loop that causes it to repeatedly
 * block for x milliseconds, before sending the value 100 to the queue that
 * was created within main().  Once the value is sent, the task loops back
 * around to block for another x milliseconds.
 *
 * The Demo Specific Queue Receive Task:
 * The queue receive task is implemented by the prvQueueReceiveTask() function
 * in this file.  prvQueueReceiveTask() sits in a loop that causes it to
 * repeatedly attempt to read data from the queue that was created within
 * main().  When data is received, the task checks the value of the data, and
 * if the value equals the expected 100, toggles the green LED.  The 'block
 * time' parameter passed to the queue receive function specifies that the task
 * should be held in the Blocked state indefinitely to wait for data to be
 * available on the queue.  The queue receive task will only leave the Blocked
 * state when the queue send task writes to the queue.  As the queue send task
 * writes to the queue every 200 milliseconds, the queue receive task leaves
 * the Blocked state every x milliseconds, and therefore toggles the LED
 * every x milliseconds.
 *
 *
 * The Demo Specific "Check" Callback Function:
 * This is called each time the 'check' timer expires.  The check timer
 * callback function inspects all the standard demo tasks to see if they are
 * all executing as expected.  The check timer is initially configured to
 * expire every three seconds, but will shorted this to every 500ms if an error
 * is ever discovered.
 *
 * The Demo Specific Idle Hook Function:
 * The idle hook function demonstrates how to query the amount of FreeRTOS heap
 * space that is remaining (see vApplicationIdleHook() defined in this file).
 *
 * The Web Server Task:
 * The IP address used by the SmartFusion target is configured by the
 * definitions configIP_ADDR0 to configIP_ADDR3, which are located in the
 * FreeRTOSConfig.h header file.
 */\

 /**************************************************************************/
 /* Standard Includes */
 /**************************************************************************/
#include <stdio.h>
#include <stdlib.h>


/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"

/* Microsemi drivers/libraries includes. */
#include "a2fxxxm3.h"
#include "mss_gpio.h"
#include "mss_timer.h"
#include "mss_uart.h"
#include "mss_ace.h"


#include "partest.h"

/* Priorities at which the tasks are created. */
#define mainQUEUE_RECEIVE_TASK_PRIORITY		( tskIDLE_PRIORITY + 2 )
#define	mainQUEUE_SEND_TASK_PRIORITY		( tskIDLE_PRIORITY + 1 )

/* The rate at which data is sent to the queue, specified in milliseconds, and
converted to ticks using the portTICK_PERIOD_MS constant. */
#define mainQUEUE_SEND_FREQUENCY_MS			( 1000 / portTICK_PERIOD_MS )

/* The number of items the queue can hold.  This is 1 as the receive task
will remove items as they are added, meaning the send task should always find
the queue empty. */
#define mainQUEUE_LENGTH			( 1 )

/* The LED toggled by the check timer callback function. */
#define mainCHECK_LED				0x07UL

/* The LED toggle by the queue receive task. */
#define mainTASK_CONTROLLED_LED		0x05UL

/* Priorities used by the various different tasks. */
#define mainuIP_TASK_PRIORITY		( tskIDLE_PRIORITY + 2 )

/* The WEB server uses string handling functions, which in turn use a bit more
stack than most of the other tasks. */
#define mainuIP_STACK_SIZE			( configMINIMAL_STACK_SIZE * 3 )

/* The period at which the check timer will expire, in ms, provided no errors
have been reported by any of the standard demo tasks. */
#define mainCHECK_TIMER_PERIOD_MS	( 3000UL / portTICK_PERIOD_MS )


/* The period at which the check timer will expire, in ms, if an error has been
reported in one of the standard demo tasks. */
#define mainERROR_CHECK_TIMER_PERIOD_MS ( 500UL / portTICK_PERIOD_MS )

/* A zero block time. */
#define mainDONT_BLOCK				( 0UL )
/*-----------------------------------------------------------*/

/*
 * Setup the NVIC, LED outputs, and button inputs.
 */
static void prvSetupHardware( void );

/*
 * The tasks as described in the comments at the top of this file.
 */
static void prvQueueReceiveTask( void *pvParameters );
static void prvQueueSendTask( void *pvParameters );

void uart_task(void *para);

/*
 * The check timer callback function, as described at the top of this file.
 */
static void prvCheckTimerCallback( TimerHandle_t xTimer );

/*
 * This is not a 'standard' partest function, so the prototype is not in
 * partest.h, and is instead included here.
 */
void vParTestSetLEDFromISR( unsigned portBASE_TYPE uxLED, signed portBASE_TYPE xValue );

/*
 * Contains the implementation of the WEB server.
 */
extern void vuIP_Task( void *pvParameters );

/*-----------------------------------------------------------*/

/* The queue used by both application specific demo tasks defined in this file. */
static QueueHandle_t xQueue = NULL;

/* The check timer.  This uses prvCheckTimerCallback() as it's callback
function. */
static TimerHandle_t xCheckTimer = NULL;

/* The status message that is displayed at the bottom of the "task stats" web
page, which is served by the uIP task.  This will report any errors picked up
by the check timer callback. */
static const char *pcStatusMessage = NULL;

/*-----------------------------------------------------------*/

//float                                 real_voltage_value;
//float                                 real_current_value;
//float                                 real_temperature_value_tc;
uint8_t                               key = 0;
uint8_t                               rx_size =0;
//volatile unsigned char                std_menu;
//volatile unsigned char                inMultimeter;

TaskHandle_t htTaskHndl = NULL;


#define System_logo \
"\n\r \
 _______________________________________\n\r \
/                                       \\n\r \
|  {###################################}  |\n\r \
|  {###################################}  |\n\r \
|  {###################################}  |\n\r \
|  {###################################}  |\n\r \
|  {###################################}  |\n\r \
|  {###################################}  |\n\r \
|                                         |\n\r \
|               80  90  100               |\n\r \
|            70     ^      120            |\n\r \
|        60 *      /|\       * 140        |\n\r \
|    55             |              160    |\n\r \
|                   |                     |\n\r \
|                   |                     |\n\r \
|   (O)            (+)              (O)   |\n\r \
\_______________________________________/"





int main(void)
{
	/* Configure the NVIC, LED outputs and button inputs. */
	prvSetupHardware();

	/* Create the queue. */
	xQueue = xQueueCreate( mainQUEUE_LENGTH, sizeof( unsigned long ) );

	if( xQueue != NULL )
	{

		xTaskCreate( prvQueueReceiveTask, "Rx", configMINIMAL_STACK_SIZE, NULL, mainQUEUE_RECEIVE_TASK_PRIORITY, NULL );
		xTaskCreate( prvQueueSendTask, "TX", configMINIMAL_STACK_SIZE, NULL, mainQUEUE_SEND_TASK_PRIORITY, NULL );



		//printf( "\n\r********* Welcome to the Measurement System  *********\n\r" );


		/* Create the software timer that performs the 'check' functionality,
		as described at the top of this file. */
		xCheckTimer = xTimerCreate( "CheckTimer",					/* A text name, purely to help debugging. */
									( mainCHECK_TIMER_PERIOD_MS ),	/* The timer period, in this case 3000ms (3s). */
									pdTRUE,							/* This is an auto-reload timer, so xAutoReload is set to pdTRUE. */
									( void * ) 0,					/* The ID is not used, so can be set to anything. */
									prvCheckTimerCallback			/* The callback function that inspects the status of all the other tasks. */
								  );

		/* Create the web server task. */
		xTaskCreate( vuIP_Task, "uIP", mainuIP_STACK_SIZE, NULL, mainuIP_TASK_PRIORITY, NULL );

		xTaskCreate( uart_task, "uart_task" ,( unsigned short ) 512 , NULL, tskIDLE_PRIORITY+1, NULL);


		/* Start the tasks and timer running. */
		vTaskStartScheduler();
	}

	/* If all is well, the scheduler will now be running, and the following line
	will never be reached.  If the following line does execute, then there was
	insufficient FreeRTOS heap memory available for the idle and/or timer tasks
	to be created.  See the memory management section on the FreeRTOS web site
	for more details. */
	for( ;; );
}
/*-----------------------------------------------------------*/




static void prvCheckTimerCallback( TimerHandle_t xTimer )
{
	/* Check the standard demo tasks are running without error.   Latch the
	latest reported error in the pcStatusMessage character pointer. */

	/* Have any errors been latch in pcStatusMessage?  If so, shorten the
	period of the check timer to mainERROR_CHECK_TIMER_PERIOD_MS milliseconds.
	This will result in an increase in the rate at which mainCHECK_LED
	toggles. */
	if( pcStatusMessage != NULL )
	{
		/* This call to xTimerChangePeriod() uses a zero block time.  Functions
		called from inside of a timer callback function must *never* attempt
		to block. */
		xTimerChangePeriod( xCheckTimer, ( mainERROR_CHECK_TIMER_PERIOD_MS ), mainDONT_BLOCK );
	}
}
/*-----------------------------------------------------------*/


/*-----------------------------------------------------------*/

/* The ISR executed when the user button is pushed. */
void GPIO8_IRQHandler( void )
{
portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;

//DO SOMETHING IF INTERUPTED BY BUTTON ON GPIO8 (SW1)


	/* Clear the interrupt before leaving. */
    MSS_GPIO_clear_irq( MSS_GPIO_8 );

	/* If calling xTimerResetFromISR() caused a task (in this case the timer
	service/daemon task) to unblock, and the unblocked task has a priority
	higher than or equal to the task that was interrupted, then
	xHigherPriorityTaskWoken will now be set to pdTRUE, and calling
	portEND_SWITCHING_ISR() will ensure the unblocked task runs next. */
	portEND_SWITCHING_ISR( xHigherPriorityTaskWoken );
}
/*-----------------------------------------------------------*/

static void prvQueueSendTask( void *pvParameters )
{
TickType_t xNextWakeTime;
const unsigned long ulValueToSend = 100UL;

	/* The timer command queue will have been filled when the timer test tasks
	were created in main() (this is part of the test they perform).  Therefore,
	while the check timer can be created in main(), it cannot be started from
	main().  Once the scheduler has started, the timer service task will drain
	the command queue, and now the check timer can be started successfully. */
	xTimerStart( xCheckTimer, portMAX_DELAY );

	/* Initialise xNextWakeTime - this only needs to be done once. */
	xNextWakeTime = xTaskGetTickCount();

	for( ;; )
	{
		/* Place this task in the blocked state until it is time to run again.
		The block time is specified in ticks, the constant used converts ticks
		to ms.  While in the Blocked state this task will not consume any CPU
		time. */
		vTaskDelayUntil( &xNextWakeTime, mainQUEUE_SEND_FREQUENCY_MS );

		/* Send to the queue - causing the queue receive task to unblock and
		toggle an LED.  0 is used as the block time so the sending operation
		will not block - it shouldn't need to block as the queue should always
		be empty at this point in the code. */
		xQueueSend( xQueue, &ulValueToSend, mainDONT_BLOCK );
	}
}
/*-----------------------------------------------------------*/

static void prvQueueReceiveTask( void *pvParameters )
{
unsigned long ulReceivedValue;

	for( ;; )
	{
		/* Wait until something arrives in the queue - this task will block
		indefinitely provided INCLUDE_vTaskSuspend is set to 1 in
		FreeRTOSConfig.h. */
		xQueueReceive( xQueue, &ulReceivedValue, portMAX_DELAY );

		/*  To get here something must have been received from the queue, but
		is it the expected value?  If it is, toggle the LED. */
		if( ulReceivedValue == 100UL )
		{
			vParTestToggleLED( mainTASK_CONTROLLED_LED );
		}
	}
}
/*-----------------------------------------------------------*/


static void prvSetupHardware( void )
{
	SystemCoreClockUpdate();


	/* Configure the GPIO for the LEDs. */
	vParTestInitialise();

    MSS_UART_init
    (
        &g_mss_uart0,
        MSS_UART_57600_BAUD,
        MSS_UART_DATA_8_BITS | MSS_UART_NO_PARITY | MSS_UART_ONE_STOP_BIT
    );

	/* ACE Initialization */
	ACE_init();

	/* Setup the GPIO and the NVIC for the switch used in this simple demo. */
	NVIC_SetPriority( GPIO8_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY );
    NVIC_EnableIRQ( GPIO8_IRQn );
    MSS_GPIO_config( MSS_GPIO_8, MSS_GPIO_INPUT_MODE | MSS_GPIO_IRQ_EDGE_NEGATIVE );
    MSS_GPIO_enable_irq( MSS_GPIO_8 );
}
/*-----------------------------------------------------------*/

void vApplicationMallocFailedHook( void )
{
	/* Called if a call to pvPortMalloc() fails because there is insufficient
	free memory available in the FreeRTOS heap.  pvPortMalloc() is called
	internally by FreeRTOS API functions that create tasks, queues, software
	timers, and semaphores.  The size of the FreeRTOS heap is set by the
	configTOTAL_HEAP_SIZE configuration constant in FreeRTOSConfig.h. */
	for( ;; );
}
/*-----------------------------------------------------------*/

void vApplicationStackOverflowHook( TaskHandle_t pxTask, char *pcTaskName )
{
	( void ) pcTaskName;
	( void ) pxTask;

	/* Run time stack overflow checking is performed if
	configconfigCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook
	function is called if a stack overflow is detected. */
	taskDISABLE_INTERRUPTS();
	for( ;; );
}
/*-----------------------------------------------------------*/

void vApplicationIdleHook( void )
{
volatile size_t xFreeStackSpace;

	/* This function is called on each cycle of the idle task.  In this case it
	does nothing useful, other than report the amount of FreeRTOS heap that
	remains unallocated. */
	xFreeStackSpace = xPortGetFreeHeapSize();

	if( xFreeStackSpace > 100 )
	{
		/* By now, the kernel has allocated everything it is going to, so
		if there is a lot of heap remaining unallocated then
		the value of configTOTAL_HEAP_SIZE in FreeRTOSConfig.h can be
		reduced accordingly. */
	}
}
/*-----------------------------------------------------------*/

char *pcGetTaskStatusMessage( void )
{
	/* Not bothered about a critical section here although technically because
	of the task priorities the pointer could change it will be atomic if not
	near atomic and its not critical. */
	if( pcStatusMessage == NULL )
	{
		return "All tasks running without error";
	}
	else
	{
		return ( char * ) pcStatusMessage;
	}
}
/*-----------------------------------------------------------*/

void vMainConfigureTimerForRunTimeStats( void )
{
const unsigned long ulMax32BitValue = 0xffffffffUL;

	MSS_TIM64_init( MSS_TIMER_PERIODIC_MODE );
	MSS_TIM64_load_immediate( ulMax32BitValue, ulMax32BitValue );
	MSS_TIM64_start();
}
/*-----------------------------------------------------------*/

unsigned long ulGetRunTimeCounterValue( void )
{
	return 0UL;
}


void uart_task(void *para)
{
const uint8_t intro[] = "\n\r \
********* Welcome to the Measurement System  *********\n\r \
\n\r \
********* Please select option **************\n\r \
********* 0.  Multimeter *********************\n\r \
";

	MSS_UART_polled_tx_string( &g_mss_uart0, (const uint8_t *)System_logo);
	MSS_UART_polled_tx( &g_mss_uart0, intro, sizeof(intro) );

	for( ;; )
		{

		}

}
