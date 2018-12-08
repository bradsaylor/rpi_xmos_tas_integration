#include "rpi_xmos_tas_integration.h"
#include "UI_functions.h"
#include "LED_functions.h"
#include "TAS_functions.h"
#include "wiringPi.h"
#include "debug.h"
#include "script.h"
#include <string.h>

struct States {
    char power;
    char source;
    char volume;
    char avs_active;
    char led_display_active;
    char error_detect;
} state;

volatile char status = IDLE;
volatile int LED_TIMER = 0;
volatile char DEBOUNCE_ON = 0;
char script_filename[50];
FILE *fp_script = NULL;
FILE *fp_log = NULL;

int initialize()
{
    wiringPi_init();
    TAS_init();
    Buttons_init();
    LED_init();
    
    state.power = PWR_ON;
    state.source = AUX_SRC;
    state.volume = MUTE;
    state.avs_active = AVS_OFF;
    state.led_display_active = LED_DISPLAY_OFF;
    state.error_detect = NO_ERROR;

    LED_ENABLE();
    state.led_display_active = LED_DISPLAY_ON;
    LED_TIMER = LED_TIMER_MS;      
    
    UI_PWR(PWR_ON);    
    UI_VOL(MUTE);
    UI_SRC(AUX_SRC);
    
    if(DEBUG_OPT) debug_out(DEBUG_OPT, "initialize", "end of init\n\n\n");
    
    return 0;
}

int wiringPi_init()
{
    wiringPiSetup();
    wiringPiISR (4, INT_EDGE_FALLING, &myInterrupt0) ;
    
    return 0;
}

PI_THREAD(LED_TIMER_THREAD)
{   
    while(1)
    {
        while(LED_TIMER > 0)
        { 
            delay(1);
            if(LED_TIMER == 1)
            {
                LED_PWR(PWR_ON);

                if(DEBUG_OPT) debug_out(DEBUG_OPT, "timer_thread", "timer expired");
            }
            LED_TIMER--;
        }
    }    
}

PI_THREAD(BUTTON_DEBOUNCE)
{
    while(1)
    {
        if(DEBOUNCE_ON)
        {
            printf("delaying\n");
            delay(15);
            DEBOUNCE_ON = 0;
            printf("debounce cleared\n");
        }
    }

}

void myInterrupt0(void) {
 
    status = (char)readPCA9554(); 
    if(DEBUG_OPT) debug_out(DEBUG_OPT, "INT", "***<BUTTON PRESS>***"); 
}

int option_handler(int argc, char *argv[])
{
    if(argc > 1)
    {
	if(!strcmp(argv[1], "-ds"))
	{
	    DEBUG_OPT = 1;  
	}
	else if(!strcmp(argv[1], "-df"))
	{
	    DEBUG_OPT = 2;
	    debug_file_init();
	}
	else if(!strcmp(argv[1], "-dsf"))
	{
	    DEBUG_OPT = 3;
	    debug_file_init();
	}
	else
	{
	    printf("invalid options...exiting");
	    return 1;
	}
    }
    if(argc > 2)
    {
	fp_script = fopen(argv[2], "r");
	strcpy(script_filename, argv[2]);

	SCRIPT_OPT = 1;
    }
    return 0;
}

int main(int argc, char *argv[])
{
    char script_string[MAX_SCRIPT_LINE];

    if(option_handler(argc, argv)) return 1;

    if(SCRIPT_OPT && DEBUG_OPT)
    {
        sprintf(debug_msg, "running script: %s", script_filename);
        if(DEBUG_OPT) debug_out(DEBUG_OPT, "main", debug_msg);
    }
    
    initialize();

    if(DEBUG_OPT) debug_out(DEBUG_OPT, "main", "starting LED timer");
    char startLedTimerThread = piThreadCreate(LED_TIMER_THREAD);
    char startDebounceThread = piThreadCreate(BUTTON_DEBOUNCE);
    
    status = IDLE;

    while(1) {
	
        if(SCRIPT_OPT)
        {
            if(fscanf(fp_script, "%s", script_string) == EOF)
	    {
		if(DEBUG_OPT) debug_out(DEBUG_OPT, "main_loop", "end of script");
		return 0;
	    }
	    
	    status = script_translate(script_string);
	    
	    if(status == -1)
	    {
		debug_out(DEBUG_OPT, "main", "invalid script command..exiting");
		return 1;
	    }
        }
        
        if((status != IDLE) && (!DEBOUNCE_ON)) 
        {
            //delay(500);

            DEBOUNCE_ON = 1;
	    
	    if(DEBUG_OPT)
	    {
		sprintf(debug_msg, "status = %d", status);
		debug_out(DEBUG_OPT, "main_switch", debug_msg);
	    }
		
            LED_ENABLE();
            state.led_display_active = LED_DISPLAY_ON;
            LED_TIMER = LED_TIMER_MS;           

            switch(status) 
            {
                case PWR :
                    if(!UI_PWR(state.power ^ 1)) state.power ^= 1;
                    break;
                    
                case VOL_UP:
                    if(state.volume < MAX_VOL)
                    {
                        if(!UI_VOL(state.volume + 1)) state.volume++;
                    } else
                    {
                        LED_OUT_OF_RANGE();
                    }
                    break;
                    
                case VOL_DOWN:
                    if(state.volume > MIN_VOL)
                    {
                        if(!UI_VOL(state.volume - 1)) state.volume--;
                    } else
                    {
                        LED_OUT_OF_RANGE();
                    }
                    break;
                    
                case SRC:
                    if(state.avs_active != AVS_ON)
                    {
                        if(!UI_SRC(state.source ^ 1)) state.source ^= 1;
                    }
                    break;
                    
                default:
                    UI_ERROR();
                    break;    
            }

	    if(DEBUG_OPT) debug_out(DEBUG_OPT, "main_switch", "returning to idle\n\n\n");
            status = IDLE;
        }
    }
 
    return 0;
}
