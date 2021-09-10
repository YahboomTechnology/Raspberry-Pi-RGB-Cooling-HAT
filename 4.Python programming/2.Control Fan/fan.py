
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
        bus.write_byte_data(addr, fan_reg, 0x01)
        time.sleep(2)

    state = (state + 1) % 2
    