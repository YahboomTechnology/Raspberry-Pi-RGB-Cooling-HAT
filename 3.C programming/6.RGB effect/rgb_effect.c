#include <stdio.h>
// 导入wiringPi/I2C库
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
    // 定义I2C相关参数
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

// 设置RGB灯,num如果大于等于Max_LED（3），则全部灯一起设置
// num=(0~3),R=(0~255),G=(0~255),B=(0~255)
void setRGB(int num, int R, int G, int B)
{
    if (num >= Max_LED)
    {
        wiringPiI2CWriteReg8(fd_i2c, 0x00, 0xff);
        delay(0.03);
        wiringPiI2CWriteReg8(fd_i2c, 0x01, R);
        delay(0.03);
        wiringPiI2CWriteReg8(fd_i2c, 0x02, G);
        delay(0.03);
        wiringPiI2CWriteReg8(fd_i2c, 0x03, B);
        delay(0.03);
    
    }
    else if (num >= 0)
    {
        wiringPiI2CWriteReg8(fd_i2c, 0x00, num);
        delay(0.03);
        wiringPiI2CWriteReg8(fd_i2c, 0x01, R);
        delay(0.03);
        wiringPiI2CWriteReg8(fd_i2c, 0x02, G);
        delay(0.03);
        wiringPiI2CWriteReg8(fd_i2c, 0x03, B);
        delay(0.03);
    }
}

// 关闭RGB
void closeRGB()
{
    wiringPiI2CWriteReg8(fd_i2c, 0x07, 0x00);
    delay(0.03);
}

// 设置RGB灯效，0流水灯，1呼吸灯,2跑马灯，3彩虹灯，4炫彩灯
void setRGBEffect(int effect)
{
    if (effect >= 0 && effect <= 4)
    {
        wiringPiI2CWriteReg8(fd_i2c, RGB_Effect, effect);
        delay(0.03);
    }  
}
// 设置RGB速度：1低速，2中速（默认），3高速
void setRGBSpeed(int speed)
{
    if (speed >= 1 && speed <= 3)
    {
        wiringPiI2CWriteReg8(fd_i2c, RGB_Speed, speed);
        delay(0.03);
    }
}
// 设置流水灯/呼吸灯颜色：0红色，1绿色（默认），2蓝色，3黄色，4紫色，5青色，6白色
void setRGBColor(int color)
{
    if (color >= 0 && color <= 6)
    {
        wiringPiI2CWriteReg8(fd_i2c, RGB_Color, color);
        delay(0.03);
    }
}