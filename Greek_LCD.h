
#include "LiquidCrystal_I2C.h"


#ifndef GREEK_LCD_H
#define LGREEK_LCD_H


// Define in your main sketch your lcd's ROW and COLUMN number
// or use my predefined values
#ifndef ROWS
    #define ROWS 2
#endif

#ifndef COLUMNS
    #define COLUMNS 16
#endif

#define GAMMA 0
byte Gamma[8] = {0x1F, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x00}; // Γ
#define DELTA 1
byte Delta[8]{0x04, 0x0A, 0x0A, 0x11, 0x11, 0x11, 0x1F, 0x00}; // Δ
#define THITA 2
byte Thita[8]{0x0E, 0x11, 0x11, 0x1F, 0x11, 0x11, 0x11, 0x00}; // Θ
#define LAMBDA 3
byte Lambda[8]{0x04, 0x0A, 0x0A, 0x1B, 0x11, 0x11, 0x11, 0x00}; // Λ
#define XI 4
byte Xi[8]{0x1F, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x1F, 0x00}; // Ξ
#define PI 5
byte Pi[8]{0x1F, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x00}; // Π
#define SIGMA 6
byte Sigma[8]{0x1F, 0x10, 0x08, 0x04, 0x08, 0x10, 0x1F, 0x00}; // Σ
#define PHI 7
byte Phi[8]{0x0E, 0x15, 0x15, 0x15, 0x0E, 0x04, 0x04, 0x00}; // Φ
#define PSI 8
byte Psi[8]{0x15, 0x15, 0x15, 0x0E, 0x04, 0x04, 0x04, 0x00}; // Ψ
#define OMEGA 9
byte Omega[8]{0x0E, 0x11, 0x11, 0x11, 0x11, 0x0A, 0x1B, 0x00}; // Ω





void createGreekChars(LiquidCrystal_I2C lcd){
    lcd.clear();
    lcd.createChar(GAMMA, Gamma);
    lcd.createChar(DELTA, Delta);
    lcd.createChar(THITA, Thita);
    lcd.createChar(LAMBDA, Lambda);
    lcd.createChar(XI, Xi);
    lcd.createChar(PI, Pi);
    lcd.createChar(SIGMA, Sigma);
    lcd.createChar(PHI, Phi);
    lcd.createChar(PSI, Psi);
    lcd.createChar(OMEGA,Omega);
}

void print_greek(LiquidCrystal_I2C lcd, unsigned char text[]){
    
int i=0;

    while(text[i]!='\0'){
         switch (text[i]){
            case 206: case 127: case 207: break;               
            case 145: case 177: case 172:lcd.write('A');
            break;           
            case 146: case 178:lcd.write('B');
            break;               
            case 147: case 179:lcd.write(GAMMA);
            break;
            case 148: case 180:lcd.write(DELTA);
            break;             
            case 149: case 181: case 173:lcd.write('E');
            break;                  
            case 150: case 182: lcd.write('Z');
            break;               
            case 151: case 183: case 174:lcd.write('H');
            break; 
            case 152: case 184: lcd.write(THITA);
            break;             
            case 153: case 185: case 175: case 144: case 138:lcd.write('I');
            break;             
            case 154: case 186: lcd.write('K');
            break;       
            case 155: case 187:lcd.write(LAMBDA);
            break;              
            case 156: case 188: lcd.write('M');
            break;               
            case 157: case 189:lcd.write('N');
            break;               
            case 158: case 190:lcd.write(XI);
            break;   
            case 159: case 191: case 140:lcd.write('O');
            break;                     
            case 160: case 128:lcd.write(PI);
            break; 
            case 161: case 129:lcd.write('P');
            break;  
            case 163: case 131: case 130: lcd.write(SIGMA);
            break; 
            case 164: case 132:lcd.write('T');
            break; 
            case 165: case 133: case 141: case 139: case 176:lcd.write('Y');
            break;                  
            case 166: case 134: lcd.write(PHI);
            break; 
            case 167: case 135: lcd.write('X');
            break;  
            case 168: case 136: lcd.write(PSI);
            break; 
            case 169: case 137: case 142:lcd.write(OMEGA);
            break; 
            default: lcd.write(text[i]);
            //Serial.println(int(text[i]));  c++; break;              
        }
        i++; 
    }
}

#endif 
