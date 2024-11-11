# LiquidCrystal_I2C_Greek Library

This library extends the standard `LiquidCrystal_I2C` library to support Greek letters on LCD displays. It maintains all functionality of the original `LiquidCrystal_I2C` library but adds the ability to display Greek text with minimal adjustments.

## Key Features
- Compatible with the standard LiquidCrystal-I2C functions.
- Adds `lcd.print_greek` function for displaying Greek text.
- Supports custom Greek characters, including full alphabet display.

## Installation
Download and include `LiquidCrystal_I2C_Greek.h` in your project. 

## Usage
To display Greek letters, use `lcd.print_greek` instead of `lcd.print`. Additionally, initialize Greek characters by calling `lcd.createGreekChars(lcd);` in the `setup()` function.

**Note:** LCDs are limited to 8 custom characters, but Greek requires 10. The library manages this limit, but the Theta (Θ) character will always appear slightly squished due to space constraints.

## Example
Below is a basic example of setting up and using the library:

```cpp
#include <Arduino.h>
#include <LiquidCrystal_I2C_Greek.h>

LiquidCrystal_I2C_Greek lcd(0x27, 16, 2);

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.createGreekChars(lcd);  // Initialize Greek characters
}

void loop() {
  lcd.setCursor(0, 0);
  lcd.print("PRINT ENGLISH");
  lcd.setCursor(0, 1);
  lcd.print_greek(lcd, "ΕΛΛΗΝΙΚΑ");  // Print Greek text
  lcd.setCursor(0, 2);
  lcd.print_greek(lcd, "ΑΒΓΔΕΖΗΘΙΚΛΜΝΞΟΠΡΣΤΥΦΧΨΩ");  // Fu![IMG_20241111_143652](https://github.com/user-attachments/assets/a70b4711-06d6-4b8b-b30e-5bafd8297b75)
ll Greek alphabet
}
```

## Known Issues
Due to the 8 custom character limit on many LCDs, the library performs optimizations to support only capital Greek letters.

![IMG_20241111_143652](https://github.com/user-attachments/assets/d79f9b2f-d0b1-4f1d-84f1-2dfce4a571b4)
