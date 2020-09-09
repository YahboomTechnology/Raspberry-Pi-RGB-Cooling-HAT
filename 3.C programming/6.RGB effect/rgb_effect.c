#include <stdio.h>
//Import wiringPi/I2C library
#include <wiringPi.h>
#include <wiringPiI2C.h>

#define Max_LED    3
#define RGB_Effect 0x04 
#define RGB_Speed  0x05
#define RGB_Color  0x06

int fd_i2c;
void setRGB(int num, int R, int G, int B);
void closeRGB();

void setRGBEffect(int effect);
void setRGBSpeed(int speed);
void setRGBColor(int color);


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

    setRGBEffect(1);
    setRGBSpeed(3);
    setRGBColor(4);

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

//Set RGB effect，0-water light，1-breathing light,2-marquee，3-rainbow lights，4-colorful lights
void setRGBEffect(int effect)
{
    if (effect >= 0 && effect <= 4)
    {
        wiringPiI2CWriteReg8(fd_i2c, RGB_Effect, effect);
    }  
}
//Set RGB light switching speed of the mode. 1-low speed, 2-medium speed (default), 3-high speed
void setRGBSpeed(int speed)
{
    if (speed >= 1 && speed <= 3)
    {
        wiringPiI2CWriteReg8(fd_i2c, RGB_Speed, speed);
    }
}
//Set the color of the water light and breathing light, 
//0-red, 1-green (default), 2-blue, 3-yellow, 4-purple, 5-cyan, 6-white. 
void setRGBColor(int color)
{
    if (color >= 0 && color <= 6)
    {
        wiringPiI2CWriteReg8(fd_i2c, RGB_Color, color);
    }
}