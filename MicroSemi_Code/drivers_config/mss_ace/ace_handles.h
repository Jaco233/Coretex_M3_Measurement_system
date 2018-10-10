/*****************************************************************************
* (c) Copyright  Actel Corporation. All rights reserved.
*
*ACE configuration .h file
*Created by Actel MSS_ACE Configurator Tue Oct 09 15:14:59 2018
*
*/

#ifndef ACE_HANDLES_H
#define ACE_HANDLES_H


#ifdef __cplusplus
extern "C" {
#endif

/*-----------------------------------------------------------------------------
*Analog input channel handles
*---------------------------------------------------------------------------*/
typedef enum {
    CurrentMonitor_0 = 0,
    VoltageMonitor_0,
    TemperatureMonitor_0,
    ExtAnalogSensor_1,
    NB_OF_ACE_CHANNEL_HANDLES
} ace_channel_handle_t;

/*-----------------------------------------------------------------------------
*Flag Handles
*---------------------------------------------------------------------------*/
typedef enum {
    NB_OF_ACE_FLAG_HANDLES = 0
} ace_flag_handle_t;

/*-----------------------------------------------------------------------------
*Procedure Handles
*---------------------------------------------------------------------------*/
typedef enum {
    ADC0_MAIN = 0,
    ADC1_MAIN,
    NB_OF_ACE_PROCEDURE_HANDLES
} ace_procedure_handle_t;

#ifdef __cplusplus
}
#endif


#endif /* ACE_HANDLES_H*/
