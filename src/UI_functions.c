#include "UI_functions.h"
#include "LED_functions.h"
#include "TAS_functions.h"
#include "i2c.h"



int Buttons_init()
{
    i2c_write(PCA9554A_ADDR, BUTTON_INPUT_REG, BUTTON_INPUT_REG_DEFAULT);
    
    return 0;
}

/*************************************************************/


int UI_PWR(char power)
{
    TAS_PWR(power);
    LED_PWR(power);

    return 0;
}

int UI_VOL(char volume)
{
    TAS_VOL(volume);
    LED_VOL(volume);

    return 0;
}

int UI_SRC(char source)
{
    TAS_SRC(source);
    LED_SRC(source);
     
    return 0;
}

int UI_ERROR()
{
    LED_ERROR();
    
    return 0;
}

int readPCA9554(){
    int result = i2c_read(PCA9554A_ADDR, BUTTON_INPUT_REG);
    
    return result;
}



