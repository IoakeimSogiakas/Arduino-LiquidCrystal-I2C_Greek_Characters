
#include <LiquidCrystal_I2C_Greek.h>
#include <inttypes.h>
#if defined(ARDUINO) && ARDUINO >= 100

#include "Arduino.h"

#define printIIC(args)	Wire.write(args)
inline size_t LiquidCrystal_I2C_Greek::write(uint8_t value) {
	send(value, Rs);
	return 1;
}

#else
#include "WProgram.h"

#define printIIC(args)	Wire.send(args)
inline void LiquidCrystal_I2C_Greek::write(uint8_t value) {
	send(value, Rs);
}

#endif
#include "Wire.h"



// When the display powers up, it is configured as follows:
//
// 1. Display clear
// 2. Function set: 
//    DL = 1; 8-bit interface data 
//    N = 0; 1-line display 
//    F = 0; 5x8 dot character font 
// 3. Display on/off control: 
//    D = 0; Display off 
//    C = 0; Cursor off 
//    B = 0; Blinking off 
// 4. Entry mode set: 
//    I/D = 1; Increment by 1
//    S = 0; No shift 
//
// Note, however, that resetting the Arduino doesn't reset the LCD, so we
// can't assume that its in that state when a sketch starts (and the
// LiquidCrystal constructor is called).

//Greek letters 
#define G_GAMMA 0
byte Greek_Gamma[8] = {0x1F, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x00}; // Γ

#define G_DELTA 1
byte Greek_Delta[8] = {0x04, 0x0A, 0x0A, 0x11, 0x11, 0x11, 0x1F, 0x00}; // Δ

#define G_THITA 2
byte Greek_Thita[8] = {0x0E, 0x11, 0x11, 0x1F, 0x11, 0x11, 0x0E, 0x00}; // Θ

#define G_LAMBDA 3
byte Greek_Lambda[8] = {0x04, 0x0A, 0x0A, 0x1B, 0x11, 0x11, 0x11, 0x00}; // Λ

#define G_XI 4
byte Greek_Xi[8] = {0x1F, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x1F, 0x00}; // Ξ

#define G_PI 5
byte Greek_Pi[8] = {0x1F, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x00}; // Π

#define G_SIGMA 6
byte Greek_Sigma[8] = {0x1F, 0x10, 0x08, 0x04, 0x08, 0x10, 0x1F, 0x00}; // Σ

#define G_PHI 7
byte Greek_Phi[8] = {0x0E, 0x15, 0x15, 0x15, 0x0E, 0x04, 0x04, 0x00}; // Φ

#define G_PSI 8
byte Greek_Psi[8] = {0x15, 0x15, 0x15, 0x0E, 0x04, 0x04, 0x04, 0x00}; // Ψ

#define G_OMEGA 9
byte Greek_Omega[8] = {0x0E, 0x11, 0x11, 0x11, 0x11, 0x0A, 0x1B, 0x00}; // Ω



LiquidCrystal_I2C_Greek::LiquidCrystal_I2C_Greek(uint8_t lcd_Addr,uint8_t lcd_cols,uint8_t lcd_rows)
{
  _Addr = lcd_Addr;
  _cols = lcd_cols;
  _rows = lcd_rows;
  _backlightval = LCD_NOBACKLIGHT;
}

void LiquidCrystal_I2C_Greek::oled_init(){
  _oled = true;
	init_priv();
}

void LiquidCrystal_I2C_Greek::init(){
	init_priv();
}

void LiquidCrystal_I2C_Greek::init_priv()
{
	Wire.begin();
	_displayfunction = LCD_4BITMODE | LCD_1LINE | LCD_5x8DOTS;
	begin(_cols, _rows);  
}

