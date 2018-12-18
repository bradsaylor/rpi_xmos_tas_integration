#ifndef UI_FUNCTIONS_H
#define UI_FUNCTIONS_H


/**********************************
FUNCTION DECLARATIONS
 **********************************/
int Buttons_init();
int UI_PWR(char power);
int UI_VOL(char volume);
int UI_SRC(char source);
int UI_ERROR();
int readPCA9554();

/*************************************
MACROS
 *************************************/
#define PCA9554A_ADDR            0x38

#define BUTTON_CONFIG_REG         0x03
#define BUTTON_CONFIG_REG_DEFAULT 0xFF

#define BUTTON_READ_REG 0x00


#endif //UI_FUNCTIONS_H
