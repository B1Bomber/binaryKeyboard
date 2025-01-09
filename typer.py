import serial
#import time
import pyautogui

pyautogui.FAILSAFE = True
# ensures that moving mouse to the upper-left will exit program

#serialcomm = serial.Serial('/dev/cu.usbserial-1120', 9600)
# put your usb port as the first argument
# put your baud rate as the second argument

serialcomm = serial.Serial('/dev/cu.usbserial-10', 9600)

serialcomm.timeout = 1

def main():
    fromSerial = serialcomm.readline().decode('ascii')
    serialcomm.close

    if len(fromSerial) < 8:
        raise Error("Input must be a 8-bit binary string")

    if fromSerial == "starOn":
        # for switching to osu keyboard down the line
        return
    
    if fromSerial == "starOff":
        # for switching back to binary keyboard down the line
        return
    
    
    
    decimal_value = int(fromSerial, 2) 
    asciiKey = chr(decimal_value)

    pyautogui.write(asciiKey, interval=0.25)
    # type the asciiKey with quarter-second pause in between each key

    main()
    # repeatedly run this because someone will be typing something. 
