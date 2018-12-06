#include <string.h>

char SCRIPT_OPT = 0;

char script_translate(char *str)
{
    if(!strcmp(str, "VOL+")) return 0x04;
    if(!strcmp(str, "VOL-")) return 0x08;
    if(!strcmp(str, "SRC"))  return 0x02;
    if(!strcmp(str, "PWR"))  return 0x01;

    return -1;
    
}
