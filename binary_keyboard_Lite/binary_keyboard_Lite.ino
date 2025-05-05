#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Wire.h>
#include <SPI.h>
#include <string.h>
#include <math.h>
// #include "U8x8lib.h"

const int OLED_WIDTH = 128;
const int OLED_HEIGHT = 16;
const int reset = -1;

#define OLED_ADDR   0x3C

Adafruit_SSD1306 display(OLED_WIDTH, OLED_HEIGHT, &Wire, reset);

const int zeroButton = 12;
const int oneButton = 11;
const int enterButton = 10;

int displayCursorColumn = 12;
// increases by 12

char binary[9];
int binaryIndex = 0;

const int keyInputDelay = 250;

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
        if (digitalRead(zeroButton) == LOW && digitalRead(oneButton) == HIGH && digitalRead(enterButton) == HIGH){
            pressZero();
            delay(keyInputDelay);
        }
        else if (digitalRead(oneButton) == LOW && digitalRead(zeroButton) == HIGH && digitalRead(enterButton) == HIGH){
            pressOne();
            delay(keyInputDelay);
        }
        else if (digitalRead(enterButton) == LOW && digitalRead(zeroButton) == HIGH && digitalRead(oneButton) == HIGH){
            pressEnter();
            delay(keyInputDelay);
        }
        else if (digitalRead(zeroButton) == LOW && digitalRead(enterButton) == LOW && digitalRead(oneButton) == HIGH){
        
        }
        else if (digitalRead(oneButton) == LOW && digitalRead(enterButton) == LOW && digitalRead(oneButton) == HIGH){
            pressBack();
            delay(keyInputDelay);
        }
        else if (digitalRead(oneButton) == LOW && digitalRead(enterButton) == LOW && digitalRead(zeroButton) == LOW){
            pressClear();
            delay(keyInputDelay);
        }
    }

    // After the 8 bits are filled. 
    if (digitalRead(zeroButton) == LOW && digitalRead(oneButton) == HIGH && digitalRead(enterButton) == HIGH){
        pressEnter();
        delay(keyInputDelay);
    }
    else if (digitalRead(oneButton) == LOW && digitalRead(zeroButton) == HIGH && digitalRead(enterButton) == HIGH){
        pressEnter();
        delay(keyInputDelay);
    }
    else if (digitalRead(enterButton) == LOW && digitalRead(zeroButton) == HIGH && digitalRead(oneButton) == HIGH){
        pressEnter();
        delay(keyInputDelay);
    }
    else if (digitalRead(zeroButton) == LOW && digitalRead(enterButton) == LOW && digitalRead(oneButton) == HIGH){
        
    }
    else if (digitalRead(oneButton) == LOW && digitalRead(enterButton) == LOW && digitalRead(zeroButton) == HIGH){
        pressBack();
        delay(keyInputDelay);
    }
    else if (digitalRead(zeroButton) == LOW && digitalRead(oneButton) == LOW && digitalRead(enterButton) == LOW){
        pressClear();
        delay(keyInputDelay);
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
    if (binaryIndex == 8){
        Serial.println(binary);
    }

    pressClear();
}

void pressBack(){
    display.fillRect(displayCursorColumn, 0, 12, 16, BLACK);
    display.print('_');
    display.display();
    binary[binaryIndex] = NULL;
}

void pressClear(){
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.println("<________>");
    display.display();

    displayCursorColumn = 12;

    binary[9] = {};
    binary[8] = '\0';

    binaryIndex = 0;
}

void displayPress(char input){
    display.setCursor(displayCursorColumn, 0);
    display.fillRect(displayCursorColumn, 0, 12, 16, BLACK);
    display.print(input);
    display.display();
}
