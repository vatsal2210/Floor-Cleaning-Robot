//Date: 29/10/15

#define MOTORRIGHTA 22       //3
#define MOTORLEFTA   23      //1
#define MOTORRIGHTB 26
#define MOTORLEFTB 27

const int sensor_1 = 40;
const int sensor_2 = 38;

const int  tPin = 47;
const int ePin = 46;

double t;
double d;

int sensors[2],i,intensityr=255,intensityl=255,intensity=25,x,count,countl,countr,counts;


void setup() {

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
 /* sensors[0] = 0;
  sensors[1] = 0;
 */
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
   delay(500);
  
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
