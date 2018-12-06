#ifndef RPI_XMOS_TAS_INTEGRATION_H
#define RPI_XMOS_TAS_INTEGRATION_H

/*************************************
FUNCTION DECLARATIONS
 *************************************/
int initialize();
int wiringPi_init();
void myInterrupt0(void);


#define IDLE     0xFF
#define PWR      0x01
#define SRC      0x02
#define VOL_UP   0x04
#define VOL_DOWN 0x08

#define OPT_SRC 0
#define AUX_SRC 1

#define PWR_OFF 0
#define PWR_ON 1

#define LED_DISPLAY_OFF 0
#define LED_DISPLAY_ON 1

#define AVS_OFF 0
#define AVS_ON 1

#define NO_ERROR 0
#define ERROR_DETECTED 1

#define LED_TIMER_MS 2000

#define MAX_VOL 15
#define MIN_VOL 0

#endif //RPI_XMOS_TAS_INTEGRATION_H
