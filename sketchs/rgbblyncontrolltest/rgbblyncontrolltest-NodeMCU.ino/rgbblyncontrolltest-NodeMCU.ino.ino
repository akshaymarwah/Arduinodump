/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************
  For this example you need UIPEthernet library:
    https://github.com/UIPEthernet/UIPEthernet

  Typical wiring would be (this is for Arduino UNO,
  search for correct wiring for your board):
   VCC -- 5V
   GND -- GND
   CS  -- D10
   SI  -- D11
   SCK -- D13
   SO  -- D12
   INT -- D2

  You’ll need:
   - Blynk App (download from AppStore or Google Play)
   - Arduino Uno board
   - Decide how to connect to Blynk
     (USB, Ethernet, Wi-Fi, Bluetooth, ...)

  There is a bunch of great example sketches included to show you how to get
  started. Think of them as LEGO bricks  and combine them as you wish.
  For example, take the Ethernet Shield sketch and combine it with the
  Servo example, or choose a USB sketch and add a code from SendData
  example.
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial
#define BLUEPIN 3
#define REDPIN 5
#define GREENPIN 6
#define soundsensor 9

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <FastLED.h>

char ssid[] = "BahubaliThing-Fiber";
char pass[] = "anything";


int rr=random(200);
int bb=random(200);
int gg=random(200);
int modes = 2;
int sensorvalue =4;
char auth[] = "1c26b675b90e4689b454fb7642f48f89";
BLYNK_WRITE(V0)
{
  modes = param.asInt();
     Serial.println(modes);
}
BLYNK_WRITE(V1)
{
  if(modes==2)
  {
  rr = param[0].asInt(); // get a RED channel value.
  gg = param[1].asInt(); // get a GREEN channel value.
  bb = param[2].asInt(); // get a BLUE channel value.
  Blynk.virtualWrite(V5, rr);
  Blynk.virtualWrite(V6, gg);
  Blynk.virtualWrite(V4, bb);
  

showrgb();
  }
}
BLYNK_WRITE(V5)
{
  if(modes==2)
  {
  rr = param.asInt(); // get a RED channel value.
  Blynk.virtualWrite(V1, rr, gg, bb); 

showrgb();
  }
}

BLYNK_WRITE(V6)
{
  if(modes==2)
  {
  gg = param.asInt(); // get a RED channel value.
  Blynk.virtualWrite(V1, rr, gg, bb); 

showrgb();
  }
}
BLYNK_WRITE(V4)
{
  if(modes==2)
  {
  bb = param.asInt(); // get a RED channel value.
  Blynk.virtualWrite(V1, rr, gg, bb); 

showrgb();
  }
}


void showrgb()
{
  analogWrite(REDPIN,   rr );
  analogWrite(GREENPIN, gg );
  analogWrite(BLUEPIN,  bb );
}
void srl()
{
  //Serial.println("in function");
  if(modes=1)
  {
    //Serial.println("in if condition");
   
   sensorvalue = digitalRead (soundsensor);
    
if (sensorvalue == 1)

{
 
  ledon();
}


else if (sensorvalue == 0)
{
  ledoff();

}
delay(1);
}}
void ledon()
  {
    Serial.println("LED ON");
    analogWrite(GREENPIN,  random(200));
    analogWrite(REDPIN,  random(200));
    analogWrite(BLUEPIN,  random(200));
     
  delay(5);
  }
void ledoff()
  {
    Serial.println("LED OFF");
    colorpallet();
//    Serial.println("LED OFF");
//    analogWrite(REDPIN, 200);
//    analogWrite(GREENPIN, 70);
//    analogWrite(BLUEPIN, 20); 
//    
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
void showAnalogRGB( const CRGB& rgb)
{
  analogWrite(REDPIN,   rgb.r );
  analogWrite(GREENPIN, rgb.g );
  analogWrite(BLUEPIN,  rgb.b );
}
void setup()
{
  // Debug console
  Serial.begin(9600);

Blynk.begin(auth, ssid, pass);
//timer.setInterval(10L, srl); //timer will run every sec 
  // You can also specify server:
  //Blynk.begin(auth, "blynk-cloud.com", 80);
  //Blynk.begin(auth, IPAddress(192,168,1,100), 8080);
  pinMode (BLUEPIN, OUTPUT);
  pinMode (REDPIN, OUTPUT);
  pinMode (GREENPIN, OUTPUT);
   pinMode (soundsensor, INPUT);
   showrgb();
}

void loop()
{
  Blynk.run();
  if (modes==1)           //romantic mood
{
//Serial.println("mode 1");
  srl();
}

 if (modes==3)           //romantic mood
    {
  rr=255;
  bb=20;
  gg=10;

  showrgb();
}
else if (modes==4)         //green mood
{
  
  rr=13;
  bb=10;
  gg=255;
  

  showrgb();
}
else if (modes==5)       //night sleep
{
  
  rr=50;
  bb=50;
  gg=50;
  

  showrgb();
}

}
