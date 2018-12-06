// program to test debugging screen/file output

#include <stdio.h>
#include "debug.h"
#include <string.h>


int main(int argc, char *argv[])
{
    char DEBUG_OPT = 0;
    
    if(argc > 1)
    {
	if (argc > 2)
	{
	    printf("too many arguments...exiting");
	    return -1;
	}

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
	    return -1;
	}
    }

    debug_out(DEBUG_OPT, "test1", "here is a test firstly");
    debug_out(DEBUG_OPT, "test2", "here is a test secondly");
    debug_out(DEBUG_OPT, "test3", "here is a test thirdly");    
    

    if(DEBUG_OPT > 1)
    {
	debug_file_close();
    }

    return 0;
}
