import serial
import serial.tools.list_ports
import time
import pyautogui
import platform

pyautogui.FAILSAFE = True
# ensures that moving mouse to the upper-left will exit program
# remove in the final version

def detectPort():
    if platform.system() == 'Windows':
        # Windows has 256 possible COM ports (1 to 256)
        # Loop through all 256 to find where the keyboard is connected to
        # Should be the first few, so run time should be low?

        portsList = list(serial.tools.list_ports.comports())

        for port in portsList:
            try:
                serialcomm = serial.Serial(port.device, 9600, timeout=None, rtscts=True)
                #print(port.device)
                return serialcomm
            except (OSError, serial.SerialException):
                pass

        #raise Exception("Sorry, no port found.") 
    elif platform.system() == 'Darwin':
        # for MacOS, 10000 possible ports
        # That number is quite big, runtime will be long

        portsList = serial.tools.list_ports.comports()

        for port in portsList:
            if (port.device == "/dev/cu.wlan-debug") or (port.device == "/dev/cu.Bluetooth-Incoming-Port"):
                continue
            try:
                serialcomm = serial.Serial(port.device, 9600, timeout=None, rtscts=True)
                print(port.device)
                return serialcomm
            except (OSError, serial.SerialException):
                pass

        #raise Exception("Sorry, no port found.") 
    else:
        print("You are either on Linux or an esoteric system. Please input the port manually or implement port detection for your specific system.")
        serialPort = '/dev/cu.usbserial-1120'
        # put your port here

        serialcomm = serial.Serial(serialPort, 9600, timeout=None, rtscts=True)
        # put your usb port as the first argument
        # put your baud rate as the second argument
        return

def normalKeyboard(inputFromSerial):
    if len(inputFromSerial) == 8:
        decimal_value = int(inputFromSerial, 2)
        asciiKey = chr(decimal_value)

        print(asciiKey)

        time.sleep(0.25)
        pyautogui.typewrite(asciiKey, interval=0.25)
        # type the asciiKey with quarter-second pause in between each key
    return


def main():
    openPort = detectPort()
    fromSerial = openPort.readline().decode('ascii').strip()

    if fromSerial == "starOn":
        # for switching to osu keyboard down the line
        return
    
    if fromSerial == "starOff":
        # for switching back to binary keyboard down the line
        return
    
    normalKeyboard(fromSerial)

    openPort.close
    # Just in case there are memory leaks

    main()
    # repeatedly run this because someone will be typing something. 

main()
# activate main in the first place
