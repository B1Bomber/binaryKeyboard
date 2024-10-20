import serial
import time
import pyautogui

#serial.Serial(<port>, <baud rate>)
serialcomm = serial.Serial('COM7', 9600)
serialcomm.timeout = 1

while True:
    i = input("input (on/ff): ").strip()
    if i == 'done':
        print (finished program)
        break 
    serialcomm.write(i.encode())
    time.sleep(0.5)
    print(serialcomm.readline().decode('ascii'))

serialcomm.close

pyautogui.write('Hello world!', interval=0.25)  # type with quarter-second pause in between each key
