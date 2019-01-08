#ifndef RPI_XMOS_TAS_INTEGRATION_H
#define RPI_XMOS_TAS_INTEGRATION_H

#include <stdio.h>

/*************************************
Global Variables
 *************************************/
extern FILE *fp_log;

/*************************************
MACROS
 *************************************/
#define IDLE     0xFF
#define PWR      0x0E
#define SRC      0x0D
#define VOL_UP   0x0B
#define VOL_DOWN 0x07

#define OPT_SRC 0
#define AUX_SRC 1

#define PWR_OFF 0
#define PWR_ON 1

#define LED_DISPLAY_OFF 0
#define LED_DISPLAY_ON 1

#define AVS_OFF 0
#define AVS_ON 1

#define DEBOUNCE_OFF 0
#define DEBOUNCE_ON 1

#define NO_ERROR 0
#define ERROR_DETECTED 1

#define LED_TIMER_MS 4000

#define MAX_VOL 15
#define MIN_VOL 0

#define DEBOUNCE_TIME_MS 300
#define SCRIPT_DELAY_MS 500
#define VOL_REPEAT_DELAY_MS 150

#define I2C_DEBUG 0
#endif //RPI_XMOS_TAS_INTEGRATION_H
