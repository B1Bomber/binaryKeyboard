import pyautogui
print("Current mouse position:", pyautogui.position())
pyautogui.moveTo(100, 100, duration=1)
print("New mouse position:", pyautogui.position())

asciiKey = "X"
pyautogui.typewrite(asciiKey, interval=0.25)
print(asciiKey)