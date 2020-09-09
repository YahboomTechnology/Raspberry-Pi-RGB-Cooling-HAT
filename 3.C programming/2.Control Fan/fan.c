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
		switch (state)
		{
			case 0:
				wiringPiI2CWriteReg8(fd_i2c, 0x08, 0x00);
			break;
			case 1:
				wiringPiI2CWriteReg8(fd_i2c, 0x08, 0x02);
			break;
			case 2:
				wiringPiI2CWriteReg8(fd_i2c, 0x08, 0x03);
			break;
			case 3:
				wiringPiI2CWriteReg8(fd_i2c, 0x08, 0x04);
			break;
			case 4:
				wiringPiI2CWriteReg8(fd_i2c, 0x08, 0x05);
			break;
			case 5:
				wiringPiI2CWriteReg8(fd_i2c, 0x08, 0x06);
			break;
			case 6:
				wiringPiI2CWriteReg8(fd_i2c, 0x08, 0x07);
			break;
			case 7:
				wiringPiI2CWriteReg8(fd_i2c, 0x08, 0x08);
			break;
			case 8:
				wiringPiI2CWriteReg8(fd_i2c, 0x08, 0x09);
			break;
			case 9:
				wiringPiI2CWriteReg8(fd_i2c, 0x08, 0x01);
			break;
			default:
			break;
		}
		if (state == 0)
		{
			delay(1000);
		}

		state++;

		if (state > 9)
		{
			delay(1000);
			state = 0;
		}

		delay(1000);
	}
	return 0;
}
