#ifndef TAS_FUNCTIONS_H
#define TAS_FUNCTIONS_H

/****************************************
FUNCION DECLARATIONS
****************************************/
int TAS_PWR(char power);
int TAS_VOL(char volume);
int TAS_SRC(char source);
int TAS_i2c_write(char ADDR, char REG, int DATA);
int TAS_init();


#define TAS_ADDR 0x56

/****************************************/
#define TAS_VOL_REG 0x07
#define TAS_CH1_VOL_REG 0x08
#define TAS_CH2_VOL_REG 0x09
#define MUTE 0
#define TAS_CH1_2_MUTE 0x03FF
#define TAS_CH1_2_UNMUTE 0x00C0
#define DEFAULT_VOLUME 0x0124

extern const int volume_table[16];

#define NUM_OPT_WRITES 26
#define NUM_AUX_WRITES 18

#define ADDR_INDEX 0
#define REG_INDEX  1
#define DATA_INDEX 2
    
    
extern const int OPT_DATA[27][3];

extern const int ANA_DATA[18][3];

#endif //TAS_FUNCTIONS_H

