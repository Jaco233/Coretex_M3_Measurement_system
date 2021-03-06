/*****************************************************************************
* (c) Copyright  Actel Corporation. All rights reserved.
*
*ACE configuration .c file
*Created by Actel MSS_ACE Configurator Wed Oct 10 15:22:40 2018
*
*/

#include "../../drivers/mss_ace/mss_ace_configurator.h"
#include "ace_config.h"
#include "ace_handles.h"

#include <stdint.h>


#ifdef __cplusplus
extern "C" {
#endif

/*-----------------------------------------------------------------------------
*AB Configuration
*---------------------------------------------------------------------------*/
ace_adc_config_t g_ace_adc_config[ACE_NB_OF_ADC] = 
{
	{
        4096,                      /* uint16_t adc_resolution */
        2560                       /* uint16_t va_ref */
	},
	{
        4096,                      /* uint16_t adc_resolution */
        2560                       /* uint16_t va_ref */
	}
};

/*-----------------------------------------------------------------------------
*Current Monitor External Resistor Value ( milli-ohms )
*---------------------------------------------------------------------------*/
const uint16_t g_ace_current_resistors[ACE_NB_OF_CURRENT_MONITORS] = 
{
	100000,	/*CM0 ( USED AS CURRENT MONITOR ) */
	1,	/*CM1 ( NOT USED AS CURRENT MONITOR ) */
	1,	/*CM2 ( NOT USED AS CURRENT MONITOR ) */
	1	/*CM3 ( NOT USED AS CURRENT MONITOR ) */
};

/*-----------------------------------------------------------------------------
*External VAREF usage
*---------------------------------------------------------------------------*/
const uint8_t g_ace_external_varef_used[ACE_NB_OF_ADC] = 
{
	0,
	0
};

/*-----------------------------------------------------------------------------
*Analog Channels
*---------------------------------------------------------------------------*/
/* Names*/
const uint8_t g_ace_channel_0_name[] = "CurrentMonitor_0";
const uint8_t g_ace_channel_1_name[] = "VoltageMonitor_0";
const uint8_t g_ace_channel_2_name[] = "ExtAnalogTemp";
const uint8_t g_ace_channel_3_name[] = "ExtAnalogHumid";
const uint8_t g_ace_channel_4_name[] = "TemperatureMonitor_0";
const uint8_t g_ace_channel_5_name[] = "ExtAnalogUV";
const uint8_t g_ace_channel_6_name[] = "ExtAnalogLight";

/* Number of Flags per Channel*/
#define CHANNEL_0_NB_OF_FLAGS           0
#define CHANNEL_1_NB_OF_FLAGS           0
#define CHANNEL_2_NB_OF_FLAGS           0
#define CHANNEL_3_NB_OF_FLAGS           0
#define CHANNEL_4_NB_OF_FLAGS           0
#define CHANNEL_5_NB_OF_FLAGS           0
#define CHANNEL_6_NB_OF_FLAGS           0

/* Input Channel to Flag Array Association*/

/* Channel Table*/
ace_channel_desc_t g_ace_channel_desc_table[ACE_NB_OF_INPUT_CHANNELS] = 
{
	{
        g_ace_channel_0_name,      /* const uint8_t * p_sz_channel_name */
        CM0,                       /* adc_channel_id_t signal_id; */
        16,                        /* uint16_t signal_ppe_offset */
        CHANNEL_0_NB_OF_FLAGS,     /* uint16_t nb_of_flags */
        0                          /* uint16_t * p_flags_array */
	},
	{
        g_ace_channel_1_name,      /* const uint8_t * p_sz_channel_name */
        TM0,                       /* adc_channel_id_t signal_id; */
        25,                        /* uint16_t signal_ppe_offset */
        CHANNEL_1_NB_OF_FLAGS,     /* uint16_t nb_of_flags */
        0                          /* uint16_t * p_flags_array */
	},
	{
        g_ace_channel_2_name,      /* const uint8_t * p_sz_channel_name */
        ABPS2,                     /* adc_channel_id_t signal_id; */
        34,                        /* uint16_t signal_ppe_offset */
        CHANNEL_2_NB_OF_FLAGS,     /* uint16_t nb_of_flags */
        0                          /* uint16_t * p_flags_array */
	},
	{
        g_ace_channel_3_name,      /* const uint8_t * p_sz_channel_name */
        ABPS3,                     /* adc_channel_id_t signal_id; */
        43,                        /* uint16_t signal_ppe_offset */
        CHANNEL_3_NB_OF_FLAGS,     /* uint16_t nb_of_flags */
        0                          /* uint16_t * p_flags_array */
	},
	{
        g_ace_channel_4_name,      /* const uint8_t * p_sz_channel_name */
        TM1,                       /* adc_channel_id_t signal_id; */
        52,                        /* uint16_t signal_ppe_offset */
        CHANNEL_4_NB_OF_FLAGS,     /* uint16_t nb_of_flags */
        0                          /* uint16_t * p_flags_array */
	},
	{
        g_ace_channel_5_name,      /* const uint8_t * p_sz_channel_name */
        ABPS6,                     /* adc_channel_id_t signal_id; */
        61,                        /* uint16_t signal_ppe_offset */
        CHANNEL_5_NB_OF_FLAGS,     /* uint16_t nb_of_flags */
        0                          /* uint16_t * p_flags_array */
	},
	{
        g_ace_channel_6_name,      /* const uint8_t * p_sz_channel_name */
        ABPS7,                     /* adc_channel_id_t signal_id; */
        70,                        /* uint16_t signal_ppe_offset */
        CHANNEL_6_NB_OF_FLAGS,     /* uint16_t nb_of_flags */
        0                          /* uint16_t * p_flags_array */
	}
};

/*-----------------------------------------------------------------------------
*Threshold Flags
*---------------------------------------------------------------------------*/
/* Flag Names*/
/* Flag Table*/


/*-----------------------------------------------------------------------------
*PPE Linear Transforms
*---------------------------------------------------------------------------*/
const ppe_transforms_desc_t g_ace_ppe_transforms_desc_table[ACE_NB_OF_INPUT_CHANNELS] = 
{
	{
        18,                        /* uint16_t    m_ppe_offset */
        19,                        /* uint16_t    c_ppe_offset */
        0x4000,                    /* int16_t     default_m2 */
        0x0000                     /* int16_t     default_c2 */
	},
	{
        27,                        /* uint16_t    m_ppe_offset */
        28,                        /* uint16_t    c_ppe_offset */
        0x4000,                    /* int16_t     default_m2 */
        0x0000                     /* int16_t     default_c2 */
	},
	{
        36,                        /* uint16_t    m_ppe_offset */
        37,                        /* uint16_t    c_ppe_offset */
        0xc000,                    /* int16_t     default_m2 */
        0xffff                     /* int16_t     default_c2 */
	},
	{
        45,                        /* uint16_t    m_ppe_offset */
        46,                        /* uint16_t    c_ppe_offset */
        0xc000,                    /* int16_t     default_m2 */
        0xffff                     /* int16_t     default_c2 */
	},
	{
        54,                        /* uint16_t    m_ppe_offset */
        55,                        /* uint16_t    c_ppe_offset */
        0x4000,                    /* int16_t     default_m2 */
        0x0000                     /* int16_t     default_c2 */
	},
	{
        63,                        /* uint16_t    m_ppe_offset */
        64,                        /* uint16_t    c_ppe_offset */
        0xc000,                    /* int16_t     default_m2 */
        0xffff                     /* int16_t     default_c2 */
	},
	{
        72,                        /* uint16_t    m_ppe_offset */
        73,                        /* uint16_t    c_ppe_offset */
        0xc000,                    /* int16_t     default_m2 */
        0xffff                     /* int16_t     default_c2 */
	}
};

/*-----------------------------------------------------------------------------
*Sequencer Procedures
*---------------------------------------------------------------------------*/
/* Procedure Name and Microcode*/
const uint8_t g_ace_sse_proc_0_name[] = "ADC0_MAIN";
const uint16_t g_ace_sse_proc_0_sequence[] = 
{
	0x1705, 0x1601, 0x152d, 0x8a0c, 
	0x1309, 0x0000, 0x14c3, 0x0000, 
	0x8a04, 0x155c, 0x14c4, 0x0000, 
	0x155c, 0x14c5, 0x0000, 0x152d, 
	0x970c, 0x132f, 0x0000, 0x14c8, 
	0x0000, 0x9704, 0x155c, 0x14c6, 
	0x0000, 0x1002 
};

const uint8_t g_ace_sse_proc_1_name[] = "ADC1_MAIN";
const uint16_t g_ace_sse_proc_1_sequence[] = 
{
	0x2705, 0x2601, 0x255c, 0x24c5, 
	0x0000, 0x255c, 0x24c6, 0x0000, 
	0x201c 
};



/* Procedure Table*/
ace_procedure_desc_t g_sse_sequences_desc_table[ACE_NB_OF_SSE_PROCEDURES] = 
{
	{
        g_ace_sse_proc_0_name,                              /* const uint8_t * p_sz_proc_name */
        2,                                                  /* uint16_t sse_loop_pc */
        0,                                                  /* uint16_t sse_load_offset */
        sizeof(g_ace_sse_proc_0_sequence) / sizeof(uint16_t), /* uint16_t sse_ucode_length */
        g_ace_sse_proc_0_sequence,                          /* const uint16_t * sse_ucode */
        0                                                   /* uint8_t sse_pc_id */
	},
	{
        g_ace_sse_proc_1_name,                              /* const uint8_t * p_sz_proc_name */
        28,                                                 /* uint16_t sse_loop_pc */
        26,                                                 /* uint16_t sse_load_offset */
        sizeof(g_ace_sse_proc_1_sequence) / sizeof(uint16_t), /* uint16_t sse_ucode_length */
        g_ace_sse_proc_1_sequence,                          /* const uint16_t * sse_ucode */
        1                                                   /* uint8_t sse_pc_id */
	}
};


#ifdef __cplusplus
}
#endif

