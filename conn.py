#!/usr/bin/env python3
import serial

if __name__ == '__main__':
    ser = serial.Serial('/dev/ttyUSB0', 9600, timeout=1)

ser.reset_input_buffer()

while True:
    x=input("Input: ")
    ser.write(str(x).encode('utf-8'))
