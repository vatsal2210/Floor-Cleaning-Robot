//Date 13/10/15
#include <Wire.h>
//#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#include <Time.h>
#include <DS1307RTC.h> 
//#include <NewPing.h>

#define I2C_ADDR    0x27 // <<- Add your address here.
#define Rs_pin  0
#define Rw_pin  8
#define En_pin  2
#define BACKLIGHT_PIN 3
#define D4_pin  4
#define D5_pin  5
#define D6_pin  6
#define D7_pin  7

//#define ECHO_PIN     11  // Arduino pin tied to echo pin on the ultrasonic sensor.
//#define TRIGGER_PIN  12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
//#define MAX_DISTANCE 500 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

//NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

LiquidCrystal_I2C lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);
tmElements_t tm;
void setup()
{
  lcd.begin (20,4); // <<-- our LCD is a 20x4, change for your LCD if needed

// LCD Backlight ON
lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
lcd.setBacklight(HIGH);
digitalWrite(Rw_pin,LOW);
//lcd.home (); // go home on LCD
//lcd.print("Range Finder HC-SR04");  
}

void loop()
{
  //unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
  //unsigned int cm = sonar.convert_cm(uS);  // Convert into centimeters
  
  /*lcd.setCursor (0,1); // go to start of 2nd line
  lcd.print("Current Distance:");
  lcd.setCursor (0,3); // go to start of 4th line
  lcd.print("Ping: ");
  lcd.print(cm);
  lcd.print(" cm ");

  delay(500);*/

  //tmElements_t tm;
// Print our characters on the LCD
 lcd.backlight();  //Backlight ON if under program control
date_time_display();
  /*if (RTC.read(tm)) {
    
    lcd.setCursor(0,0); //Start at character 0 on line 0
    //lcd.print("TIME :");
//  lcd.setCursor(6,0); 
    print2digits(tm.Hour);
    lcd.print(':');
    print2digits(tm.Minute);
    lcd.print(':');
    print2digits(tm.Second);
    
    lcd.setCursor(0,1); //Start at character 0 on line 1
    //lcd.print("DATE :"); 
    lcd.print(tm.Day);
    lcd.print('/');
    lcd.print(tm.Month);
    lcd.print('/');
    lcd.print(tmYearToCalendar(tm.Year));
   
  } 
  delay(990);*/
  lcd.setCursor(2,1);
  lcd.print("INDUS UNIVERSITY");
  lcd.setCursor(6,2);
  lcd.print("V BOT 210");
  lcd.setCursor(5,3);
  lcd.print("WELCOME YOU");
  
}


void date_time_display()
{
  if (RTC.read(tm)) {
    
    lcd.setCursor(0,0); //Start at character 0 on line 0
    //lcd.print("TIME :");
//  lcd.setCursor(6,0); 
    lcd.print("DT:");
    lcd.print(tm.Day);
    lcd.print('/');
    lcd.print(tm.Month);
    lcd.print('/');
    lcd.print(tmYearToCalendar(tm.Year));
   
    lcd.setCursor(15,0);
    print2digits(tm.Hour);
    lcd.print(':');
    print2digits(tm.Minute);
    //lcd.print(':');
    //print2digits(tm.Second);
    
    /*lcd.setCursor(0,1); //Start at character 0 on line 1
    //lcd.print("DATE :"); 
    lcd.print(tm.Day);
    lcd.print('/');
    lcd.print(tm.Month);
    lcd.print('/');
    lcd.print(tmYearToCalendar(tm.Year));*/
   
  } 
  delay(990);
}
void print2digits(int number) {
  if (number >= 0 && number < 10) {
    lcd.print('0');
  }
  lcd.print(number);
}
