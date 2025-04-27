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
const int ctrlButton = 10;

int displayCursorColumn = 12;
// increases by 12

char binary[9];
int binaryIndex = 0;

const int keyInputDelay = 350;

void setup(){
    Serial.begin(9600);

    pinMode(zeroButton, INPUT_PULLUP);
    pinMode(oneButton, INPUT_PULLUP);
    pinMode(ctrlButton, INPUT_PULLUP);

    display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
    display.display();
    delay(2000);
    display.clearDisplay();

    startText();
}

void loop(){
    while (binaryIndex < 8){
        if (digitalRead(zeroButton) == LOW && digitalRead(oneButton) == HIGH && digitalRead(ctrlButton) == HIGH){
            pressZero();
            delay(keyInputDelay);
        }
        else if (digitalRead(oneButton) == LOW && digitalRead(zeroButton) == HIGH && digitalRead(ctrlButton) == HIGH){
            pressOne();
            delay(keyInputDelay);
        }
        else if (digitalRead(ctrlButton) == LOW){
            if (digitalRead(zeroButton) == LOW){
                pressBack();
                delay(keyInputDelay);
            }
            else if (digitalRead(oneButton) == LOW){
                pressEnter();
                delay(keyInputDelay);
            }
        }
    }

    // After the 8 bits are filled. 
    if (digitalRead(zeroButton) == LOW && digitalRead(oneButton) == HIGH && digitalRead(ctrlButton) == HIGH){
        pressEnter();
        delay(keyInputDelay);
    }
    else if (digitalRead(oneButton) == LOW && digitalRead(zeroButton) == HIGH && digitalRead(ctrlButton) == HIGH){
        pressEnter();
        delay(keyInputDelay);
    }
    else if (digitalRead(ctrlButton) == LOW && digitalRead(zeroButton) == HIGH && digitalRead(oneButton) == HIGH){
        pressEnter();
        delay(keyInputDelay);
    }
    else if (digitalRead(zeroButton) == LOW && digitalRead(ctrlButton) == LOW && digitalRead(oneButton) == HIGH){
        
    }
    else if (digitalRead(oneButton) == LOW && digitalRead(ctrlButton) == LOW && digitalRead(zeroButton) == HIGH){
        pressBack();
        delay(keyInputDelay);
    }
    else if (digitalRead(zeroButton) == LOW && digitalRead(oneButton) == LOW && digitalRead(ctrlButton) == LOW){
        pressClear();
        delay(keyInputDelay);
    }
}

void startText() {
    scrollText();
}

void scrollText() {
    const char startText[] = "Welcome to PIB Binary Keyboard! Hello, py.";
    const int scrollSpeedDelay = 4;
    const int yPos = 0;
    const int delayBeforeEnding = 500;

    display.setTextSize(2);  
    display.setTextColor(WHITE);

    int textWidthPixels = strlen(startText) * 12; 

    for (int x = display.width(); x >= -textWidthPixels; x--) {

        display.clearDisplay();     // Clear the buffer before drawing the next frame

        display.setCursor(x, yPos); // Set the starting position for the text
                                    // 'x' decreases each time, moving text left

        display.print(startText);   // Draw the entire text string

        display.display();          // Update the physical screen with this frame

        delay(scrollSpeedDelay);    // This delay controls the scrolling speed.

    }

    delay(delayBeforeEnding);
    display.clearDisplay(); // Clear the display once scrolling is done
    display.display();
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
