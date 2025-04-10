# binaryKeyboard

## Arduino Files
`serialTest` contains the Arduino code used to test the serial port. 

`binary_keyboard_LCD` contains the Arduino code from the LCD display implementation. This has been discontinued in favor of the OLED implementations. 

`binary_keyboard_OLED` contains the Arduino code from the 64x128 OLED implementation. 

`binary_keyboard_Lite` contains the Arduino code from the lighter implementation. The OSU mode is removed. Only the core features are retained. 

`binary_keyboard_final` contains the Arduino code from the 16x128 OLED implementation. This is the most updated version. 

`binary_keyboard_workshop` contains the Arduino code version used for the Project in a Box workshop. This is based on the `binary_keyboard_Lite` implementation and has fill in the blank code. 

`binary_keyboard_ctrl` contains a work-in-progress new implementation of the binary keyboard. 

## Python Files
`typingTesting.py` tests the serial port on the Python side. 

`pyautoguiTest.py` tests the pyautogui library for typing and mouse movements. 

`typer.py` is the most updated version of the Python typing script. 

`typer_Lite.py` is the lighter Python typing script. The OSU mode is removed. Only the core features are retained. 

`typer_workshop.py` is the Python typing script version used for the Project in a Box workshop. This is based on the `typer_Lite.py` implementation and has fill in the blank code. 

## Miscellaneous Files
`Libraries` contains all the relevant libraries for this project. 

`binary_keyboard_env` contains the Python environment for this project. 

`LICENSE` GNU General Public License v3.0

`README.md` Congratulations on reading this file!

## Tutorial
Read this [manual](https://docs.google.com/document/d/131jxqDxg6rdgfoZZD68hpaoMgKV9Y7bRPiuu5lFj_eU/edit?usp=sharing) for the full setup and documentation. Currently, it is still a work in progress.
