#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include "U8x8lib.h"

#define OLED_WIDTH 128
#define OLED_HEIGHT 64

#define OLED_ADDR   0x3C

Adafruit_SSD1306 display(OLED_WIDTH, OLED_HEIGHT);

int zero = 12;
int one = 11;
int enter = 10;

int col = 1;

char binary[8] = {};

int index = 0;

void setup(){
    display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
    display.clearDisplay();

    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.println("Welcome to PIB Binary Keyboard");
    display.display(); 
    //may need to this function
  
    pinMode(zero, INPUT_PULLUP);
    pinMode(one, INPUT_PULLUP);
    pinMode(enter, INPUT_PULLUP);
    Serial.begin(9600);
}

void loop(){
    int index = col - 1;

    
}