void LiquidCrystal_I2C_Greek::begin(uint8_t cols, uint8_t lines, uint8_t dotsize) {
	if (lines > 1) {
		_displayfunction |= LCD_2LINE;
	}
	_numlines = lines;

	// for some 1 line displays you can select a 10 pixel high font
	if ((dotsize != 0) && (lines == 1)) {
		_displayfunction |= LCD_5x10DOTS;
	}

	// SEE PAGE 45/46 FOR INITIALIZATION SPECIFICATION!
	// according to datasheet, we need at least 40ms after power rises above 2.7V
	// before sending commands. Arduino can turn on way befer 4.5V so we'll wait 50
	delay(50); 
  
	// Now we pull both RS and R/W low to begin commands
	expanderWrite(_backlightval);	// reset expanderand turn backlight off (Bit 8 =1)
	delay(1000);

  	//put the LCD into 4 bit mode
	// this is according to the hitachi HD44780 datasheet
	// figure 24, pg 46
	
	  // we start in 8bit mode, try to set 4 bit mode
   write4bits(0x03 << 4);
   delayMicroseconds(4500); // wait min 4.1ms
   
   // second try
   write4bits(0x03 << 4);
   delayMicroseconds(4500); // wait min 4.1ms
   
   // third go!
   write4bits(0x03 << 4); 
   delayMicroseconds(150);
   
   // finally, set to 4-bit interface
   write4bits(0x02 << 4); 


	// set # lines, font size, etc.
	command(LCD_FUNCTIONSET | _displayfunction);  
	
	// turn the display on with no cursor or blinking default
	_displaycontrol = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;
	display();
	
	// clear it off
	clear();
	
	// Initialize to default text direction (for roman languages)
	_displaymode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
	
	// set the entry mode
	command(LCD_ENTRYMODESET | _displaymode);
	
	home();
  
}

/********** high level commands, for the user! */
void LiquidCrystal_I2C_Greek::clear(){
	command(LCD_CLEARDISPLAY);// clear display, set cursor position to zero
	delayMicroseconds(2000);  // this command takes a long time!
  if (_oled) setCursor(0,0);
}

void LiquidCrystal_I2C_Greek::home(){
	command(LCD_RETURNHOME);  // set cursor position to zero
	delayMicroseconds(2000);  // this command takes a long time!
}

void LiquidCrystal_I2C_Greek::setCursor(uint8_t col, uint8_t row){
	int row_offsets[] = { 0x00, 0x40, 0x14, 0x54 };
	if ( row > _numlines ) {
		row = _numlines-1;    // we count rows starting w/0
	}
	command(LCD_SETDDRAMADDR | (col + row_offsets[row]));
}

// Turn the display on/off (quickly)
void LiquidCrystal_I2C_Greek::noDisplay() {
	_displaycontrol &= ~LCD_DISPLAYON;
	command(LCD_DISPLAYCONTROL | _displaycontrol);
}
void LiquidCrystal_I2C_Greek::display() {
	_displaycontrol |= LCD_DISPLAYON;
	command(LCD_DISPLAYCONTROL | _displaycontrol);
}

// Turns the underline cursor on/off
void LiquidCrystal_I2C_Greek::noCursor() {
	_displaycontrol &= ~LCD_CURSORON;
	command(LCD_DISPLAYCONTROL | _displaycontrol);
}
void LiquidCrystal_I2C_Greek::cursor() {
	_displaycontrol |= LCD_CURSORON;
	command(LCD_DISPLAYCONTROL | _displaycontrol);
}

// Turn on and off the blinking cursor
void LiquidCrystal_I2C_Greek::noBlink() {
	_displaycontrol &= ~LCD_BLINKON;
	command(LCD_DISPLAYCONTROL | _displaycontrol);
}
void LiquidCrystal_I2C_Greek::blink() {
	_displaycontrol |= LCD_BLINKON;
	command(LCD_DISPLAYCONTROL | _displaycontrol);
}

// These commands scroll the display without changing the RAM
void LiquidCrystal_I2C_Greek::scrollDisplayLeft(void) {
	command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVELEFT);
}
void LiquidCrystal_I2C_Greek::scrollDisplayRight(void) {
	command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVERIGHT);
}

