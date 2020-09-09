import smbus
import time
bus = smbus.SMBus(1)

addr = 0x0d
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
    

bus.write_byte_data(addr, rgb_off_reg, 0x00)
time.sleep(1)
setRGB(Max_LED, 0, 0, 255)
