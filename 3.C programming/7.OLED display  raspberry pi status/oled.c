//Import wiringPi/I2C library
#include <wiringPi.h>
#include <wiringPiI2C.h>

//Import oled library
#include "ssd1306_i2c.h"

//Import file control library
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sysinfo.h>
//Import read IP library
#include <ifaddrs.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
//Import read disk library
#include <sys/vfs.h>
#include <unistd.h>

#define TEMP_PATH "/sys/class/thermal/thermal_zone0/temp"
#define MAX_SIZE 32

int main(void)
{
	int fd_temp;
	double temp = 0;
	char buf[MAX_SIZE];

	// get system usage / info
	struct sysinfo sys_info;
	struct statfs disk_info;

	struct ifaddrs *ifAddrStruct = NULL;
	void *tmpAddrPtr = NULL;
	getifaddrs(&ifAddrStruct);

	ssd1306_begin(SSD1306_SWITCHCAPVCC, SSD1306_I2C_ADDRESS);
	// ssd1306_display();      //show logo
	// ssd1306_clearDisplay();
	// delay(500);
	printf("init ok!\n");

	while (1)
	{
		//Read the system information
		if (sysinfo(&sys_info) != 0) // sysinfo(&sys_info) != 0
		{
			printf("sysinfo-Error\n");
			ssd1306_clearDisplay();
			char *text = "sysinfo-Error";
			ssd1306_drawString(text);
			ssd1306_display();
			delay(500);
			continue;
		}
		else
		{
			//clear display
			ssd1306_clearDisplay();

			//CPU usage
			char CPUInfo[MAX_SIZE];
			unsigned long avgCpuLoad = sys_info.loads[0] / 1000;
			sprintf(CPUInfo, "CPU:%ld%%", avgCpuLoad);

			//Running memory usage, remaining/total memory
			char RamInfo[MAX_SIZE];
			unsigned long totalRam = sys_info.totalram >> 20;
			unsigned long freeRam = sys_info.freeram >> 20;
			sprintf(RamInfo, "RAM:%ld/%ld MB", freeRam, totalRam);

			//Get IP adress
			char IPInfo[MAX_SIZE];
			while (ifAddrStruct != NULL)
			{
				if (ifAddrStruct->ifa_addr->sa_family == AF_INET)
				{ // check it is IP4 is a valid IP4 Address
					tmpAddrPtr = &((struct sockaddr_in *)ifAddrStruct->ifa_addr)->sin_addr;
					char addressBuffer[INET_ADDRSTRLEN];
					inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);

					if (strcmp(ifAddrStruct->ifa_name, "eth0") == 0)
					{
						sprintf(IPInfo, "eth0:IP:%s", addressBuffer);
						break;
					}
					else if (strcmp(ifAddrStruct->ifa_name, "wlan0") == 0)
					{
						sprintf(IPInfo, "wlan0:%s", addressBuffer);
						break;
					}
				}
				ifAddrStruct = ifAddrStruct->ifa_next;
			}

			//Read CPU temperature and judge
			char CPUTemp[MAX_SIZE];
			fd_temp = open(TEMP_PATH, O_RDONLY);
			if (fd_temp < 0)
			{
				temp = 0;
				printf("failed to open thermal_zone0/temp\n");
			}
			else
			{
				//Read temperature and judge
				if (read(fd_temp, buf, MAX_SIZE) < 0)
				{
					temp = 0;
					printf("fail to read temp\n");
				}
				else
				{
					//Convert to floating point printing
					temp = atoi(buf) / 1000.0;
					// printf("temp: %.1f\n", temp);
					sprintf(CPUTemp, "Temp:%.1fC", temp);
				}
			}
			close(fd_temp);

			//Read disk space, remaining/total space
			char DiskInfo[MAX_SIZE];
			statfs("/", &disk_info);
			unsigned long long totalBlocks = disk_info.f_bsize;
			unsigned long long totalSize = totalBlocks * disk_info.f_blocks;
			size_t mbTotalsize = totalSize >> 20;
			unsigned long long freeDisk = disk_info.f_bfree * totalBlocks;
			size_t mbFreedisk = freeDisk >> 20;
			sprintf(DiskInfo, "Disk:%ld/%ldMB", mbFreedisk, mbTotalsize);

			//What you need to display on the OLED
			ssd1306_drawText(0, 0, CPUInfo);
			ssd1306_drawText(56, 0, CPUTemp);
			ssd1306_drawText(0, 8, RamInfo);
			ssd1306_drawText(0, 16, DiskInfo);
			ssd1306_drawText(0, 24, IPInfo);

			//Refresh display
			ssd1306_display();
		}
		delay(500);
	}

	return 0;
}
