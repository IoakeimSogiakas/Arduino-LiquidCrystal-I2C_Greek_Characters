//Default set up and how to use 
#include <Arduino.h>
#include <Greek_LCD.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);


void setup() {
  lcd.init();
  lcd.backlight():
  createGreekChars(lcd);
  
}
void loop(){
  lcd.setCursor(0,0);
  lcd.print("PRINT ENGLISH");
  lcd.setCursor(0,1);
  print_greek(lcd,"ΕΚΤΥΠΩΣΗ ΕΛΛΗΝΙΚΑ");

}






