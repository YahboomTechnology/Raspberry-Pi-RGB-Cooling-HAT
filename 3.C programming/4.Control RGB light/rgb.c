#include <stdio.h>
//Import wiringPi/I2C library
#include <wiringPi.h>
#include <wiringPiI2C.h>

#define Max_LED 3

int fd_i2c;
void setRGB(int num, int R, int G, int B);
void closeRGB();


int main(void)
{
    //Define I2C related parameters
    wiringPiSetup();
    fd_i2c = wiringPiI2CSetup(0x0d);
    if (fd_i2c < 0)
    {
        fprintf(stderr, "fail to init I2C\n");
        return -1;
    }

    closeRGB();
    delay(1);
    setRGB(Max_LED, 0, 255, 0);

    return 0;
}

/*
if it is greater than or equal to 3, then all the lights are set at the same time. 
The R, G, and B values range from 0 to 255.
*/
// num=(0~3),R=(0~255),G=(0~255),B=(0~255)
void setRGB(int num, int R, int G, int B)
{
    if (num >= Max_LED)
    {
        wiringPiI2CWriteReg8(fd_i2c, 0x00, 0xff);
        wiringPiI2CWriteReg8(fd_i2c, 0x01, R);
        wiringPiI2CWriteReg8(fd_i2c, 0x02, G);
        wiringPiI2CWriteReg8(fd_i2c, 0x03, B);
    }
    else if (num >= 0)
    {
        wiringPiI2CWriteReg8(fd_i2c, 0x00, num);
        wiringPiI2CWriteReg8(fd_i2c, 0x01, R);
        wiringPiI2CWriteReg8(fd_i2c, 0x02, G);
        wiringPiI2CWriteReg8(fd_i2c, 0x03, B);
    }
}

//Close RGB
void closeRGB()
{
    wiringPiI2CWriteReg8(fd_i2c, 0x07, 0x00);
}
