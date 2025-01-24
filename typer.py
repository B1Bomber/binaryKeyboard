import serial
import time
import pyautogui
import platform

pyautogui.FAILSAFE = True
# ensures that moving mouse to the upper-left will exit program
# remove in the final version

def detectPort():
    # Faster implementation may be to use serial.tools.list_ports.comports() 
    # This generates a list of valid ports and then check the valid ports against serial
    if platform.system() == 'Windows':
        # Windows has 256 possible COM ports (1 to 256)
        # Loop through all 256 to find where the keyboard is connected to
        # Should be the first few, so run time should be low?

        return
    elif platform.system() == 'Darwin':
        # for MacOS, 10000 possible ports
        # That number is quite big, runtime will be long

        return
    else:
        print("You are either on Linux or an esoteric system. Please input the port manually or implement port detection for your specific system.")
        #serialcomm = serial.Serial('/dev/cu.usbserial-1120', 9600, timeout=1, rtscts=True)
        # put your usb port as the first argument
        # put your baud rate as the second argument
        return

serialcomm = serial.Serial('/dev/cu.usbserial-110', 9600, timeout=1, rtscts=True)

def normalKeyboard(inputFromSerial):
    if len(inputFromSerial) == 8:
        decimal_value = int(inputFromSerial, 2)
        asciiKey = chr(decimal_value)

        print(asciiKey)

        time.sleep(0.5)
        pyautogui.typewrite(asciiKey, interval=0.25)
        # type the asciiKey with quarter-second pause in between each key
    return

def main():
    fromSerial = serialcomm.readline().decode('ascii').strip()
    #serialcomm.close

    if fromSerial == "starOn":
        # for switching to osu keyboard down the line
        return
    
    if fromSerial == "starOff":
        # for switching back to binary keyboard down the line
        return
    
    normalKeyboard(fromSerial)
    
    main()
    # repeatedly run this because someone will be typing something. 

main()
# activate main in the first place
