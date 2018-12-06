#include "LED_functions.h"
#include "rpi_xmos_tas_integration.h"
#include "i2c.h"

const char PWM_REG[16] = {0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9,
			  0xA, 0xB, 0xC, 0xD, 0xE, 0xF, 0x10, 0x11};

int LED_init()
{
    i2c_write(TLC59116_ADDR, MODE1_REG, MODE1_REG_DEFAULT);
    i2c_write(TLC59116_ADDR, MODE2_REG, MODE2_REG_DEFAULT);

    i2c_write(TLC59116_ADDR, LED_OUT_0_REG, LED_OUT_0_REG_DEFAULT); 
    i2c_write(TLC59116_ADDR, LED_OUT_1_REG, LED_OUT_1_REG_DEFAULT);
    i2c_write(TLC59116_ADDR, LED_OUT_2_REG, LED_OUT_2_REG_DEFAULT);
    i2c_write(TLC59116_ADDR, LED_OUT_3_REG, LED_OUT_3_REG_DEFAULT);    
    
    for(int count = 0; count < 16; count++)
    {
        i2c_write(TLC59116_ADDR, PWM_REG[count], PWM_REG_DEFAULT);
    }
    
    return 0;
}

/*******************************************************/

int LED_PWR(char power)
{
    unsigned long int led_state = LED_RESET_STATE;
    unsigned char LED_PWM[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    
    switch(power)
    {
        case PWR_OFF:
            LED_DISABLE();
            break;
            
        case PWR_ON:
            LED_PWM[_1R] = DEFAULT_LED_PWM;
            led_state = led_state | LED_1R_ON;        
            LED_ENABLE();
            break;
            
        default:
            break;
    }

    
    
    LED_i2c_write(led_state, LED_PWM);
    
    return 0;
}

int LED_VOL(char volume)
{
    unsigned long int led_state = LED_RESET_STATE;
    unsigned char LED_PWM[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

    switch(volume)
    {
        case 0:
            break;
        case 1:
            LED_PWM[_1B] = DEFAULT_LED_PWM / 3;
            led_state = led_state | LED_1B_ON;
            break;
        case 2:
            LED_PWM[_1B] = DEFAULT_LED_PWM / 2;        
            led_state = led_state | LED_1B_ON;            
            break;    
        case 3:
            LED_PWM[_1B] = DEFAULT_LED_PWM;        
            led_state = led_state | LED_1B_ON;        
            break;
        case 4:
            LED_PWM[_1B] = DEFAULT_LED_PWM;
            LED_PWM[_2B] = DEFAULT_LED_PWM / 3;            
            led_state = led_state | LED_1B_ON | LED_2B_ON;        
            break;
        case 5:
            LED_PWM[_1B] = DEFAULT_LED_PWM;
            LED_PWM[_2B] = DEFAULT_LED_PWM / 2;        
            led_state = led_state | LED_1B_ON | LED_2B_ON;        
            break;
        case 6:
            LED_PWM[_1B] = DEFAULT_LED_PWM;
            LED_PWM[_2B] = DEFAULT_LED_PWM;        
            led_state = led_state | LED_1B_ON | LED_2B_ON;        
            break;
        case 7:
            LED_PWM[_1B] = DEFAULT_LED_PWM;
            LED_PWM[_2B] = DEFAULT_LED_PWM;    
            LED_PWM[_3B] = DEFAULT_LED_PWM / 3;                
            led_state = led_state | LED_1B_ON | LED_2B_ON | LED_3B_ON;        
            break;   
        case 8:
            LED_PWM[_1B] = DEFAULT_LED_PWM;
            LED_PWM[_2B] = DEFAULT_LED_PWM;    
            LED_PWM[_3B] = DEFAULT_LED_PWM / 2;        
            led_state = led_state | LED_1B_ON | LED_2B_ON | LED_3B_ON;        
            break;
        case 9:
            LED_PWM[_1B] = DEFAULT_LED_PWM;
            LED_PWM[_2B] = DEFAULT_LED_PWM;    
            LED_PWM[_3B] = DEFAULT_LED_PWM;        
            led_state = led_state | LED_1B_ON | LED_2B_ON | LED_3B_ON;        
            break;
        case 10:
            LED_PWM[_1B] = DEFAULT_LED_PWM;
            LED_PWM[_2B] = DEFAULT_LED_PWM;    
            LED_PWM[_3B] = DEFAULT_LED_PWM;    
            LED_PWM[_4B] = DEFAULT_LED_PWM / 3;                
            led_state = led_state | LED_1B_ON | LED_2B_ON | LED_3B_ON | LED_4B_ON;        
            break;
        case 11:
            LED_PWM[_1B] = DEFAULT_LED_PWM;
            LED_PWM[_2B] = DEFAULT_LED_PWM;    
            LED_PWM[_3B] = DEFAULT_LED_PWM;    
            LED_PWM[_4B] = DEFAULT_LED_PWM / 2;        
            led_state = led_state | LED_1B_ON | LED_2B_ON | LED_3B_ON | LED_4B_ON;        
            break;
        case 12:
            LED_PWM[_1B] = DEFAULT_LED_PWM;
            LED_PWM[_2B] = DEFAULT_LED_PWM;    
            LED_PWM[_3B] = DEFAULT_LED_PWM;    
            LED_PWM[_4B] = DEFAULT_LED_PWM;
            led_state = led_state | LED_1B_ON | LED_2B_ON | LED_3B_ON | LED_4B_ON;        
            break;
        case 13:
            LED_PWM[_1B] = DEFAULT_LED_PWM;
            LED_PWM[_2B] = DEFAULT_LED_PWM;    
            LED_PWM[_3B] = DEFAULT_LED_PWM;    
            LED_PWM[_4B] = DEFAULT_LED_PWM;
            LED_PWM[_5B] = DEFAULT_LED_PWM / 3;            
            led_state = led_state | LED_1B_ON | LED_2B_ON | LED_3B_ON | LED_4B_ON | LED_5B_ON;        
            break;
        case 14:
            LED_PWM[_1B] = DEFAULT_LED_PWM;
            LED_PWM[_2B] = DEFAULT_LED_PWM;    
            LED_PWM[_3B] = DEFAULT_LED_PWM;    
            LED_PWM[_4B] = DEFAULT_LED_PWM;
            LED_PWM[_5B] = DEFAULT_LED_PWM / 2;      
            led_state = led_state | LED_1B_ON | LED_2B_ON | LED_3B_ON | LED_4B_ON | LED_5B_ON;        
            break;
        case 15:
            LED_PWM[_1B] = DEFAULT_LED_PWM;
            LED_PWM[_2B] = DEFAULT_LED_PWM;    
            LED_PWM[_3B] = DEFAULT_LED_PWM;    
            LED_PWM[_4B] = DEFAULT_LED_PWM;
            LED_PWM[_5B] = DEFAULT_LED_PWM;              
            led_state = led_state | LED_1B_ON | LED_2B_ON | LED_3B_ON | LED_4B_ON | LED_5B_ON;        
            break;
        default:
            break;
    }            
    
    
    
    
    LED_i2c_write(led_state, LED_PWM);
    
    
    return 0;
}

int LED_SRC(char source)
{
    unsigned long int led_state = LED_RESET_STATE;
    unsigned char LED_PWM[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    
    switch(source)
    {
        case OPT_SRC:
            LED_PWM[_1G] = DEFAULT_LED_PWM;
            LED_PWM[_2G] = DEFAULT_LED_PWM;
            led_state = led_state | LED_1G_ON | LED_2G_ON;
            break;
        case AUX_SRC:
            LED_PWM[_1G] = DEFAULT_LED_PWM;
            led_state = led_state | LED_1G_ON;
            break;
        default:
            break;
    }
    
    LED_i2c_write(led_state, LED_PWM);
    
    
    return 0;
}

int LED_ERROR()
{
    LED_ERROR_i2c();
    
    return 0;
}

/*****************************************************/



int LED_i2c_write(unsigned long int led_state, char LED_PWM[16])
{
    unsigned char LED_OUT_0 = (unsigned char) led_state;
    unsigned char LED_OUT_1 = (unsigned char) (led_state >> 8);
    unsigned char LED_OUT_2 = (unsigned char) (led_state >> 16);
    unsigned char LED_OUT_3 = (unsigned char) (led_state >> 24);
    
    for(int count = 0; count < 16; count++)
    {
        i2c_write(TLC59116_ADDR, PWM_REG[count], LED_PWM[count]);
    }
    
    i2c_write(TLC59116_ADDR, LED_OUT_0_REG, LED_OUT_0);
    i2c_write(TLC59116_ADDR, LED_OUT_1_REG, LED_OUT_1);
    i2c_write(TLC59116_ADDR, LED_OUT_2_REG, LED_OUT_2);    
    
    return 0;
}



int LED_ERROR_i2c()
{
   
    
    return 0;
}

int LED_ENABLE()
{
    i2c_write(TLC59116_ADDR, MODE1_REG, (MODE1_REG_DEFAULT | LED_OSC_ENABLE));
            
    return 0;
}

int LED_DISABLE()
{
    i2c_write(TLC59116_ADDR, MODE1_REG, (MODE1_REG_DEFAULT & LED_OSC_DISABLE));
    
    return 0;
}

int LED_OUT_OF_RANGE()
{

    return 0;
}
