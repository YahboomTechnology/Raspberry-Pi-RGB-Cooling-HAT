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

int main(void)
{
    //Define CPU temperature related parameters
    int fd_temp;
    double temp = 0, level_temp = 0;
    char buf[MAX_SIZE];

    //Define I2C related parameters
    int fd_i2c;
    wiringPiSetup();
    fd_i2c = wiringPiI2CSetup(0x0d);
    if (fd_i2c < 0)
    {
        fprintf(stderr, "fail to init I2C\n");
        return -1;
    }

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
                wiringPiI2CWriteReg8(fd_i2c, 0x08, 0x00);
            }
            else if (temp <= 47)
            {
                level_temp = 47;
                wiringPiI2CWriteReg8(fd_i2c, 0x08, 0x04);
            }
            else if (temp <= 49)
            {
                level_temp = 49;
                wiringPiI2CWriteReg8(fd_i2c, 0x08, 0x06);
            }
            else if (temp <= 51)
            {
                level_temp = 51;
                wiringPiI2CWriteReg8(fd_i2c, 0x08, 0x08);
            }
            else if (temp <= 53)
            {
                level_temp = 53;
                wiringPiI2CWriteReg8(fd_i2c, 0x08, 0x09);
            }
            else
            {
                level_temp = 55;
                wiringPiI2CWriteReg8(fd_i2c, 0x08, 0x01);
            }
        }

        delay(500);
    }

    return 0;
}
