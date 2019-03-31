#include <FastLED.h>

// Example showing how to use FastLED color functions
// even when you're NOT using a "pixel-addressible" smart LED strip.
//
// This example is designed to control an "analog" RGB LED strip
// (or a single RGB LED) being driven by Arduino PWM output pins.
// So this code never calls FastLED.addLEDs() or FastLED.show().
//
// This example illustrates one way you can use just the portions 
// of FastLED that you need.  In this case, this code uses just the
// fast HSV color conversion code.
// 
// In this example, the RGB values are output on three separate
// 'analog' PWM pins, one for red, one for green, and one for blue.
 
#define REDPIN   5
#define GREENPIN 6
#define BLUEPIN  3

// showAnalogRGB: this is like FastLED.show(), but outputs on 
// analog PWM output pins instead of sending data to an intelligent,
// pixel-addressable LED strip.
// 
// This function takes the incoming RGB values and outputs the values
// on three analog PWM output pins to the r, g, and b values respectively.
void showAnalogRGB( const CRGB& rgb)
{
  analogWrite(REDPIN,   rgb.r );
  analogWrite(GREENPIN, rgb.g );
  analogWrite(BLUEPIN,  rgb.b );
}



// colorBars: flashes Red, then Green, then Blue, then Black.
// Helpful for diagnosing if you've mis-wired which is which.
void colorBars()
{
  showAnalogRGB( CRGB::Red );   delay(1000);
  showAnalogRGB( CRGB::Green ); delay(1000);
  showAnalogRGB( CRGB::Blue );  delay(1000);
  //showAnalogRGB( CRGB::White ); delay(100);
  showAnalogRGB( CRGB::Black ); delay(1000);
}

void colorpallet()
{
  static uint8_t hue;
  hue = hue + 1;
  // Use FastLED automatic HSV->RGB conversion
 showAnalogRGB( CHSV( hue, 255, 255) );

   //colorBars();
  delay(100);
}
void colordef(const CRGB& rgb)
{
    showAnalogRGB(rgb);
   //colorBars();
  //delay(100);
}
void colordef(int c)
{
  showAnalogRGB( c );
   //colorBars();
  //delay(100);
}
void loop() 
{
  const CRGB& rgb.r1 =100;
  const CRGB& rgb.g1 =255;
  const CRGB& rgb.b1 =255;
  //const CRGB& c = 1;
  colordef(r1, g1, b1);
  //colordef();
  
  //colorpallet();
}


void setup() {
  pinMode(REDPIN,   OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(BLUEPIN,  OUTPUT);

  // Flash the "hello" color sequence: R, G, B, black.
 // colorBars();
}
