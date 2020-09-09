#include <stdio.h>
#include <stdlib.h>

//Import file control function library
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

//Import wiringPi/I2C library
#include <wiringPi.h>
#include <wiringPiI2C.h>

#define TEMP_PATH "/sys/class/thermal/thermal_zone0/temp"
#define MAX_SIZE 20
#define Max_LED  3

void setRGB(int num, int R, int G, int B);
void closeRGB();

int fd_i2c = -1;

int main(void)
{
    //Define CPU temperature related parameters
    int fd_temp;
    double temp = 0, level_temp = 0;
    char buf[MAX_SIZE];

    //Define I2C related parameters
    wiringPiSetup();
    fd_i2c = wiringPiI2CSetup(0x0d);
    if (fd_i2c < 0)
    {
        fprintf(stderr, "fail to init I2C\n");
        return -1;
    }
    closeRGB();

    while (1)
    {
        fd_temp = open(TEMP_PATH, O_RDONLY);
        //Determine if the file is open normally
        if (fd_temp < 0)
        {
            fprintf(stderr, "fail to open thermal_zone0/temp\n");
            return -1;
        }

        //Read temperature and judge
        if (read(fd_temp, buf, MAX_SIZE) < 0)
        {
            fprintf(stderr, "fail to read temp\n");
            return -1;
        }

        //Conversion format, the output retains 2 decimal places
        temp = atoi(buf) / 1000.0;
        printf("temp: %.1fC\n", temp);
        close(fd_temp); //turn off file

        if (abs(temp - level_temp) >= 1)
        {
            if (temp <= 45)
            {
                level_temp = 45;
                setRGB(Max_LED, 0x00, 0x00, 0xff);
            }
            else if (temp <= 47)
            {
                level_temp = 47;
                setRGB(Max_LED, 0x1e, 0x90, 0xff);
            }
            else if (temp <= 49)
            {
                level_temp = 49;
                setRGB(Max_LED, 0x00, 0xbf, 0xff);
            }
            else if (temp <= 51)
            {
                level_temp = 51;
                setRGB(Max_LED, 0x5f, 0x9e, 0xa0);
            }

            else if (temp <= 53)
            {
                level_temp = 53;
                setRGB(Max_LED, 0xff, 0xff, 0x00);
            }
            else if (temp <= 55)
            {
                level_temp = 55;
                setRGB(Max_LED, 0xff, 0xd7, 0x00);
            }
            else if (temp <= 57)
            {
                level_temp = 57;
                setRGB(Max_LED, 0xff, 0xa5, 0x00);
            }
            else if (temp <= 59)
            {
                level_temp = 59;
                setRGB(Max_LED, 0xff, 0x8c, 0x00);
            }

            else if (temp <= 61)
            {
                level_temp = 61;
                setRGB(Max_LED, 0xff, 0x45, 0x00);
            }
            else if (temp >= 63)
            {
                level_temp = 63;
                setRGB(Max_LED, 0xff, 0x00, 0x00);
            }
        }

        delay(500);
    }

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
    delay(10);
}
