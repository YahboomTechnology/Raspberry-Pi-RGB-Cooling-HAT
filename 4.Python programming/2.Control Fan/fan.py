import smbus
import time
bus = smbus.SMBus(1)

addr = 0x0d
fan_reg = 0x08
state = 0

while True:
    if state == 0:
        bus.write_byte_data(addr, fan_reg, 0x00)
        time.sleep(2)
    elif state == 1:
        bus.write_byte_data(addr, fan_reg, 0x02)
    elif state == 2:
        bus.write_byte_data(addr, fan_reg, 0x03)
    elif state == 3:
        bus.write_byte_data(addr, fan_reg, 0x04)
    elif state == 4:
        bus.write_byte_data(addr, fan_reg, 0x05)
    elif state == 5:
        bus.write_byte_data(addr, fan_reg, 0x06)
    elif state == 6:
        bus.write_byte_data(addr, fan_reg, 0x07)
    elif state == 7:
        bus.write_byte_data(addr, fan_reg, 0x08)
    elif state == 8:
        bus.write_byte_data(addr, fan_reg, 0x09)
    elif state == 9:
        bus.write_byte_data(addr, fan_reg, 0x01)

    state += 1

    if state > 9:
        time.sleep(1)
        state = 0
    time.sleep(1)
    
