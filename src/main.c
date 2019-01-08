/*****************************************************************
INCLUDES
*****************************************************************/
#include "rpi_xmos_tas_integration.h"
#include "UI_functions.h"
#include "LED_functions.h"
#include "TAS_functions.h"

#include "debug.h"
#include "script.h"

#include "wiringPi.h"

#include <string.h>
#include <stdint.h>

/*****************************************************************
LOCAL VARIABLES
*****************************************************************/
struct States {
    uint8_t status;
    uint8_t power;
    uint8_t source;
    uint8_t volume;
    uint8_t avs_active;
    uint8_t led_display_active;
    uint8_t debounce_active;
    uint8_t error_detect;
} state;

volatile int LED_TIMER = 0;
volatile uint8_t startDebounceThread;
volatile uint8_t startLedTimerThread;
char script_filename[50];
FILE *fp_script = NULL;
FILE *fp_log = NULL;

/*************************************
INTERNAL FUNCTION DECLARATIONS
 *************************************/
int initialize();
int wiringPi_init();
void myInterrupt0(void);
int option_handler(int argc, char *argv[]);
int avs_detect();
int exit_fn();
int start_LED_timer();


/*****************************************************************
THREAD FUNCTIONS
*****************************************************************/
PI_THREAD(LED_TIMER_THREAD)
{   
    while(LED_TIMER > 0)
    {
	    state.led_display_active = 1;
	    delay(1);
	    if(LED_TIMER == 1)
	    {
	        state.led_display_active = 0;
	        LED_PWR(PWR_ON);

	        if(DEBUG_OPT) debug_out(DEBUG_OPT,
		             		        "timer_thread",
				                    "timer expired");
	    }
	    LED_TIMER--;
    }
}

PI_THREAD(BUTTON_DEBOUNCE)
{
    state.debounce_active = 1;
    if(DEBUG_OPT) debug_out(DEBUG_OPT,
           		    "DEBOUNCE_THREAD",
			    "*****DEBOUNCE ON*****");
    delay(DEBOUNCE_TIME_MS);
    state.debounce_active = 0;
    if(DEBUG_OPT) debug_out(DEBUG_OPT,
   			    "DEBOUNCE_THREAD",
			    "*****DEBOUNCE CLEARED*****");
    
}


/*****************************************************************
MAIN()
*****************************************************************/
int main(int argc, char *argv[])
{
    char script_string[MAX_SCRIPT_LINE];

    //Run option_handler() to set desired scripting and debug
    //options from command line input
    if(option_handler(argc, argv))
    {
	    printf("OPTION ERROR\n");
	    exit_fn();
	    return 1;
    }

    if(SCRIPT_OPT && DEBUG_OPT)
    {
        sprintf(debug_msg, "running script: %s", script_filename);
        debug_out(DEBUG_OPT, "main", debug_msg);
    }
    //Initialize hardware, wiringPi, and initial system state
    initialize();


    /*********************************
    BEGIN UI LOOP
    **********************************/
    while(1) {

	if(digitalRead(2))  avs_detect();

        //load next command if running from script
        if(SCRIPT_OPT)
        {
            if(fscanf(fp_script, "%s", script_string) == EOF)
            {
                if(DEBUG_OPT) debug_out(DEBUG_OPT,
                            "main_loop",
                            "end of script");
                exit_fn();
                return 0;
            }
            
            state.status = script_translate(script_string);
            
            if(state.status == -1)
            {
                printf("Invalid Scripting command\n");
                exit_fn();
                return 1;
            }
        }

        //if status has changed process the input        
        if((state.status != IDLE) && (!state.debounce_active)) 
        {
            startDebounceThread = piThreadCreate(BUTTON_DEBOUNCE);
            
            //if running from script delay for obseravtion
            if(SCRIPT_OPT) delay(SCRIPT_DELAY_MS);

            if(DEBUG_OPT)
            {
                sprintf(debug_msg, "status = %d", state.status);
                debug_out(DEBUG_OPT, "main_switch", debug_msg);
            }     


            switch(state.status) 
            {
		    /////////////////////////////////////////////////////
                case PWR :
                    if(!UI_PWR(state.power ^ 1)) state.power ^= 1;
                    break;
		    /////////////////////////////////////////////////////                    
                case VOL_UP:
                    while((uint8_t)readPCA9554() == VOL_UP)
                    {
                        if(state.volume < MAX_VOL)
                        {
                            if(!UI_VOL(state.volume + 1)) state.volume++;
                        } else
                        {
                            LED_OUT_OF_RANGE();
                            UI_VOL(state.volume);
                        }
                        delay(VOL_REPEAT_DELAY_MS);
                    }
                    break;
		    /////////////////////////////////////////////////////
                case VOL_DOWN:
                    while((uint8_t)readPCA9554() == VOL_DOWN)
                    {
                        if(state.volume > MIN_VOL)
                        {
                            if(!UI_VOL(state.volume - 1)) state.volume--;
                        } else
                        {
                            LED_OUT_OF_RANGE();
                        }
                        delay(VOL_REPEAT_DELAY_MS);
                    }
                    break;
		    /////////////////////////////////////////////////////
                case SRC:
                    if(!state.avs_active)
                    {
                        if(!UI_SRC(state.source ^ 1)) state.source ^= 1;
                    }
                    break;
		    /////////////////////////////////////////////////////
                default:
                    UI_ERROR();
                    break;    
            }

	        if(DEBUG_OPT) debug_out(DEBUG_OPT,
				                    "main_switch",
				                    "returning to idle\n\n\n");
            state.status = IDLE;
        }
    }
    /************************************************
     END - UI LOOP
     ***********************************************/

    return 0;
}

/*****************************************************************
LOCAL FUNCTIONS
*****************************************************************/
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
    state.debounce_active = DEBOUNCE_OFF;
    state.error_detect = NO_ERROR;
    
    UI_VOL(MUTE);
    UI_SRC(AUX_SRC);

    LED_ENABLE();    
    UI_PWR(PWR_ON);
    
    if(DEBUG_OPT) debug_out(DEBUG_OPT,
			    "initialize",
			    "end of init\n\n\n");
    
    state.status = IDLE;
    
    // add a button READ during init to clear 
    // any interrupts on boot
    readPCA9554(); 

    return 0;
}

int wiringPi_init()
{
    wiringPiSetup();
    wiringPiISR (4, INT_EDGE_FALLING, &myInterrupt0) ;
    pinMode(5, OUTPUT);
    digitalWrite(5, HIGH);
    
    return 0;
}


void myInterrupt0(void) {
 
    state.status = (uint8_t)readPCA9554(); 
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

int avs_detect()
{
    UI_VOL(DEFAULT_AVS_VOLUME);

    if(DEBUG_OPT) debug_out(DEBUG_OPT,
	         	    "AVS_detect_thread",
			    "*****AVS ACITVE*****");
    while(digitalRead(2))
    {
        LED_AVS_ACTIVE();
	start_LED_timer();
    }

    if(DEBUG_OPT) debug_out(DEBUG_OPT,
	         	    "AVS_detect_thread",
			    "*****AVS FINISHED*****");
    UI_VOL(state.volume);

    return 0;
}

int exit_fn()
{
    if((DEBUG_OPT == 2) || (DEBUG_OPT == 3)) debug_file_close;
    if(SCRIPT_OPT) fclose(fp_script);

    return 0;
}

int start_LED_timer()
{
    LED_TIMER = LED_TIMER_MS;           
    if(!state.led_display_active)
    {
	startLedTimerThread = piThreadCreate(LED_TIMER_THREAD);
    } 

    return 0;
}
