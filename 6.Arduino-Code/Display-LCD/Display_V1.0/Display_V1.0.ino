//Date:12/10/15
//#include <dht11.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Time.h>
#include <DS1307RTC.h> 
#include <LCDI2C.h>


//const char* zile[] =
// { "Lun", "Mar", "Mie", "Joi", "Vin", "Sam", "Dum"}; //days of the week in romanian (not used)
//const char* luni[] =
 //{"Dec", "Ian", "Feb", "Mar", "Apr", "Mai", "Iun", "Iul", "Aug", "Sep", "Oct", "Noi" }; //months of the week also in romanian
 //const char* months[] =
 //{"Dec", "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov" }; //months of the week also in romanian
/*
byte termometru[8] = //icon for termometer
{
    B00100,
    B01010,
    B01010,
    B01110,
    B01110,
    B11111,
    B11111,
    B01110
};

byte picatura[8] = //icon for water droplet 
{
    B00100,
    B00100,
    B01010,
    B01010,
    B10001,
    B10001,
    B10001,
    B01110,
};*/


/*-----( Declare objects )-----*/
// set the LCD address to 0x20 for a 16 chars 2 line display
// Set the pins on the I2C chip used for LCD connections:
//                    addr, en,rw,rs,d4,d5,d6,d7,bl,blpol
  LiquidCrystal_I2C lcd(0x27, 20,4);  // Set the LCD I2C address
//dht11 DHT11;

/*-----( Declare Constants, Pin Numbers )-----*/
//#define DHT11PIN 2 //dht11 signal pin connected to D2

void setup()   /*----( SETUP: RUNS ONCE )----*/
{
  Wire.begin();
  lcd.begin(20,4);         // initialize the lcd for 16 chars 2 lines, turn on backlight
  lcd.backlight();
  lcd.clear();
//   lcd.createChar(1,termometru);
 //  lcd.createChar(2,picatura);
   
   // part code from http://tronixstuff.wordpress.com/
Wire.beginTransmission(0x68);
Wire.write(0x07); // move pointer to SQW address
Wire.write(0x10); // sends 0x10 (hex) 00010000 (binary) to control register - turns on square wave
Wire.endTransmission();
// end part code from http://tronixstuff.wordpress.com/

setSyncProvider(RTC.get);
   
   
}/*--(end setup )---*/

void loop()   /*----( LOOP: RUNS CONSTANTLY )----*/

{
   //afisare_temperatura(); //displaying temperature
   date_time(); //displaying date and time
}

/*void afisare_temperatura() 

{

  int chk = DHT11.read(DHT11PIN);
  lcd.setCursor(1, 1);
  lcd.write(1);
  lcd.setCursor(3, 1);
  lcd.print((float)DHT11.temperature, 0);
  lcd.setCursor(5, 1);
  lcd.print((char)223); //degree sign
  lcd.print("C");
    
  lcd.setCursor(9, 1);
  lcd.write(2);
  lcd.setCursor(11, 1);
  lcd.print((float)DHT11.humidity, 0);
  lcd.print("%");
  delay(2000);

}*/


void date_time()
{ 

  tmElements_t tm;
  (RTC.read(tm));

  lcd.setCursor(0, 0);
  print2digits(tm.Hour);
  lcd.print(":");
  print2digits(tm.Minute);
  lcd.setCursor(7,0); 
  print2digits(tm.Day);
  lcd.print(" ");
  lcd.print(tm.Month);
  lcd.print(" ");
  lcd.print(tmYearToCalendar(tm.Year)-2000);
 // lcd.setCursor(12,1); // this code is used for displaying day of the week
//  lcd.print(tm.Wday[zile-2]); //it's disabled because for some reason it doesn't work on i2c display
}

void print2digits(int number) { //this adds a 0 before single digit numbers
  if (number >= 0 && number < 10) {
    lcd.write('0');
  }
  lcd.print(number);
}

/* ( THE END ) */

