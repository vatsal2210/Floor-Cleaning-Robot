/*Version V 1.20
Date: 20/10/2015

Code for interfacing RTC and 20x4 LCD with arduino for vaccum cleaner robot

To display as:

    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9
 0 | |I|N|D|U|S| |R|O|B|O|T|I|C| |C|L|U|B| |
 1 | | | | | | |V|S| |B|O|T| |1| | | | | | |
 2 | | | | | |W|E|L|C|O|M|E| |Y|O|U| | | | |
 3 |2|0| |N|O|V|.| | |0|6|:|3|0|:|4|5| |P|M|

by K.P.V.S.Sathvik

*/

#include <Wire.h>
#include <LiquidCrystal.h>
#include <Time.h>
#include <DS1307RTC.h> 

#define Rs_pin  0
#define En_pin  2
#define D4_pin  4
#define D5_pin  5
#define D6_pin  6
#define D7_pin  7
#define Rw_pin  8
//#define BACKLIGHT_PIN 3

LiquidCrystal lcd(Rs_pin,En_pin,D4_pin,D5_pin,D6_pin,D7_pin);

tmElements_t tm;  //Object declaration for RTC module

const char *monthName[12] = {
  "Jan.", "Feb.", "Mar.", "Apr.", "May.", "Jun.",
  "Jul.", "Aug.", "Sep.", "Oct.", "Nov.", "Dec."
};

void setup()
{ 
  pinMode(A8,OUTPUT);
  analogWrite(A8,50);
  lcd.begin (20,4); // <<-- our LCD is a 20x4, change for your LCD if needed

// LCD Backlight ON
//lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
//lcd.setBacklight(HIGH);

digitalWrite(Rw_pin,LOW);

}

void loop()
{
  // Print our characters on the LCD
  // lcd.backlight();  //Backlight ON if under program control   
  
  lcd.setCursor(1,0);   //Start at character 1 on line 0
  lcd.print("INDUS ROBOTIC CLUB");
  lcd.setCursor(6,1);   //Go to character 6 on line 1
  lcd.print("VS BOT 1");
  lcd.setCursor(5,2);   //Go to character 5 on line 2
  lcd.print("WELCOME YOU");

  date_time_display();   //Function to display time and Date
  
  delay(500);
}


void date_time_display()  //Function to display time and Date
{
  if (RTC.read(tm)) //Reads the time from RTC module
  {
    
    lcd.setCursor(0,3); //Go to character 0 on line 3
    lcd.print(tm.Day);  //Displays day
    lcd.print(' ');
    /*char Month[12];
    uint8_t monthIndex;
*/
int t=tm.Month;
lcd.print(monthName[t-1]);
    
    /*lcd.print(tm.Month); //Displays month
    lcd.print('.');
    lcd.print(tmYearToCalendar(tm.Year));   //Displays year in two digits
   */
    // Displays time in 12 hours
    //lcd.setCursor(9,3); //Go to character 10 on line 3
    print2digits(Hour());  //Displays hour in two digit
    lcd.print(':');
    print2digits(tm.Minute);  //Displays minute in two digit
    lcd.print(':');
    print2digits(tm.Second);  //Displays second in two digit

    /*
    // Displays time in 24 hours  
    lcd.setCursor(12,3); //Go to character 12 on line 3
    print2digits(tm.Hour());  //Displays hour in two digit
    lcd.print(':');
    print2digits(tm.Minute);  //Displays minute in two digit
    lcd.print(':');
    print2digits(tm.Second);  //Displays second in two digit
    */
  } 
}


void print2digits(int number)   //Function to display a number in two digits
{
  if (number >= 0 && number < 10) 
  {
    lcd.print('0');   //Puts 0 if it is less than 10. For example, if it is 5 than it displays 05
  }

  lcd.print(number);  
}


int Hour()  //Funtion to Display time in 12 hours
{
  int h=tm.Hour;  //Storing hours from RTC module in h
  lcd.setCursor(18,3); //Go to character 10 on line 3
  
  if(h>12)
  {
    h=h-12;
    lcd.print("PM");  //Display PM if h is greater than 12
  }
  else
  {
    lcd.print("AM");  //Display AM if h is less than 12
  }

  lcd.setCursor(9,3); //Go to character 10 on line 3
  
  return h;
}

