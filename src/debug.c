#include <stdio.h>
#include <time.h>
#include <string.h>

#include "debug.h"
#include "rpi_xmos_tas_integration.h"

char debug_msg[50]= "";
char DEBUG_OPT = 0;

char* get_time_stamp()
{
    time_t result = time(NULL);
    return (ctime(&result));
}

int debug_file_init()
{
    char filename[50];
    char *time_stamp = get_time_stamp();

    int count = 0;
    while(*(time_stamp + count) != '\0')
    {
	if(*(time_stamp + count) == ' ')
	{
	    *(time_stamp + count) = '_';
	}
	if(*(time_stamp + count) == '\n')
	{
	    *(time_stamp + count) = '\0';
	}
	count++;
    }

    strcpy(filename, PATH_TO_LOG);
    strcat(filename, time_stamp);
    strcat(filename, DEBUG_FILE_NAME);
    fp_log = fopen(filename, "w");

    return 0;
}

int debug_file_close()
{
    fclose(fp_log);

    return 0;
}

int debug_out(char DEBUG_OPT, char *id, char *msg)
{
    switch(DEBUG_OPT)
    {
    case 1:
	debug_to_screen(id, msg);
	break;
    case 2:
	debug_to_file(id, msg);
	break;
    case 3:
	debug_to_screen(id, msg);
	debug_to_file(id, msg);
	break;
    }

    return 0;
}

int debug_to_screen(char *id, char *msg)
{
    printf(DEBUG_FORMAT, id, msg);

    return 0;
}

int debug_to_file(char *id, char *msg)
{
    fprintf(fp, DEBUG_FORMAT, id, msg);

    return 0;
}

