#!/usr/bin/env python

import warnings
import serial
import serial.tools.list_ports
import time
import sys

arduino_ports = [
    p.device
    for p in serial.tools.list_ports.comports()
    if '55730303037351E0E1F0' in p.serial_number
    ]
if not arduino_ports:
    raise IOError("No Arduino found")
if len(arduino_ports) > 1:
    warnings.warn('Multiple Arduinos found - using the first')

serial_port = serial.Serial(arduino_ports[0], 9600)
time.sleep(2)

arg = sys.argv[1].strip()

serial_port.write(arg)
