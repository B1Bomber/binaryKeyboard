#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Wire.h>
#include <SPI.h>
// #include "U8x8lib.h"

const int OLED_WIDTH = 128;
const int OLED_HEIGHT = 16;
const int reset = -1;

#define OLED_ADDR   0x3C

Adafruit_SSD1306 display(OLED_WIDTH, OLED_HEIGHT, &Wire, reset);

const int zeroButton = 12;
const int oneButton = 11;
const int enterButton = 10;

bool OSUKeyboard = false;
int displayCursorColumn = 12;
// increases by 12

char binary[9] = {};
binary[8] = '\0';

int binaryIndex = 0;

void setup(){
    Serial.begin(9600);

    pinMode(zeroButton, INPUT_PULLUP);
    pinMode(oneButton, INPUT_PULLUP);
    pinMode(enterButton, INPUT_PULLUP);

    display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
    display.display();
    delay(2000);
    display.clearDisplay();

    startText();
}

void loop(){
    while (binaryIndex < 8){
        if (digitalRead(zeroButton) == LOW){
            pressZero();
        }
        else if (digitalRead(oneButton) == LOW){
            pressOne();
        }
        else if (digitalRead(enterButton) == LOW){
            pressEnter();
        }
        else if (digitalRead(zeroButton) == LOW && digitalRead(enterButton) == LOW){
            OSUKeyboard = true;
            Serial.println("starOn");
            changeKeyboard(OSUKeyboard);
        }
        else if (digitalRead(oneButton) == LOW && digitalRead(enterButton) == LOW){
            pressBack();
        }
        else if (digitalRead(zeroButton) == LOW && digitalRead(oneButton) == LOW && digitalRead(enterButton) == LOW){
            pressClear();
        }
    }

    pressEnter();
}

void startText(){
    const char startTextLines[4][10] = {"Welcome to", "PIB Binary", "Keyboard! ", "<________>"};
    const int length = sizeof(startTextLines) / sizeof(startTextLines[0]);

    for (int i = 0; i < length; i++){
        display.clearDisplay();
        display.setTextSize(2);
        display.setTextColor(WHITE);
        display.setCursor(0, 0);
        display.println(startTextLines[i]);
        delay(2000);
        display.display();
    }
}

void pressZero(){
    displayPress('0');
    
    binary[binaryIndex] = '0';

    binaryIndex += 1;
    displayCursorColumn += 12;

    Serial.println("Pressed 0");
}

void pressOne(){
    displayPress('1');
    binary[binaryIndex] = '1';

    binaryIndex += 1;
    displayCursorColumn += 12;

    Serial.println("Pressed 1");
}

void pressEnter(){
    Serial.print(binary);

    pressClear();
}

void pressBack(){
    display.fillRect(displayCursorColumn, 0, 12, 16, BLACK);
    display.display();
    binary[binaryIndex] = NULL;
}

void pressClear(){
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.println("<________>");

    displayCursorColumn = 12;

    binary[9] = {};
    binary[8] = '\0';

    binaryIndex = 0;
}

void changeKeyboard(bool & keyboardOSU){
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.println("OSU! MODE");
    display.display();

    while (keyboardOSU == true){
        if (digitalRead(zeroButton) == LOW){
            // press z key
            Serial.println("Z");
        }
        else if (digitalRead(oneButton) == LOW){
            // press x key
            Serial.println("X")
        }
        else if (digitalRead(zeroButton) == LOW && digitalRead(enterButton) == LOW){
            // put the previous entered bits in
            keyboardOSU = false;
            Serial.println("starOff");
        }
    }
}

void displayPress(char input){
    display.setCursor(displayCursorColumn, 0);
    display.fillRect(displayCursorColumn, 0, 12, 16, BLACK);
    display.print(input);
    display.display();
}
