//#include <Keyboard.h>
#include <LiquidCrystal.h>

int zero = 12;
int one = 11;
int enter = 10;

int col = 1;

int displayCursorColumn = 12;
// increases by 12

char binary[8] = {};
char (*previousBinary)[8] = &binary;
//char previousBinary[8] = {};
int index = 0;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

void setup() {
  lcd.begin(16, 2);
  lcd.clear();
  lcd.print("[________]");
  
  pinMode(zero, INPUT_PULLUP);
  pinMode(one, INPUT_PULLUP);
  pinMode(enter, INPUT_PULLUP);
  
  //debug
  Serial.begin(800);
}

void loop(){
  // set the cursor to column 0, line 1
  // lcd.setCursor(0, 1);
  // lcd.print("g");
  
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

  //debug
  Serial.println(binary);

  int binary[8] = {};
  //lcd.clear();
  col = 1;
  lcd.setCursor(index, 0);
  lcd.print("[________]");
  lcd.setCursor(col, 0);
}

void binaryKeb(){
  if (digitalRead(zero) == 0){
   lcd.setCursor(col, 0);
   lcd.print("0");
   col = col + 1;
   int index = col - 1;
   binary[index] = "0";
  }
  else if (digitalRead(one) == 0){
    lcd.setCursor(col, 0);
    lcd.print("1");
    col = col + 1;
    int index = col - 1;
    binary[index] = "1";
  }
  else if (digitalRead(enter) == 0){
    enterFunction();
  }
  else if ((digitalRead(zero) == 0) && (digitalRead(enter) == 0)){
    lcd.print(" ");
    binary[index - 1] = 0;
  }
  else if ((digitalRead(one) == 0) && (digitalRead(enter) == 0)){
    lcd.clear();
    col = 1;
    lcd.print("[________]");
  }
  //else{
    // all 3 are pressed
  //return to previousBinary
  //}
  delay(100);
}
