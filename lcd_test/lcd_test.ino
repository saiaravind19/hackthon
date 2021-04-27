
#include <LiquidCrystal_I2C.h>
#include<Wire.h>
// set the LCD number of columns and rows


// set LCD address, number of columns and rows
// if you don't know your display address, run an I2C scanner sketch
LiquidCrystal_I2C lcd(0x27,20,4);  

void setup(){
  Wire.begin();
lcd.init();
  // initialize LCD
  // turn on LCD backlight                      
  lcd.backlight();
}

void loop(){
  // set cursor to first column, first row
  lcd.setCursor(0, 0);
  // print message
  lcd.print("Kittu");
  delay(1000);
  // clears the display to print new message
  lcd.clear();
  // set cursor to first column, second row
  lcd.setCursor(0,1);
  lcd.print("Ruthvik");
  delay(1000);
  lcd.clear(); 
}
