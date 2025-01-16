import serial
import time
import pyautogui

pyautogui.FAILSAFE = True
# ensures that moving mouse to the upper-left will exit program

osuMode = False
# switches the keyboard to osu mode

serialcomm = serial.Serial('/dev/cu.usbserial-110', 9600, timeout=1, rtscts=True)
# put your usb port as the first argument
# put your baud rate as the second argument
# put the time out as the third argument

def normalKeyboard(inputFromSerial):
    if len(inputFromSerial) == 8:
        decimal_value = int(inputFromSerial, 2)
        asciiKey = chr(decimal_value)

        print(asciiKey)

        time.sleep(0.5)
        pyautogui.typewrite(asciiKey, interval=0.25)
        # type the asciiKey with quarter-second pause in between each key
    return

def osuKeyboard():
    osuKey = serialcomm.readline().decode('ascii').strip()

    if osuKey == "starOff":
        return False
    
    pyautogui.typewrite(osuKey, interval=0.25)
    return True

def main():
    fromSerial = serialcomm.readline().decode('ascii').strip()
    #serialcomm.close

    if fromSerial == "starOn":
        # for switching to osu keyboard
        while osuKeyboard == True:
            return

    
    normalKeyboard(fromSerial)
    
    main()
    # repeatedly run this because someone will be typing something. 

main()
# activate main in the first place
