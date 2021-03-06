#include "TAS_functions.h"
#include "rpi_xmos_tas_integration.h"
#include "i2c.h"
#include "debug.h"

const int ANA_DATA[18][3] = {
    {0x18, 0x7F, 0x50},
    {0x18, 0x00, 0x01},
    {0x18, 0x36, 0x02},
    {0x18, 0x7F, 0x50},
    {0x18, 0x00, 0x00},
    {0x18, 0x01, 0x07},
    {0x18, 0x7F, 0x50},
    {0x18, 0x00, 0x01},
    {0x18, 0x36, 0x02},
    {0x18, 0x7F, 0x50},
    {0x18, 0x00, 0x01},
    {0x18, 0x3A, 0x02},
    {0x18, 0x7F, 0x50},
    {0x18, 0x00, 0x00},
    {0x18, 0x01, 0x07},
    {0x18, 0x7F, 0x50},
    {0x18, 0x00, 0x01},
    {0x18, 0x3A, 0x02}    
};

const int OPT_DATA[27][3] = {
    {0x40, 0x6B, 0x00},
    {0x40, 0x34, 0x02},
    {0x18, 0x7F, 0X50},
    {0x18, 0x00, 0x01},
    {0x18, 0x36, 0x01},
    {0x18, 0x7F, 0x50},
    {0x18, 0x00, 0x00},
    {0x18, 0x01, 0x07},
    {0x18, 0x00, 0x00},
    {0x18, 0x00, 0x01},
    {0x18, 0x00, 0x00},
    {0x18, 0x00, 0x01},
    {0x18, 0x00, 0x00},
    {0x18, 0x00, 0x01},
    {0x18, 0x00, 0x00},
    {0x18, 0x7F, 0x50},
    {0x18, 0x00, 0x01},
    {0x18, 0x36, 0x01},
    {0x18, 0x7F, 0x50},
    {0x18, 0x00, 0x01},
    {0x18, 0x3A, 0x01},
    {0x18, 0x7F, 0x50},
    {0x18, 0x00, 0x00},
    {0x18, 0x01, 0x07},
    {0x18, 0x7F, 0x50},
    {0x18, 0x00, 0x01},   
    {0x18, 0x3A, 0x01}    
};

/*****************************************
const int volume_table[16] = {
    0x03FF,  //MUTE
    0x0200,  //-40dB
    0x01D8,  //-35
    0x01B0,  //-30
    0x019C,  //-27.5
    0x0188,  //-25
    0x0174,  //-22.5
    0x0160,  //-20
    0x014C,  //-17.5
    0x0138,  //-15
    0x0124,  //-12.5
    0x0110,  //-10
    0x00FC,  //-7.5         
    0x00E8,  //-5
    0x00D4,  //-2
    0x00C0};  //0
****************************************/

const int volume_table[16] = {
    0xFF03,  //MUTE
    0x0002,  //-40dB
    0xD801,  //-35
    0xB001,  //-30
    0x9C01,  //-27.5
    0x8801,  //-25
    0x7401,  //-22.5
    0x6001,  //-20
    0x4C01,  //-17.5
    0x3801,  //-15
    0x2401,  //-12.5
    0x1001,  //-10
    0xFC00,  //-7.5         
    0xE800,  //-5
    0xD400,  //-2
    0xC000};  //0



int TAS_init()
{
    if(DEBUG_OPT) debug_out(DEBUG_OPT, "TAS_init", "initializing");
    return 0;
}

/*********************************************************/

int TAS_PWR(char power)
{
    if(DEBUG_OPT)
    {
	sprintf(debug_msg, "tas power to:%d", power);
	debug_out(DEBUG_OPT, "TAS_PWR", debug_msg);
    }
    
    switch(power)
    {
        case PWR_ON:
            TAS_i2c_write(TAS_ADDR, TAS_CH1_VOL_REG, TAS_CH1_2_UNMUTE);
            TAS_i2c_write(TAS_ADDR, TAS_CH2_VOL_REG, TAS_CH1_2_UNMUTE);            
            break;
            
        case PWR_OFF:
            TAS_i2c_write(TAS_ADDR, TAS_CH1_VOL_REG, TAS_CH1_2_MUTE);
            TAS_i2c_write(TAS_ADDR, TAS_CH2_VOL_REG, TAS_CH1_2_MUTE);            
            break;
            
        default:
            break;
    }
    return 0;
}

int TAS_VOL(char volume)
{
    if(DEBUG_OPT)
    {
	sprintf(debug_msg, "tas volume to:%d", volume);
	debug_out(DEBUG_OPT, "TAS_VOL", debug_msg);
    }

    
    TAS_i2c_write(TAS_ADDR, TAS_VOL_REG, volume_table[volume]);
  
    return 0;
}

int TAS_SRC(char source)
{
    if(DEBUG_OPT)
    {
	sprintf(debug_msg, "tas src to:%d", source);
	debug_out(DEBUG_OPT, "TAS_SRC", debug_msg);
    }


    switch(source)
    {
        case OPT_SRC:
            for(int count = 0; count < NUM_OPT_WRITES; count++)
            {
                i2c_write(OPT_DATA[count][ADDR_INDEX], 
                              OPT_DATA[count][REG_INDEX], 
                              OPT_DATA[count][DATA_INDEX]);
            }
            break;
            
        case AUX_SRC:
            for(int count = 0; count < NUM_AUX_WRITES; count++)
            {
                i2c_write(ANA_DATA[count][ADDR_INDEX], 
                              ANA_DATA[count][REG_INDEX], 
                              ANA_DATA[count][DATA_INDEX]);
            }
            break;
            
        default:
            break;
    }

    
    return 0;
}

/**************************************************/

int TAS_i2c_write(char ADDR, char REG, int DATA)
{
    i2c_write16(ADDR, REG, DATA);
    
    return 0;
}
