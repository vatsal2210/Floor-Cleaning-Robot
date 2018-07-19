// Sketch by brainstorm ABC for I2C Based Clock Using RTC and 16x2 I2c Display
#include <Wire.h>
#include <Time.h>
#include <DS1307RTC.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>

#define I2C_ADDR    0x27  // Define I2C Address for the PCF8574T 
//---(Following are the PCF8574 pin assignments to LCD connections )----
// This are different than earlier/different I2C LCD displays

#define Rs_pin  0
#define Rw_pin  1
#define En_pin  2
#define BACKLIGHT_PIN  3
#define D4_pin  4
#define D5_pin  5
#define D6_pin  6
#define D7_pin  7

#define  LED_OFF  1
#define  LED_ON  0

/*-----( Declare objects )-----*/  
LiquidCrystal_I2C  lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);



void setup() {

 lcd.begin (16,2);  // initialize the lcd 
// Switch on the backlight
 lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
 lcd.setBacklight(LED_ON);
}

void loop() {
  tmElements_t tm;
// Print our characters on the LCD
 lcd.backlight();  //Backlight ON if under program control

  if (RTC.read(tm)) {
    
    lcd.setCursor(0,0); //Start at character 0 on line 0
    lcd.print("TIME :");
//  lcd.setCursor(6,0); 
    print2digits(tm.Hour);
    lcd.print(':');
    print2digits(tm.Minute);
    lcd.print(':');
    print2digits(tm.Second);
    
    lcd.setCursor(0,1); //Start at character 0 on line 1
    lcd.print("DATE :"); 
    lcd.print(tm.Day);
    lcd.print('/');
    lcd.print(tm.Month);
    lcd.print('/');
    lcd.print(tmYearToCalendar(tm.Year));
   
  } 
  delay(990);
}

void print2digits(int number) {
  if (number >= 0 && number < 10) {
    lcd.print('0');
  }
  lcd.print(number);
}
