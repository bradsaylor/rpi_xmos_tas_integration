#include "rpi_xmos_tas_integration.h"

#include <string.h>

/*****************************************************************
LOCAL VARIABLES
*****************************************************************/
char SCRIPT_OPT = 0;

/*****************************************************************
LOCAL FUNCTIONS
*****************************************************************/ 
char script_translate(char *str)
{
    if(!strcmp(str, "VOL+")) return VOL_UP;
    if(!strcmp(str, "VOL-")) return VOL_DOWN;
    if(!strcmp(str, "SRC"))  return SRC;
    if(!strcmp(str, "PWR"))  return PWR;

    return -1;
    
}
