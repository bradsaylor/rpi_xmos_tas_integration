#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <stdio.h>

#define LED_ADDR 0x60

int main()
{
    wiringPiSetup();

    int fd = wiringPiI2CSetup(LED_ADDR);

    printf("MODE 1:%d\n", wiringPiI2CWriteReg8(fd, 0x00, 0x11));

    printf("MODE 2:%d\n", wiringPiI2CWriteReg8(fd, 0x01, 0x00));

    printf("MODE 1:%d\n", wiringPiI2CWriteReg8(fd, 0x00, 0x01));

    printf("PWM0->255 :%d\n", wiringPiI2CWriteReg8(fd, 0x02, 0xFF));    

    printf("LED0->ON :%d\n", wiringPiI2CWriteReg8(fd, 0x14, 0x13));

    delay(2000);

    printf("PWM0->160 :%d\n", wiringPiI2CWriteReg8(fd, 0x02, 0xA0));   

    delay(2000);

    printf("PWM0->80 :%d\n", wiringPiI2CWriteReg8(fd, 0x02, 0x50));  
 
    return 0;
}
