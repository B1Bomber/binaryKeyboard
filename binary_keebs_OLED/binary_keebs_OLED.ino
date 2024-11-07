#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#define OLED_WIDTH 128
#define OLED_HEIGHT 64

#define OLED_ADDR   0x3C

Adafruit_SSD1306 display(OLED_WIDTH, OLED_HEIGHT);

int zero = 12;
int one = 11;
int enter = 10;

int col = 1;

char binary[8] = {};
char (*previousBinary)[8] = &binary;
//char previousBinary[8] = {};
int index = 0;

void setup() {
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
  
  //debug
  Serial.begin(9600);
}

void loop(){
  int index = col - 1;
  
  //debug
  //Serial.println(digitalRead(zero));
  //Serial.println(col);
  
  //debug binary conversion
  //Serial.println(binary[0]);
  //Serial.println(binary[1]);
  //Serial.println(binary[2]);
  //Serial.println(binary[3]);
  //Serial.println(binary[4]);
  //Serial.println(binary[5]);
  //Serial.println(binary[6]);
  //Serial.println(binary[7]);
  
  if (col == 9){
    if ((digitalRead(zero) == 0) || (digitalRead(one) == 0)){
      enterFunction();
    }
    else if (digitalRead(enter) == 0){
      enterFunction();
    }
    //else other stuff?
  }
  else{
    binaryKeb();
  }
  
}

void enterFunction(){
  //copy binary to previousBinary
  char (*previousBinary)[8] = &binary;
  
  //conversion
  atoi(binary);
  // have python do this instead

  Serial.display(binary);

  //debug
  Serial.println(binary);

  int binary[8] = {};
  //lcd.clear();
  col = 1;
  display.setCursor(index, 0);
  display.print("[________]");
  display.setCursor(col, 0);
}

void binaryKeb(){
  if (digitalRead(zero) == 0){
   display.setCursor(col, 0);
   display.print("0");
   col = col + 1;
   int index = col - 1;
   binary[index] = "0";
  }
  else if (digitalRead(one) == 0){
    display.setCursor(col, 0);
    display.print("1");
    col = col + 1;
    int index = col - 1;
    binary[index] = "1";
  }
  else if (digitalRead(enter) == 0){
    enterFunction();
  }
  else if ((digitalRead(zero) == 0) && (digitalRead(enter) == 0)){
    display.print("_");
    binary[index - 1] = 0;
  }
  else if ((digitalRead(one) == 0) && (digitalRead(enter) == 0)){
    display.clearDisplay();
    col = 1;
    display.print("[________]");
  }
  //else{
    // all 3 are pressed
  //return to previousBinary
  //}
  delay(100);
}
