import serial
import time
#import pyautogui

#arduino = serial.Serial(port = 'COM7', baudrate = 9600, timeout = 1) 
serialcomm = serial.Serial('/dev/cu.usbserial-1120', 9600)
serialcomm.timeout = 1

def binary_to_ascii(binary_value):
    if len(binary_value) != 8:
        raise Error("Input must be a 8-bit binary string")
    
    decimal_value = int(binary_value,2)

    ascii_value = chr(decimal_value)

    return ascii_value


#serialcomm.write(i.encode())
#time.sleep(0.5)
fromSerial = serialcomm.readline().decode('ascii')

serialcomm.close

#pyautogui.write('Hello world!', interval=0.25)  # type with quarter-second pause in between each key
