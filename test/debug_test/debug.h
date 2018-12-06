#ifndef DEBUG_H
#define DEBUG_H

#include <stdio.h>

/******************************************
FUNCTION DECLARATIONS
 ******************************************/
int debug_file_init();
int debug_file_close();
int debug_out(char DEBUG_OPT, char *id, char *msg);
int debug_to_screen(char *id, char *msg);
int debug_to_file(char *id, char *msg);
/******************************************/

/******************************************
MACRO DEFINITIONS
 ******************************************/
#define DEBUG_FILE_NAME "_debug_out.txt"
#define PATH_TO_LOG "log/"
#define DEBUG_FORMAT "%s:\t\t%s\n"

/******************************************
EXTERN DEFINITIONS
 ******************************************/
extern FILE *fp;



#endif //DEBUG_H
