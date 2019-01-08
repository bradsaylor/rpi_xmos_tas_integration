#include "rpi_xmos_tas_integration.h"
#include "wiringPiI2C.h"
#include "debug.h"
#include "i2c.h"
#include <unistd.h>

/*****************************************************************
LOCAL FUNCTIONS
*****************************************************************/
int i2c_write(char addr, char reg, char data)
{
    int fd = wiringPiI2CSetup(addr);
    
    int result = wiringPiI2CWriteReg8(fd, reg, data);    

    if(I2C_DEBUG && DEBUG_OPT)
    {
	    sprintf(debug_msg, "id:%x addr:%x data:%x ->%d", addr, reg, data, result);
	    debug_out(DEBUG_OPT, "i2c_write", debug_msg);
    }

    i2c_close_file(fd);
    
    return result;
}

int i2c_read(char addr, char reg)
{
    int fd = wiringPiI2CSetup(addr);

    int result = wiringPiI2CReadReg8(fd, reg);    
    
    if(I2C_DEBUG && DEBUG_OPT)
    {
	    sprintf(debug_msg, "id:%x addr:%x result:%x", addr, reg, (char)result);
	    debug_out(DEBUG_OPT, "i2c_read", debug_msg);
    }

    i2c_close_file(fd);

    return result;    
}

int i2c_write16(char addr, char reg, int data)
{
    int fd = wiringPiI2CSetup(addr);
    
    int result = wiringPiI2CWriteReg16(fd, reg, data);

    if(I2C_DEBUG && DEBUG_OPT)
    {
	    sprintf(debug_msg, "id:%x addr:%x data:%x ->%d", addr, reg, data, result);
	    debug_out(DEBUG_OPT, "i2c_write", debug_msg);
    }
    
    i2c_close_file(fd); 
    
    return result;
}


int i2c_close_file(int fd)
{
    close(fd);

}    

