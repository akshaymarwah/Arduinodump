//Van der Stappen © 

#define REDPIN 5   
#define GREENPIN 6
#define BLUEPIN 3

int redNow;
int blueNow;
int greenNow;
int redNew;
int blueNew;
int greenNew;

void setup()
{
  pinMode(7,INPUT); //SIG of the Parallax Sound Impact Sensor connected to Digital Pin 7 
  pinMode(REDPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(BLUEPIN, OUTPUT);
  redNow = random(255);
  blueNow = random(255);
  greenNow = random(255);
  redNew = redNow;
  blueNew = blueNow;
  greenNew = greenNow;

}

#define fade(x,y) if (x>y) x--; else if (x<y) x++;

void loop()
{
  boolean soundstate = digitalRead(7);
  if (soundstate == 1) {
    analogWrite(BLUEPIN, blueNow);
    analogWrite(REDPIN, redNow);
    analogWrite(GREENPIN, greenNow);
    redNew = random(255);
    blueNew = random(255);
    greenNew = random(255);
    // fade to new colors
    while ((redNow != redNew) ||
      (blueNow != blueNew) ||
      (greenNow != greenNew))
    {
      fade(redNow,redNew)
        fade(blueNow,blueNew)
          fade(greenNow,greenNew)
            analogWrite(BLUEPIN, blueNow);
      analogWrite(REDPIN, redNow);
      analogWrite(GREENPIN, greenNow);
      delay(1);
    }
  }
  else{ 
    digitalWrite(REDPIN,0);
    digitalWrite(GREENPIN,0);
    digitalWrite(BLUEPIN,0);
  }
}
