/*Version V 1.10
Date: 3/11/2015

Code for interfacing RTC and 20x4 LCD with arduino for vaccum cleaner robot

To display as:

    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9
 0 | |I|N|D|U|S| |R|O|B|O|T|I|C| |C|L|U|B| |
 1 | | | | | | |V|S| |B|O|T| |1| | | | | | |
 2 | | | | | |W|E|L|C|O|M|E| |Y|O|U| | | | |
 3 |2|0|.|1|0|.|1|5| | |0|6|:|3|0|:|4|5|P|M|

by K.P.V.S.Sathvik

*/

#include <Wire.h>
#include <LiquidCrystal.h>
#include <Time.h>
#include <DS1307RTC.h> 
#include <SoftwareSerial.h>



#define MOTORRIGHTA  50      //3
#define MOTORLEFTA   48     //1
#define MOTORRIGHTB 46
#define MOTORLEFTB 44
#define MOTORC 42
#define sw  36
const int sensor_1 = 40;
const int sensor_2 = 38;

const int  tPin = 30;
const int ePin = 31;

double t;
double d;

int sensors[2],i,intensityr=255,intensityl=255,intensity=25,x,count,countl,countr,counts;
byte switch1=false;

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

#define bluetoothTx 10   //tx, rx pins for bluetooth module
#define bluetoothRx 11

SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);

char check;  //char for checking the app response

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
Serial.begin(9600);
 pinMode(sensor_1, INPUT); 
 pinMode(sensor_2, INPUT);
 pinMode(MOTORRIGHTA, OUTPUT);
 pinMode(MOTORRIGHTB, OUTPUT);
 pinMode(MOTORLEFTA, OUTPUT);
 pinMode(MOTORLEFTB, OUTPUT);

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

  digitalWrite(8,LOW);
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  // print out the value you read:
  //Serial.println(sensorValue);
  
  if(sensorValue<150)
  {
    //Serial.print("LED on");
    digitalWrite(8,HIGH);
  }

 /* sensors[0] = 0;
  sensors[1] = 0;
  */
  switch1=false;
  switch1=digitalRead(sw);
  
 if(switch1)
 {
  if((tm.Hour==9)&&(tm.Minute>=0)&&(tm.Minute<=15))
  {
    sensors[0] = digitalRead(sensor_1);
    sensors[1] = digitalRead(sensor_2);
  
  /*for ( i = 0; i < 2;i++)
  {
    // sensors[i] = digitalRead(sensor_);
     sensors[i]=!sensors[i];
  }*/

   Serial.print(sensors[0]);
   Serial.print(" ");
   Serial.print(sensors[1]);
  if(sensors[0]==1 && sensors[1]==1 )
  {
    stopt();
    
  }
  else
  {
    forward();
  }

  pinMode(tPin, OUTPUT);
  digitalWrite(tPin, LOW);
  delayMicroseconds(3);
  digitalWrite(tPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(tPin, LOW);
  delayMicroseconds(10);
  pinMode(ePin, INPUT);
  t = pulseIn(ePin, HIGH);
  d = t /57.1000;
  if (d >= 300 || d <= 0)
    {
      Serial.print(" Out of range");
    }
    else 
    {
      /*Serial.print(t);
      Serial.print(" ");*/
      Serial.print(d);
      Serial.println(" cm");
    }
    if(d>9)
    {
      stopt();
    }
   Serial.println("");
 }
 }
else
{
  
  if(bluetooth.available()>= 0)  //checking if bluetooth is connected or not
  {
      Serial.println("bluetooth available  ");
      check=bluetooth.read();     //reads char send by bluetooth and stores the in variable check 
     // Serial.println(check);
      if(check=='U')
      {   forward();   
          Serial.println(" forward");   }

      if(check=='D')
      {   backward();   
          Serial.println(" backward");   }

      if(check=='L')
      {   left();   
          Serial.println(" left");   }

      if(check=='R')
      {   right();   
          Serial.println(" right");   }

      if(check=='S')
      {   stopt();   
          Serial.println(" stop");   }

      if(check=='1')
      {   vacuum_on();   
          Serial.println("  vacuum_on");   }

      if(check=='0')
      {   vacuum_off();   
          Serial.println(" vacuum_off");   }
      //delay(200);
   }
}
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

void forward()
{
    Serial.print("STRAIGHT ");
    analogWrite(MOTORRIGHTA, intensityr);
    analogWrite(MOTORRIGHTB, 0);
    analogWrite(MOTORLEFTA, intensityl);
    analogWrite(MOTORLEFTB, 0);
  }
  
void stopt()
 {
  Serial.print("STOP ");
    analogWrite(MOTORRIGHTA, 0);
    analogWrite(MOTORRIGHTB, 0);
    analogWrite(MOTORLEFTA, 0);
    analogWrite(MOTORLEFTB, 0);
}


void backward()
{
  Serial.print("BACKWARD ");
    digitalWrite(MOTORRIGHTA,LOW);
    digitalWrite(MOTORRIGHTB,HIGH);
    digitalWrite(MOTORLEFTA,LOW);
    digitalWrite(MOTORLEFTB,HIGH);
}

void left()
{
  Serial.print("LEFT ");
    digitalWrite(MOTORRIGHTA,HIGH);
    digitalWrite(MOTORRIGHTB,LOW);
    digitalWrite(MOTORLEFTA,LOW);
    digitalWrite(MOTORLEFTB,LOW);
}

void right()
{
  Serial.print("RIGHT ");
    digitalWrite(MOTORRIGHTA,LOW);
    digitalWrite(MOTORRIGHTB,LOW);
    digitalWrite(MOTORLEFTA,HIGH);
    digitalWrite(MOTORLEFTB,LOW);
}

void vacuum_on()
{
  Serial.print("VACUUM ON ");
    digitalWrite(MOTORC,HIGH);
}

void vacuum_off()
{
  Serial.print("VACUUM OFF ");
    digitalWrite(MOTORC,LOW);
}
