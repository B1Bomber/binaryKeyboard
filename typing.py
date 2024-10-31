import serial
import time
#import pyautogui

#arduino = serial.Serial(port = 'COM7', baudrate = 9600, timeout = 1) 
serialcomm = serial.Serial('/dev/cu.usbserial-1120', 9600)
# put your usb port as the first argument
serialcomm.timeout = 1

def binary_to_ascii(binary_value):
    if len(binary_value) != 8:
        raise Error("Input must be a 8-bit binary string")
    
    decimal_value = int(binary_value,2)

    ascii_value = chr(decimal_value)
    # do I need a library for this?

    return ascii_value

def main():
    fromSerial = serialcomm.readline().decode('ascii')
    serialcomm.close
    # maybe reading the serial should be outside?
    # try testing this

    if fromSerial == "star":
        # for switching to osu keyboard down the line
        return
    
    if fromSerial == "backspace":
        #for doing a backspace maybe? Only if ascii doesn't have a backspace key
        return

    asciiKey = binary_to_ascii(int(fromSerial))
    pyautogui.write('Hello world!', interval=0.25)  # type with quarter-second pause in between each key
    #type the asciikey

    main()
    # repeatedly run this because someone will be typing something. 


#Don't worry about these for now
#serialcomm.write(i.encode())
#time.sleep(0.5)