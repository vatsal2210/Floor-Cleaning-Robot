/*                      GPS Time Cock
                   
                   bounts up and down 7.6.5
                            GPS 2,3
                          Buzzer pin 8
     DS18B20 Digital Temperature Sensor Chip Module on 10
   
                              Note
   
                Temperature C' and f' working now
                  satelites fix with befor lcd
                       
                           Alarms
   
*/


#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>
#include <OneWire.h>
#include "pitches.h"

LiquidCrystal_I2C lcd (0x27,20,4);
OneWire  ds(10);

SoftwareSerial mySerial(3, 2);

Adafruit_GPS GPS(&mySerial);
#define GPSECHO  true

boolean usingInterrupt = false;
void useInterrupt(boolean);  // Func prototype keeps Arduino 0023 happy




//                            Alarms songs
                        // notes in the melody:
int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};


void setup()  
{
  Serial.begin(115200); 
  GPS.begin(9600);
  
  lcd.init();                      // initialize the lcd 
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(4,1);
  lcd.print("GPS Time Cock");
  lcd.setCursor(8,2);
  lcd.print("V1.6");
  delay(10000);
  lcd.clear();
  lcd.setCursor(6,0);
  lcd.print("Looking");
  lcd.setCursor(8,1);
  lcd.print("For");
  lcd.setCursor(5,2);
  lcd.print("Satellites");
  
  delay(10000);
  lcd.clear();
  
  
  // get time then open up 
  lcd.clear(); //reset lcd
  lcd.setCursor(7,2); //set cursor of led to front
  lcd.print("'C");
  lcd.setCursor(16,2);
  lcd.print("'F");  
  
  
  // uncomment this line to turn on RMC (recommended minimum) and GGA (fix data) including altitude
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  // uncomment this line to turn on only the "minimum recommended" data
  //GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCONLY);
  // For parsing data, we don't suggest using anything but either RMC only or RMC+GGA since
  // the parser doesn't care about other sentences at this time
  
  // Set the update rate
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);   // 1 Hz update rate
  // For the parsing code to work nicely and have time to sort thru the data, and
  // print it out we don't suggest using anything higher than 1 Hz

  // Request updates on antenna status, comment out to keep quiet
  GPS.sendCommand(PGCMD_ANTENNA);

  // the nice thing about this code is you can have a timer0 interrupt go off
  // every 1 millisecond, and read data from the GPS for you. that makes the
  // loop code a heck of a lot easier!
  useInterrupt(true);

  delay(1000);
  // Ask for firmware version
  mySerial.println(PMTK_Q_RELEASE);
}

// Interrupt is called once a millisecond, looks for any new GPS data, and stores it
SIGNAL(TIMER0_COMPA_vect) {
  char c = GPS.read();
  // if you want to debug, this is a good time to do it!
#ifdef UDR0
  if (GPSECHO)
    if (c) UDR0 = c;  
    // writing direct to UDR0 is much much faster than Serial.print 
    // but only one character can be written at a time. 
#endif
}

void useInterrupt(boolean v) {
  if (v) {
    // Timer0 is already used for millis() - we'll just interrupt somewhere
    // in the middle and call the "Compare A" function above
    OCR0A = 0xAF;
    TIMSK0 |= _BV(OCIE0A);
    usingInterrupt = true;
  } else {
    // do not call the interrupt function COMPA anymore
    TIMSK0 &= ~_BV(OCIE0A);
    usingInterrupt = false;
  }
}

