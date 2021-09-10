import smbus
import time
import os
bus = smbus.SMBus(1)

addr = 0x0d
fan_reg = 0x08
state = 0
temp = 0
level_temp = 0

while True:
    cmd = os.popen('vcgencmd measure_temp').readline()
    CPU_TEMP = cmd.replace("temp=","").replace("'C\n","")
    print(CPU_TEMP)
    temp = float(CPU_TEMP)

    if temp <= 45:
        bus.write_byte_data(addr, fan_reg, 0x00)
    elif temp >= 50:
        bus.write_byte_data(addr, fan_reg, 0x01)

    time.sleep(1)
    
