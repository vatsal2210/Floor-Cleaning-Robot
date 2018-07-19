/*
Version 1.0-Random floor cleaning
Date 9/10/15

Code for interfacing three ultrasonic sensors with arduino for driving vaccum cleaner robot in autonomous mode.

by K.P.V.S.Sathvik

f-> front ultrasonic sensor
r-> right ultrasonic sensor
l-> left ultrasonic sensor
*/

#define tPin_f  2  //trigger pin
#define ePin_f  3  //echo pin
#define tPin_r  4
#define ePin_r  5
#define tPin_l  6
#define ePin_l  7
/*#define m1_a  5  //left motor
#define m1_b  4 
#define m2_a  3  //right motor
#define m2_b  2*/
float d_f, d_r, d_l ;  //distance for front, right, left sensors
float t_f, t_r, t_l;   //time for front, right, left sensors
void setup() 
{
  Serial.begin(9600);
  
  pinMode(tPin_f, OUTPUT);
  //pinMode(ePin_f,INPUT);
  pinMode(tPin_r, OUTPUT);
  //pinMode(ePin_r,INPUT);
  pinMode(tPin_l, OUTPUT);
  //pinMode(ePin_l,INPUT);
  /*pinMode(m1_a, OUTPUT);
  pinMode(m1_b, OUTPUT);
  pinMode(m2_a, OUTPUT);
  pinMode(m2_b, OUTPUT);  */
}

void loop() 
{
  /*digitalWrite(tPin_f, LOW);
  digitalWrite(tPin_r, LOW);
  digitalWrite(tPin_l, LOW);
  delayMicroseconds(3);
  digitalWrite(tPin_f, HIGH);
  digitalWrite(tPin_r, HIGH);
  digitalWrite(tPin_l, HIGH);
  delayMicroseconds(10);
  digitalWrite(tPin_f, LOW);
  digitalWrite(tPin_r, LOW);
  digitalWrite(tPin_l, LOW);
  delayMicroseconds(10);
  pinMode(ePin_f, INPUT);
  pinMode(ePin_r, INPUT);
  pinMode(ePin_l, INPUT);
  t_f = pulseIn(ePin_f, HIGH);
  t_r = pulseIn(ePin_r, HIGH);
  t_l = pulseIn(ePin_l, HIGH);
  d_f = (t_f * 34 * 3)/1800;
  d_r = (t_r * 34 * 3)/1800;
  d_l = (t_l * 34 * 3)/1800;*/

  //Front ultasonic sensor
  digitalWrite(tPin_f, LOW);   
  delayMicroseconds(3);
  digitalWrite(tPin_f, HIGH);
  delayMicroseconds(10);
  digitalWrite(tPin_f, LOW);
  delayMicroseconds(10);
  pinMode(ePin_f, INPUT);
  t_f = pulseIn(ePin_f, HIGH);
  d_f = (t_f * 34 * 3)/5800;    //calculating distance for front ultasonic sensor

  //Right ultasonic sensor
  digitalWrite(tPin_r, LOW);
  delayMicroseconds(3);
  digitalWrite(tPin_r, HIGH);
  delayMicroseconds(10);
  digitalWrite(tPin_r, LOW);
  delayMicroseconds(10);
  pinMode(ePin_r, INPUT);
  t_r = pulseIn(ePin_r, HIGH);
  d_r = (t_r * 34 * 3)/5800;   //calculating distance for right ultasonic sensor

  //Left ultasonic sensor
  digitalWrite(tPin_l, LOW);
  delayMicroseconds(3);
  digitalWrite(tPin_l, HIGH);
  delayMicroseconds(10);
  digitalWrite(tPin_l, LOW);
  delayMicroseconds(10);
  pinMode(ePin_l, INPUT);
  t_l = pulseIn(ePin_l, HIGH);
  d_l = (t_l * 34 * 3)/5800;  //calculating distance for left ultasonic sensor
  

  
  /*if (d >= 200 || d <= 0)
    {
      Serial.println("Out of range");
    }
    else*/ 
    {
      Serial.print("Front:");
      Serial.print(d_f);          
      Serial.println(" cm");
      
      Serial.print("Right:");
      Serial.print(d_r);
      Serial.println(" cm  ");
      
      Serial.print("Left:");
      Serial.print(d_l);
      Serial.println(" cm  ");
      Serial.println("  ");
    }
    
    /*if (d_f < 20)
    {
      
      reverse();        //If front sensor distance is less than 20 than take reverse for 1 second
      delay(1000);
      
      if(d_r>20)        //than if right sensor distance is greater than 20 than take right
      {  right_turn(); }
      
      else if(d_l>20)   //or if left sensor distance is greater than 20 than take left
      {   left_turn(); }
      
      else              //or if both those conditions are wrong than take more reverse 
      { reverse();  }
    }
    
    else
    {
      forward();              //If front sensor distance is greater than 20 than go forward
      Serial.print("forward");
    }*/

    delay(2000);
}


/*
void forward()
{
digitalWrite(m1_a, HIGH);
digitalWrite(m1_b, LOW);
digitalWrite(m2_a, HIGH);
digitalWrite(m2_b, LOW);
}

void reverse()
{
digitalWrite(m1_a, LOW);
digitalWrite(m1_b, HIGH);
digitalWrite(m2_a, LOW);
digitalWrite(m2_b, HIGH);
}

void right_turn()
{
digitalWrite(m1_a, HIGH);
digitalWrite(m1_b, LOW);
digitalWrite(m2_a, LOW);
digitalWrite(m2_b, LOW);
delay(2000);
}

void left_turn()
{
digitalWrite(m1_a, LOW);
digitalWrite(m1_b, LOW);
digitalWrite(m2_a, HIGH);
digitalWrite(m2_b, LOW);
delay(2000);
}  
*/
