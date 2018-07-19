#include <math.h>
#include <limits.h>

#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

int red_pin = 10;
int green_pin = 9;

void setup()
{
  lcd.begin(16, 2);
  lcd.print("dlance - MAT 172");
  pinMode( red_pin, OUTPUT );
  pinMode( green_pin, OUTPUT );
}

void loop()
{
  set_displays(millis());
}
 
void set_displays(unsigned long int value)
{
  // cosine function gives LED color and percentage
  // based on time (in milliseconds). Period of cosine
  // determines how long a complete charge / discharge
  // cycle lasts.
  int result = -127.5 * cosf((M_PI / 30000.0) * value) + 127.5;
  
  analogWrite(red_pin, 255-(255-result));
  analogWrite(green_pin, 255-result);

  float percentage = (result / 255.0) * 100;

  lcd.setCursor(0, 1);
  lcd.print("T:");
  lcd.print(value / 1000);
  lcd.setCursor(9, 1);
  lcd.print("Bat:");
  lcd.print((int)percentage);
  lcd.print("% ");
}