/*Version V 1.20
Date: 14/10/2015

Code for bluetooth app interface with arduino for vaccum cleaner robot

by K.P.V.S.Sathvik

*/
#include <SoftwareSerial.h>

#define MOTORA1 7  //Right motor 
#define MOTORA2 6
#define MOTORB1 5   //Left motor
#define MOTORB2 4
#define MOTORC 3  //Vaccum motor


#define bluetoothTx 10   //tx, rx pins for bluetooth module
#define bluetoothRx 12

SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);

char check;  //char for checking the app response

//byte fw,bw,rt,lt,on_off,auto_app;//application switchs
void setup() 
{
  pinMode(MOTORA1,OUTPUT);
  pinMode(MOTORA2,OUTPUT);
  pinMode(MOTORB1,OUTPUT);
  pinMode(MOTORB2,OUTPUT);
  pinMode(MOTORC,OUTPUT);
  //pinMode(MOTORC2,OUTPUT); 
 
  Serial.begin(9600);
  bluetooth.begin(9600);
  
}

void loop() 
{
  
  if(bluetooth.available()>= 0)  //checking if bluetooth is connected or not
  {
      Serial.println("bluetooth available  ");
      check=bluetooth.read();     //reads char send by bluetooth and stores the in variable check 
      Serial.println(check);
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
      {   stopm();   
          Serial.println(" stop");   }

      if(check=='1')
      {   vacuum_on();   
          Serial.println("  vacuum_on");   }

      if(check=='0')
      {   vacuum_off();   
          Serial.println(" vacuum_off");   }
      delay(200);
   }     
}

void forward()
{
    digitalWrite(MOTORA1,HIGH);
    digitalWrite(MOTORA2,LOW);
    digitalWrite(MOTORB1,HIGH);
    digitalWrite(MOTORB2,LOW);
}

void backward()
{
    digitalWrite(MOTORA1,LOW);
    digitalWrite(MOTORA2,HIGH);
    digitalWrite(MOTORB1,LOW);
    digitalWrite(MOTORB2,HIGH);
}

void left()
{
    digitalWrite(MOTORA1,HIGH);
    digitalWrite(MOTORA2,LOW);
    digitalWrite(MOTORB1,LOW);
    digitalWrite(MOTORB2,LOW);
}

void right()
{
    digitalWrite(MOTORA1,LOW);
    digitalWrite(MOTORA2,LOW);
    digitalWrite(MOTORB1,HIGH);
    digitalWrite(MOTORB2,LOW);
}

void stopm()
{
    digitalWrite(MOTORA1,LOW);
    digitalWrite(MOTORA2,LOW);
    digitalWrite(MOTORB1,LOW);
    digitalWrite(MOTORB2,LOW);
}

void vacuum_on()
{
    digitalWrite(MOTORC,HIGH);
}

void vacuum_off()
{
    digitalWrite(MOTORC,LOW);
}
