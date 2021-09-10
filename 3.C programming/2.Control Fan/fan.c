#include <stdio.h>
// Import wiringPi/I2C library
#include <wiringPi.h>
#include <wiringPiI2C.h>

int main(void)
{
	int state = 0;
	//Define I2C related parameters
	int fd_i2c;
	wiringPiSetup();
	fd_i2c = wiringPiI2CSetup(0x0d);
	if (fd_i2c < 0)
	{
		fprintf(stderr, "fail to init I2C\n");
		return -1;
	}

// Loop to let the state increase by 1, each time you add 1 to send a command to adjust the speed of 
	while (1)
	{
		if (state == 0)
		{
			wiringPiI2CWriteReg8(fd_i2c, 0x08, 0x00);
			delay(2000);
		}
		else
		{
			wiringPiI2CWriteReg8(fd_i2c, 0x08, 0x01);
			delay(2000);
		}
		
		state = (state + 1) % 2;

	}
	return 0;
}
