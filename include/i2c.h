#ifndef I2C_H
#define I2C_H


/******************************************
function declarations
******************************************/
int i2c_write(char addr, char reg, char data);
int i2c_read(char addr, char reg);
int i2c_write16(char addr, char reg, int data);
int i2c_close_file(int fd);



#endif //I2C_H
