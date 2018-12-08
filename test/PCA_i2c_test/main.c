#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>


int main()
{
    int fd = wiringPiI2CSetup(0x38);

    int result = wiringPiI2CWriteReg8(fd, 0x03, 0xff);


    printf("fd:%d\tresult:%d\n", fd, result);


    


    return 0;
}