// This is for text that flows Left to Right
void LiquidCrystal_I2C_Greek::leftToRight(void) {
	_displaymode |= LCD_ENTRYLEFT;
	command(LCD_ENTRYMODESET | _displaymode);
}

// This is for text that flows Right to Left
void LiquidCrystal_I2C_Greek::rightToLeft(void) {
	_displaymode &= ~LCD_ENTRYLEFT;
	command(LCD_ENTRYMODESET | _displaymode);
}

// This will 'right justify' text from the cursor
void LiquidCrystal_I2C_Greek::autoscroll(void) {
	_displaymode |= LCD_ENTRYSHIFTINCREMENT;
	command(LCD_ENTRYMODESET | _displaymode);
}

// This will 'left justify' text from the cursor
void LiquidCrystal_I2C_Greek::noAutoscroll(void) {
	_displaymode &= ~LCD_ENTRYSHIFTINCREMENT;
	command(LCD_ENTRYMODESET | _displaymode);
}

// Allows us to fill the first 8 CGRAM locations
// with custom characters
void LiquidCrystal_I2C_Greek::createChar(uint8_t location, uint8_t charmap[]) {
	location &= 0x7; // we only have 8 locations 0-7
	command(LCD_SETCGRAMADDR | (location << 3));
	for (int i=0; i<8; i++) {
		write(charmap[i]);
	}
}
//Create greek characters 
void LiquidCrystal_I2C_Greek::createGreekChars(LiquidCrystal_I2C_Greek lcd){
    lcd.clear();
    lcd.createChar(G_GAMMA, Greek_Gamma);
    lcd.createChar(G_DELTA, Greek_Delta);
    lcd.createChar(G_THITA, Greek_Thita);
    lcd.createChar(G_LAMBDA, Greek_Lambda);
    lcd.createChar(G_XI, Greek_Xi);
    lcd.createChar(G_PI, Greek_Pi);
    lcd.createChar(G_SIGMA, Greek_Sigma);
    lcd.createChar(G_PHI, Greek_Phi);
    lcd.createChar(G_PSI, Greek_Psi);
    lcd.createChar(G_OMEGA,Greek_Omega);
}

//Map greek characters
void LiquidCrystal_I2C_Greek::print_greek(LiquidCrystal_I2C_Greek lcd, unsigned char text[]){
    
int i=0;

    while(text[i]!='\0'){
         switch (text[i]){
            case 206: case 127: case 207: break;               
            case 145: case 177: case 172:lcd.write('A');
            break;           
            case 146: case 178:lcd.write('B');
            break;               
            case 147: case 179:lcd.write(G_GAMMA); // Issue probably
            break;
            case 148: case 180:lcd.write(G_DELTA); // Issue probably
            break;             
            case 149: case 181: case 173:lcd.write('E');
            break;                  
            case 150: case 182: lcd.write('Z');
            break;               
            case 151: case 183: case 174:lcd.write('H');
            break; 
            case 152: case 184: lcd.write(G_THITA); // Issue probably
            break;             
            case 153: case 185: case 175: case 144: case 138:lcd.write('I');
            break;             
            case 154: case 186: lcd.write('K');
            break;       
            case 155: case 187:lcd.write(G_LAMBDA);
            break;              
            case 156: case 188: lcd.write('M');
            break;               
            case 157: case 189:lcd.write('N');
            break;               
            case 158: case 190:lcd.write(G_XI);
            break;   
            case 159: case 191: case 140:lcd.write('O');
            break;                     
            case 160: case 128:lcd.write(G_PI);
            break; 
            case 161: case 129:lcd.write('P');
            break;  
            case 163: case 131: case 130: lcd.write(G_SIGMA);
            break; 
            case 164: case 132:lcd.write('T');
            break; 
            case 165: case 133: case 141: case 139: case 176:lcd.write('Y');
            break;                  
            case 166: case 134: lcd.write(G_PHI);
            break; 
            case 167: case 135: lcd.write('X');
            break;  
            case 168: case 136: lcd.write(G_PSI);
            break; 
            case 169: case 137: case 142:lcd.write(G_OMEGA);
            break; 
            default: lcd.write(text[i]);
            //Serial.println(int(text[i]));  c++; break;              
        }
        i++; 
    }
}
//createChar with PROGMEM input
void LiquidCrystal_I2C_Greek::createChar(uint8_t location, const char *charmap) {
	location &= 0x7; // we only have 8 locations 0-7
	command(LCD_SETCGRAMADDR | (location << 3));
	for (int i=0; i<8; i++) {
	    	write(pgm_read_byte_near(charmap++));
	}
}

