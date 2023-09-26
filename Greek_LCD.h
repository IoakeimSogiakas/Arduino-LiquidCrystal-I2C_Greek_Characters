
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

#define G_GAMMA 0
byte Greek_Gamma[8] = {0x1F, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x00}; // Γ

#define G_DELTA 1
byte Greek_Delta[8] = {0x04, 0x0A, 0x0A, 0x11, 0x11, 0x11, 0x1F, 0x00}; // Δ

#define G_THITA 2
byte Greek_Thita[8] = {0x0E, 0x11, 0x11, 0x1F, 0x11, 0x11, 0x11, 0x00}; // Θ

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

void createGreekChars(LiquidCrystal_I2C lcd){
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

void print_greek(LiquidCrystal_I2C lcd, unsigned char text[]){
    
int i=0;

    while(text[i]!='\0'){
         switch (text[i]){
            case 206: case 127: case 207: break;               
            case 145: case 177: case 172:lcd.write('A');
            break;           
            case 146: case 178:lcd.write('B');
            break;               
            case 147: case 179:lcd.write(G_GAMMA);
            break;
            case 148: case 180:lcd.write(G_DELTA);
            break;             
            case 149: case 181: case 173:lcd.write('E');
            break;                  
            case 150: case 182: lcd.write('Z');
            break;               
            case 151: case 183: case 174:lcd.write('H');
            break; 
            case 152: case 184: lcd.write(G_THITA);
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

#endif 