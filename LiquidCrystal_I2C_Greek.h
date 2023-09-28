//YWROBOT
#ifndef LiquidCrystal_I2C_Greek_h
#define LiquidCrystal_I2C_Greek_h

#include <inttypes.h>
#include "Print.h" 
#include <Wire.h>


 
#define G_GAMMA 0
#define G_DELTA 1
#define G_THITA 2
#define G_LAMBDA 3
#define G_XI 4
#define G_PI 5
#define G_SIGMA 246
#define G_PHI 6
#define G_PSI 7
#define G_OMEGA 244


// commands
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

// flags for function set
#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00

// flags for backlight control
#define LCD_BACKLIGHT 0x08
#define LCD_NOBACKLIGHT 0x00

#define En B00000100  // Enable bit
#define Rw B00000010  // Read/Write bit
#define Rs B00000001  // Register select bit




class LiquidCrystal_I2C_Greek : public Print {
public:
  LiquidCrystal_I2C_Greek(uint8_t lcd_Addr,uint8_t lcd_cols,uint8_t lcd_rows);
  void begin(uint8_t cols, uint8_t rows, uint8_t charsize = LCD_5x8DOTS );
  void clear();
  void home();
  void noDisplay();
  void display();
  void noBlink();
  void blink();
  void noCursor();
  void cursor();
  void scrollDisplayLeft();
  void scrollDisplayRight();
  void printLeft();
  void printRight();
  void leftToRight();
  void rightToLeft();
  void shiftIncrement();
  void shiftDecrement();
  void noBacklight();
  void backlight();
  void autoscroll();
  void noAutoscroll(); 
  void createChar(uint8_t, uint8_t[]);
  void createChar(uint8_t location, const char *charmap);
  void createGreekChars(LiquidCrystal_I2C_Greek lcd);
  void print_greek(LiquidCrystal_I2C_Greek lcd, const String& text);
  void print_greek(LiquidCrystal_I2C_Greek lcd, unsigned char text[]);
  // Example: 	const char bell[8] PROGMEM= {B00100,B01110,B01110,B01110,B11111,B00000,B00100,B00000,};
  
 byte Greek_Gamma[8]  = {B11111, B10000, B10000, B10000, B10000, B10000, B10000, B00000}; // Γ
 byte Greek_Delta[8]  = {B00100, B01010, B01010, B10001, B10001, B10001, B11111, B00000};  // Δ
 byte Greek_Thita[8]  = {B01110, B10001, B10001, B11111, B10001, B10001, B01110, B00000}; // Θ
 byte Greek_Lambda[8] = {B00100, B01010, B01010, B10001, B10001, B10001, B10001, B00000}; // Λ
 //
 byte Greek_Xi[8]     = {B11111, B00000, B00000, B01110, B00000, B00000, B11111, B00000}; // Ξ
 byte Greek_Pi[8]     = {B11111, B10001, B10001, B10001, B10001, B10001, B10001, B00000};  // Π
 byte Greek_Sigma[8]  = {B11111, B01000, B00100, B00010, B00100, B01000, B11111, B00000};// Σ
 byte Greek_Phi[8]    = {B00100, B01110, B10101, B10101, B10101, B01110, B00100, B00000};// Φ
 byte Greek_Psi[8]    = {B10001, B10101, B10101, B10101, B01110, B00100, B00100, B00000}; // Ψ
 byte Greek_Omega[8]  = {B01110, B10001, B10001, B10001, B10001, B01010, B11011, B00000}; // Ω
  
  void setCursor(uint8_t, uint8_t); 
#if defined(ARDUINO) && ARDUINO >= 100
  virtual size_t write(uint8_t);
#else
  virtual void write(uint8_t);
#endif
  void command(uint8_t);
  void init();
  void oled_init();

////compatibility API function aliases
void blink_on();						// alias for blink()
void blink_off();       					// alias for noBlink()
void cursor_on();      	 					// alias for cursor()
void cursor_off();      					// alias for noCursor()
void setBacklight(uint8_t new_val);				// alias for backlight() and nobacklight()
void load_custom_character(uint8_t char_num, uint8_t *rows);	// alias for createChar()
void printstr(const char[]);

////Unsupported API functions (not implemented in this library)
uint8_t status();
void setContrast(uint8_t new_val);
uint8_t keypad();
void setDelay(int,int);
void on();
void off();
uint8_t init_bargraph(uint8_t graphtype);
void draw_horizontal_graph(uint8_t row, uint8_t column, uint8_t len,  uint8_t pixel_col_end);
void draw_vertical_graph(uint8_t row, uint8_t column, uint8_t len,  uint8_t pixel_col_end);
	 

private:
  void init_priv();
  void send(uint8_t, uint8_t);
  void write4bits(uint8_t);
  void expanderWrite(uint8_t);
  void pulseEnable(uint8_t);
  uint8_t _Addr;
  uint8_t _displayfunction;
  uint8_t _displaycontrol;
  uint8_t _displaymode;
  uint8_t _numlines;
  bool _oled = false;
  uint8_t _cols;
  uint8_t _rows;
  uint8_t _backlightval;
};

#endif