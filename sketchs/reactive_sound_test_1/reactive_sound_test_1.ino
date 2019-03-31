#include <FastLED.h>
#define REDPIN   5
#define GREENPIN 6
#define BLUEPIN  3
#define soundsensor 7
#define mode 10
int mv =0;
void setup() 
{ 
pinMode (soundsensor, INPUT);
pinMode (BLUEPIN, OUTPUT);
pinMode (GREENPIN, OUTPUT);
pinMode (REDPIN, OUTPUT);
pinMode (mode, INPUT);
 mv =0;
}

void loop()

{ 
 

  
  int sensorvalue = digitalRead (soundsensor);

if (sensorvalue == 1)

{
  ledon();
}


else if (sensorvalue == 0)
{
  ledoff();

}
delay(1);
}

  void ledon()
  {
    analogWrite(GREENPIN,  random(200));//delay(5);
    analogWrite(REDPIN,  random(200));//delay(5);
    analogWrite(BLUEPIN,  random(200));
     
  delay(5);
  }

  void ledoff()
  {
colorpallet();
//analogWrite(REDPIN, 50);
//    analogWrite(GREENPIN, 50);
//    analogWrite(BLUEPIN, 50); 
    
    }
 void showAnalogRGB( const CRGB& rgb)
{
  analogWrite(REDPIN,   rgb.r );
  analogWrite(GREENPIN, rgb.g );
  analogWrite(BLUEPIN,  rgb.b );
}
void colorpallet()
{
  static uint8_t hue;
  hue = hue + 1;
  // Use FastLED automatic HSV->RGB conversion
 showAnalogRGB( CHSV( hue, 200, 100) );

   //colorBars();
  delay(10);
}
