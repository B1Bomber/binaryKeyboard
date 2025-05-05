import serial
import serial.tools.list_ports
import time
import pyautogui
import platform

def detectPort():
    if platform.system() == 'Windows':
        portsList = list(serial.tools.list_ports.comports())

        for port in portsList:
            if (port.device[:3] != "COM"):
                continue
            try:
                serialcomm = serial.Serial(port.device, 9600, timeout=None, rtscts=True)
                print(port.device)
                return serialcomm
            except (OSError, serial.SerialException):
                pass

        raise Exception("Sorry, no port found.") 
    elif platform.system() == 'Darwin':
        portsList = serial.tools.list_ports.comports()

        for port in portsList:
            if (port.device[:18] != "/dev/cu.usbserial-"):
                continue
            try:
                serialcomm = serial.Serial(port.device, 9600, timeout=None, rtscts=True)
                print(port.device)
                return serialcomm
            except (OSError, serial.SerialException):
                pass

        raise Exception("Sorry, no port found.") 
    else:
        print("You are either on Linux or an esoteric system. Please input the port manually or implement port detection for your specific system.")
        serialPort = '/dev/ttyUSB0' 
        # put your port here

        serialcomm = serial.Serial(serialPort, 9600, timeout=None, rtscts=True)
        # put your usb port as the first argument
        # put your baud rate as the second argument
        return serialcomm

def normalKeyboard(inputFromSerial):
    if len(inputFromSerial) == 8:
        decimal_value = int(___, 2)
        asciiKey = chr(___)

        pyautogui.typewrite(___, interval=___)
    return

openPort = detectPort()
def main():
    fromSerial = openPort.readline().decode('ascii').strip()
    
    normalKeyboard(fromSerial)

    openPort.close

    main()

main()