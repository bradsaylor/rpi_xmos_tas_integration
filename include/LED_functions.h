#ifndef LED_FUNCTIONS_H
#define LED_FUNCTIONS_H

/******************************************************
Function Declarations
******************************************************/
int LED_init();
int LED_PWR(char power);
int LED_VOL(char volume);
int LED_SRC(char source);
int LED_ERROR();
int LED_i2c_write(unsigned long int led_state, char LED_PWM[16]);
int LED_ERROR_i2c();
int LED_ENABLE();
int LED_DISABLE();



/**********************************************************************************************/
#define TLC59116_ADDR 0x48

#define LED_OUT_0_REG 0x14
#define LED_OUT_1_REG 0x15
#define LED_OUT_2_REG 0x16
#define LED_OUT_3_REG 0x17

#define LED_OUT_0_REG_DEFAULT 0x00
#define LED_OUT_1_REG_DEFAULT 0x00
#define LED_OUT_2_REG_DEFAULT 0x00
#define LED_OUT_3_REG_DEFAULT 0x00

#define MODE1_REG 0x00
#define MODE2_REG 0x01

#define MODE1_REG_DEFAULT 0x11
#define MODE2_REG_DEFAULT 0x00

#define LED_OSC_ENABLE 0x10
#define LED_OSC_DISABLE 0xEF

extern const char PWM_REG[16]; 
#define PWM_REG_DEFAULT 0x00

/**********************************************************************************************/
#define LED_RESET_STATE 0x00000000

#define LED_1R_ON 0x00000003
#define LED_1G_ON 0x0000000C 
#define LED_1B_ON 0x00000030

#define LED_2R_ON 0x000000C0
#define LED_2G_ON 0x00000300
#define LED_2B_ON 0x00000C00

#define LED_3R_ON 0x00003000
#define LED_3G_ON 0x0000C000
#define LED_3B_ON 0x00030000

#define LED_4R_ON 0x000C0000
#define LED_4G_ON 0x00300000
#define LED_4B_ON 0x00C00000

#define LED_5R_ON 0x03000000
#define LED_5G_ON 0x0C000000
#define LED_5B_ON 0x30000000

#define DEFAULT_LED_PWM 255

#define _1R 0
#define _1G 1
#define _1B 2
#define _2R 3
#define _2G 4
#define _2B 5
#define _3R 6
#define _3G 7
#define _3B 8
#define _4R 9
#define _4G 10
#define _4B 11
#define _5R 12
#define _5G 13
#define _5B 14
/**********************************************************************************************/


#endif //LED_FUNCTIONS_H
