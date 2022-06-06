//Interface a 16x2 character LCD in 4-bit mode

#include <LiquidCrystal.h>

const int RS = 12, EN = 11, D4 = 5, D5 = 4, D6 = 3, D7 = 2;
LiquidCrystal lcd(RS,EN,D4,D5,D6,D7);             //set Uno pins that are connected to LCD, 4-bit mode
//LiquidCrystal lcd(RS,EN,D1,D2,D3,D4,D5,D6,D7);  //set Uno pins that are connected to LCD, 8-bit mode

//create custom character, each character is 5x8 (WxH) pixels
byte thumbsup0[8] = {B00100,B00011,B00100,B00011,B00100,B00011,B00010,B00001};
byte thumbsup1[8] = {B00000,B00000,B00000,B00000,B00000,B00000,B00000,B00011};
byte thumbsup2[8] = {B00000,B00000,B00000,B00000,B00000,B00000,B00001,B11110};
byte thumbsup3[8] = {B00000,B01100,B10010,B10010,B10001,B01000,B11110,B00000};
byte thumbsup4[8] = {B00010,B00010,B00010,B00010,B00010,B01110,B10000,B00000};
byte thumbsup5[8] = {B00000,B00000,B00000,B00000,B00000,B10000,B01000,B00110};

void setup() {
  lcd.begin(16,2);    //set 16 columns and 2 rows of 16x2 LCD
  //lcd.begin(20,4);    //set 20 columns and 4 rows of 20x4 LCD 

}

void loop() {
  lcd.print("Hello World");             //print "Hello World" on first row
  delay(3000);                          //delay 3 seconds
  lcd.clear();                          //clear display, sets cursor back to home
  lcd.print("Fuel Your Creativity");    //notice how "Creativity" does not wrap around to next line
  delay(3000);
  lcd.clear();
  lcd.print("Fuel Your");
  lcd.setCursor(0,1);                   //set cursor to column 0, row 1 (rows and columns start from 0)
  lcd.print("Creativity");
  delay(3000);
  lcd.clear();
  lcd.cursor();                         //show visible cursor below next char that will be printed
  delay(3000);
  lcd.noCursor();                       //turns cursor off
  delay(3000);
  lcd.blink();                          //similar to lcd.cursor but creates blinking block cursor
  delay(3000);
  lcd.noBlink();                        //turn blinking cursor off
  delay(3000);
  lcd.print("Fuel Your Creativity");
  delay(3000);
  lcd.scrollDisplayLeft();              //moves "Fuel Your Creativity" to the left by one character
  delay(1000);
  lcd.scrollDisplayLeft();    
  delay(1000);
  lcd.scrollDisplayLeft();    
  delay(1000);
  lcd.scrollDisplayLeft();    
  delay(1000);
  lcd.scrollDisplayRight();             //moves "Fuel Your Creativity" to the right by one character
  delay(1000);
  lcd.scrollDisplayRight();    
  delay(1000);
  lcd.scrollDisplayRight();    
  delay(1000);
  lcd.scrollDisplayRight();    
  delay(3000);
  lcd.clear();

  //display thumbsup character
  lcd.createChar(0, thumbsup0);
  lcd.createChar(1, thumbsup1);
  lcd.createChar(2, thumbsup2);
  lcd.createChar(3, thumbsup3);
  lcd.createChar(4, thumbsup4);
  lcd.createChar(5, thumbsup5);
  lcd.setCursor(2,1);
  lcd.write((uint8_t)0);
  lcd.setCursor(2,0);
  lcd.write(1);
  lcd.setCursor(3,1);
  lcd.write(2);
  lcd.setCursor(3,0);
  lcd.write(3);
  lcd.setCursor(4,1);
  lcd.write(4);
  lcd.setCursor(4,0);
  lcd.write(5);
  delay(3000);
  lcd.clear();

}
