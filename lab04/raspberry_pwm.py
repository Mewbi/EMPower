#!/usr/bin/python3
import os, sys
import serial
import time

ser = serial.Serial('/dev/ttyACM0',115200, timeout = 5)

def set_led_status(gpio, value):
    path = base_path + "gpio" + str(gpio) + "/value"
    f = open(path, "w")
    f.write(str(value))
    f.close
    return

# listen for the input, exit if nothing received in timeout period

while True:
	line = ser.readline()
	if len(line) == 0:
		print("Time out! Exit.\n")
		sys.exit()
	print(line.decode('ascii'), end='')

