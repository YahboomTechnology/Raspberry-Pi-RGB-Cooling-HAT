import smbus
import time
import os
bus = smbus.SMBus(1)

addr = 0x0d
fan_reg = 0x08
state = 0
temp = 0
level_temp = 0
rgb_off_reg = 0x07
Max_LED = 3

def setRGB(num, r, g, b):
    if num >= Max_LED:
        bus.write_byte_data(addr, 0x00, 0xff)
        bus.write_byte_data(addr, 0x01, r&0xff)
        bus.write_byte_data(addr, 0x02, g&0xff)
        bus.write_byte_data(addr, 0x03, b&0xff)
    elif num >= 0:
        bus.write_byte_data(addr, 0x00, num&0xff)
        bus.write_byte_data(addr, 0x01, r&0xff)
        bus.write_byte_data(addr, 0x02, g&0xff)
        bus.write_byte_data(addr, 0x03, b&0xff)

bus.write_byte_data(addr,rgb_off_reg,0x00)
time.sleep(1)
while True:
    cmd = os.popen('vcgencmd measure_temp').readline()
    CPU_TEMP = cmd.replace("temp=","").replace("'C\n","")
    print(CPU_TEMP)
    temp = float(CPU_TEMP)

    if abs(temp - level_temp) >= 1:
        if temp <= 45:
            level_temp = 45
            setRGB(Max_LED, 0x00, 0x00, 0xff)
        elif temp <= 47:
            level_temp = 47
            setRGB(Max_LED, 0x1e, 0x90, 0xff)
        elif temp <= 49:
            level_temp = 49
            setRGB(Max_LED, 0x00, 0xbf, 0xff)
        elif temp <= 51:
            level_temp = 51
            setRGB(Max_LED, 0x5f, 0x9e, 0xa0)
        elif temp <= 53:
            level_temp = 53
            setRGB(Max_LED, 0xff, 0xff, 0x00)
        elif temp <= 55:
            level_temp = 55
            setRGB(Max_LED, 0xff, 0xd7, 0x00)
        elif temp <= 57:
            level_temp = 57
            setRGB(Max_LED, 0xff, 0xa5, 0x00)
        elif temp <= 59:
            level_temp = 59
            setRGB(Max_LED, 0xff, 0x8c, 0x00)
        elif temp <= 61:
            level_temp = 61
            setRGB(Max_LED, 0xff, 0x45, 0x00)
        elif temp >= 63:
            level_temp = 63
            setRGB(Max_LED, 0xff, 0x00, 0x00)

    time.sleep(.5)
    
