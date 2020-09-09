import smbus
import time
bus = smbus.SMBus(1)

addr = 0x0d
rgb_off_reg = 0x07
rgb_effect_reg = 0x04
rgb_speed_reg = 0x05
rgb_color_reg = 0x06
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

def setRGBEffect(effect):
    if effect >= 0 and effect <= 4:
        bus.write_byte_data(addr, rgb_effect_reg, effect&0xff)
def setRGBSpeed(speed):
    if speed >= 1 and speed <= 3:
        bus.write_byte_data(addr, rgb_speed_reg, speed&0xff)
def setRGBColor(color):
    if color >= 0 and color <= 6:
        bus.write_byte_data(addr, rgb_color_reg, color&0xff)

bus.write_byte_data(addr, rgb_off_reg, 0x00)
time.sleep(1)
setRGBEffect(1)
setRGBSpeed(3)
setRGBColor(4)
