
/*
NOTES ON passing const 2d array to function:
______________________________________________

In this method, we must typecast the 2D array when passing to function.

#include <stdio.h> 
void print(int *arr, int m, int n) 
{ 
    int i, j; 
    for (i = 0; i < m; i++) 
      for (j = 0; j < n; j++) 
        printf("%d ", *((arr+i*n) + j)); 
} 

int main() 
{ 
    int arr[][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}; 
    int m = 3, n = 3; 
  
    // We can also use "print(&arr[0][0], m, n);" 
    print((int *)arr, m, n); 
    return 0; 
} 
*/

#include "wiringPiI2C.h"
#include "debug.h"

int i2c_write(char addr, char reg, char data)
{
    int fd = wiringPiI2CSetup(addr);
    
    int result = wiringPiI2CWriteReg8(fd, reg, data);    

    if(DEBUG_OPT)
    {
	sprintf(debug_msg, "id:%x addr:%x data:%x ->%d", addr, reg, data, result);
	debug_out(DEBUG_OPT, "i2c_write", debug_msg);
    }
    
    return result;
}

int i2c_read(char addr, char reg)
{
    int fd = wiringPiI2CSetup(addr);

    int result = wiringPiI2CReadReg8(fd, reg);    
    
    if(DEBUG_OPT)
    {
	sprintf(debug_msg, "id:%x addr:%x value:%x", addr, reg, result);
	debug_out(DEBUG_OPT, "i2c_read", debug_msg);
    }


    return result;
    
}

int i2c_write16(char addr, char reg, int data)
{
    int fd = wiringPiI2CSetup(addr);
    
    int result = wiringPiI2CWriteReg16(fd, reg, data);

    if(DEBUG_OPT)
    {
	sprintf(debug_msg, "id:%x addr:%x data:%x ->%d", addr, reg, data, result);
	debug_out(DEBUG_OPT, "i2c_write", debug_msg);
    }
    
     
    return result;
}