uint32_t timer = millis();
void loop()                     // run over and over again
{
  // in case you are not using the interrupt above, you'll
  // need to 'hand query' the GPS, not suggested :(
  if (! usingInterrupt) {
    // read data from the GPS in the 'main loop'
    char c = GPS.read();
    // if you want to debug, this is a good time to do it!
    if (GPSECHO)
      if (c) Serial.print(c);
  }
  
  // if a sentence is received, we can check the checksum, parse it...
  if (GPS.newNMEAreceived()) {
    // a tricky thing here is if we print the NMEA sentence, or data
    // we end up not listening and catching other sentences! 
    // so be very wary if using OUTPUT_ALLDATA and trytng to print out data
    //Serial.println(GPS.lastNMEA());   // this also sets the newNMEAreceived() flag to false
  
    if (!GPS.parse(GPS.lastNMEA()))   // this also sets the newNMEAreceived() flag to false
      return;  // we can fail to parse a sentence in which case we should just wait for another
  }

  // if millis() or timer wraps around, we'll just reset it
  if (timer > millis())  timer = millis();

  // approximately every 2 seconds or so, print out the current stats
  if (millis() - timer > 2000) { 
    timer = millis(); // reset the timer
    
    lcd.setCursor(3,0);
    
    Serial.print("\nTime: ");
    lcd.print("Time: ");
    Serial.print(GPS.hour, DEC); Serial.print(':'); //++ for 1 houer
    lcd.print((int)GPS.hour); 
    lcd.print(":"),
    Serial.print(GPS.minute, DEC); Serial.print(':');
    lcd.print((int)GPS.minute);
    lcd.print(":");
    Serial.print(GPS.seconds, DEC); Serial.print('.');
    lcd.print((int)GPS.seconds); lcd.print('.');
    
    
    // hide the lcd.print('.') on the lcd

    lcd.setCursor(3,1);
    
    Serial.print("Date: ");
    lcd.print("Date: ");
    Serial.print(GPS.day, DEC); Serial.print('/');
    lcd.print((int)GPS.day);
    lcd.print("-"),
    Serial.print(GPS.month, DEC); Serial.print("/20");
    lcd.print((int)GPS.month);
    lcd.print("-");
    Serial.println(GPS.year, DEC);
    lcd.print("20"),
    lcd.print((int)GPS.year);
    
   // lcd.print("Temperature: ");
   
   
  byte i;
  byte present = 0;
  byte type_s;
  byte data[12];
  byte addr[8];
  
  // Final values
  float celsius, fahrenheit;
  
  // if sensor cannot connect
  if ( !ds.search(addr)) {
    Serial.println("No more addresses.");
    Serial.println();
    ds.reset_search();
    delay(250);
    return;
  }
  
  // get ROM value of sensor (debugging)
  Serial.print("ROM =");
  for( i = 0; i < 8; i++) {
    Serial.write(' ');
    Serial.print(addr[i], HEX);
  }

  if (OneWire::crc8(addr, 7) != addr[7]) {
      Serial.println("CRC is not valid!");
      return;
  }
  Serial.println();
 
  // the first ROM byte indicates which chip
  switch (addr[0]) {
    case 0x10:
      Serial.println(" Chip = DS18S20"); // or old DS1820
      type_s = 1;
      break;
    case 0x28:
      Serial.println(" Chip = DS18B20");
      type_s = 0;
      break;
    case 0x22:
      Serial.println(" Chip = DS1822");
      type_s = 0;
      break;
    default:
      Serial.println("Device is not a DS18x20 family device.");
      return;
  }

  ds.reset();
  ds.select(addr);
  ds.write(0x44, 1); // start conversion, with parasite power on at the end
  
  delay(1000); // maybe 750ms is enough, maybe not
  // we might do a ds.depower() here, but the reset will take care of it.
  
  present = ds.reset();
  ds.select(addr);
  ds.write(0xBE); // Read Scratchpad

  Serial.print(" Data = ");
  Serial.print(present, HEX);
  Serial.print(" ");
  for ( i = 0; i < 9; i++) { // we need 9 bytes
    data[i] = ds.read();
    Serial.print(data[i], HEX);
    Serial.print(" ");
  }
  Serial.print(" CRC=");
  Serial.print(OneWire::crc8(data, 8), HEX);
  Serial.println();

  // Convert the data to actual temperature
  // because the result is a 16 bit signed integer, it should
  // be stored to an "int16_t" type, which is always 16 bits
  // even when compiled on a 32 bit processor.
  int16_t raw = (data[1] << 8) | data[0];
  if (type_s) {
    raw = raw << 3; // 9 bit resolution default
    if (data[7] == 0x10) {
      // "count remain" gives full 12 bit resolution
      raw = (raw & 0xFFF0) + 12 - data[6];
    }
  } else {
    byte cfg = (data[4] & 0x60);
    // at lower res, the low bits are undefined, so let's zero them
    if (cfg == 0x00) raw = raw & ~7; // 9 bit resolution, 93.75 ms
    else if (cfg == 0x20) raw = raw & ~3; // 10 bit res, 187.5 ms
    else if (cfg == 0x40) raw = raw & ~1; // 11 bit res, 375 ms
    //// default is 12 bit resolution, 750 ms conversion time
  }
  celsius = (float)raw / 16.0;
  fahrenheit = celsius * 1.8 + 32.0;
  Serial.print(" Temperature =");
  Serial.print(celsius);
  Serial.print(" Celsius, ");
  Serial.print(fahrenheit);
  Serial.println(" Fahrenheit");
  
  lcd.setCursor(2,2);
  lcd.print(celsius);
  lcd.setCursor(11,2);
  lcd.print(fahrenheit);
    
  
    
    //Gps
    lcd.setCursor(2,3);
    lcd.print("Satellites Fix ");
    lcd.print((int)GPS.satellites);
    Serial.print("Fix: ");
 

}
 }
  

