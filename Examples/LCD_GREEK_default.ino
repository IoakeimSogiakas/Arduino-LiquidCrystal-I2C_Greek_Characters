//Default set up and how to use 
#include <Arduino.h>
#include <LiquidCrystal_I2C_Greek.h>
LiquidCrystal_I2C_Greek lcd(0x27, 16, 2);


void setup() {
  lcd.init();
  lcd.backlight();
  lcd.createGreekChars(lcd);
}
void loop(){
  lcd.setCursor(0,0);
  // lcd.print("PRINT ENGLISH");
  // lcd.setCursor(0,1);
  // lcd.print_greek("ΕΛΛΗΝΙΚΑ");
  // lcd.setCursor(0,2);
  lcd.print_greek(lcd, "ΑΒΓΔΕΖΗΘΙΚΛΜΝΞΟΠΡΣΤΥΦΧΨΩ");
}