// Turn the (optional) backlight off/on
void LiquidCrystal_I2C_Greek::noBacklight(void) {
	_backlightval=LCD_NOBACKLIGHT;
	expanderWrite(0);
}

void LiquidCrystal_I2C_Greek::backlight(void) {
	_backlightval=LCD_BACKLIGHT;
	expanderWrite(0);
}



/*********** mid level commands, for sending data/cmds */

inline void LiquidCrystal_I2C_Greek::command(uint8_t value) {
	send(value, 0);
}


/************ low level data pushing commands **********/

// write either command or data
void LiquidCrystal_I2C_Greek::send(uint8_t value, uint8_t mode) {
	uint8_t highnib=value&0xf0;
	uint8_t lownib=(value<<4)&0xf0;
       write4bits((highnib)|mode);
	write4bits((lownib)|mode); 
}

void LiquidCrystal_I2C_Greek::write4bits(uint8_t value) {
	expanderWrite(value);
	pulseEnable(value);
}

void LiquidCrystal_I2C_Greek::expanderWrite(uint8_t _data){                                        
	Wire.beginTransmission(_Addr);
	printIIC((int)(_data) | _backlightval);
	Wire.endTransmission();   
}

void LiquidCrystal_I2C_Greek::pulseEnable(uint8_t _data){
	expanderWrite(_data | En);	// En high
	delayMicroseconds(1);		// enable pulse must be >450ns
	
	expanderWrite(_data & ~En);	// En low
	delayMicroseconds(50);		// commands need > 37us to settle
} 


// Alias functions

void LiquidCrystal_I2C_Greek::cursor_on(){
	cursor();
}

void LiquidCrystal_I2C_Greek::cursor_off(){
	noCursor();
}

void LiquidCrystal_I2C_Greek::blink_on(){
	blink();
}

void LiquidCrystal_I2C_Greek::blink_off(){
	noBlink();
}

void LiquidCrystal_I2C_Greek::load_custom_character(uint8_t char_num, uint8_t *rows){
		createChar(char_num, rows);
}

void LiquidCrystal_I2C_Greek::setBacklight(uint8_t new_val){
	if(new_val){
		backlight();		// turn backlight on
	}else{
		noBacklight();		// turn backlight off
	}
}

void LiquidCrystal_I2C_Greek::printstr(const char c[]){
	//This function is not identical to the function used for "real" I2C displays
	//it's here so the user sketch doesn't have to be changed 
	print(c);
}


// unsupported API functions
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
void LiquidCrystal_I2C_Greek::off(){}
void LiquidCrystal_I2C_Greek::on(){}
void LiquidCrystal_I2C_Greek::setDelay (int cmdDelay,int charDelay) {}
uint8_t LiquidCrystal_I2C_Greek::status(){return 0;}
uint8_t LiquidCrystal_I2C_Greek::keypad (){return 0;}
uint8_t LiquidCrystal_I2C_Greek::init_bargraph(uint8_t graphtype){return 0;}
void LiquidCrystal_I2C_Greek::draw_horizontal_graph(uint8_t row, uint8_t column, uint8_t len,  uint8_t pixel_col_end){}
void LiquidCrystal_I2C_Greek::draw_vertical_graph(uint8_t row, uint8_t column, uint8_t len,  uint8_t pixel_row_end){}
void LiquidCrystal_I2C_Greek::setContrast(uint8_t new_val){}
#pragma GCC diagnostic pop
	