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

const int zeroPin = 12;
const int onePin = 11;
const int enterPin = 10;

bool OSUKeyboard = false;
int displayCursorColumn = 12;
// increases by 12

char binary[8] = {};
int binaryIndex = 0;

void setup(){
    Serial.begin(115200);

    pinMode(zero, INPUT_PULLUP);
    pinMode(one, INPUT_PULLUP);
    pinMode(enter, INPUT_PULLUP);

    display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
    display.display();
    delay(2000);
    display.clearDisplay();

    startText();
}

void loop(){
    if (binaryIndex > 7){
        pressEnter();
        continue;
    }

    if (zeroPin == LOW){
        pressZero();
    }
    else if (onePin == LOW){
        pressOne();
    }
    else if (enterPin == LOW){
        pressEnter();
    }
    else if (zeroPin == LOW && enterPin == LOW){
        OSUKeyboard = true;
        changeKeyboard(OSUKeyboard);
    }
    else if (onePin == LOW && enterPin == LOW){
        pressBack();
    }
    else if (zeroPin == LOW && onePin == LOW && enterPin == LOW){
        pressClear();
    }
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
    displayPress("0");
    binary[binaryIndex] = "0";

    binaryIndex += 1;
    displayCursorColumn += 12;
}

void pressOne(){
    displayPress("1");
    binary[binaryIndex] = "1";

    binaryIndex += 1;
    displayCursorColumn += 12;
}

void pressEnter(){

}

void pressBack(){
    displayPress(" ");
    binary[binaryIndex] = NULL;
}

void pressClear(){
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.println("<________>");

    displayCursorColumn = 12;

    binary[8] = {};
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
        if (zeroPin == LOW){
            // press z key
        }
        else if (onePin == LOW){
            // press x key
        }
        else if (zeroPin == LOW && enterPin == LOW){
            // put the previous entered bits in
            keyboardOSU = false;
        }
    }
}

void displayPress(char input){
    display.setCursor(displayCursorColumn, 0);
    display.println(" ");
    display.println(input);
    display.display();
}