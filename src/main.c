#include "rpi_xmos_tas_integration.h"
#include "UI_functions.h"
#include "LED_functions.h"
#include "TAS_functions.h"

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
    state.error_detect = NO_ERROR

    LED_ENABLE();
    state.led_display_active = LED_DISPLAY_ON;
    LED_TIMER = LED_TIMER_MS;      
    
    UI_PWR(PWR_ON);    
    UI_VOL(MUTE);
    UI_SRC(AUX_SRC);
    
    
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
            }
            LED_TIMER--;
        }
    }    
}

void myInterrupt0(void) {
    status = (char)readPCA9554();   
}

int main()
{
    initialize();
    char startLedTimerThread = piThreadCreate(LED_TIMER_THREAD);
    
    status = IDLE;

    while(1) {
    
        if(status != IDLE) 
        {
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
                        if(UI_VOL(state.volume - 1)) state.volume--;
                    } else
                    {
                        LED_OUT_OF_RANGE();
                    }
                    break;
                    
                case SRC:
                    if(state.avs_active != ACTIVE)
                    {
                        if(UI_SRC(state.source ^ 1)) state.source ^= 1;
                    }
                    break;
                    
                default:
                    UI_ERROR();
                    break;    
            }    
            status = IDLE;
        }
    }
 
    return 0;
}