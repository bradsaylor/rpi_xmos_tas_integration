#include "UI_functions.h"
#include "LED_functions.h"
#include "TAS_functions.h"
#include "i2c.h"
#include "debug.h"
#include <string.h>


/*****************************************************************
UI INIT FUNCTIONS
*****************************************************************/
int Buttons_init()
{
    i2c_write(PCA9554A_ADDR, BUTTON_CONFIG_REG, BUTTON_CONFIG_REG_DEFAULT);
    
    return 0;
}

/*****************************************************************
BUTTON PRESS UI FUNCTIONS
*****************************************************************/
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

/*****************************************************************
READING BUTTON STATE
*****************************************************************/
int readPCA9554(){

    int result = i2c_read(PCA9554A_ADDR, BUTTON_READ_REG);
    
    return result;
}



