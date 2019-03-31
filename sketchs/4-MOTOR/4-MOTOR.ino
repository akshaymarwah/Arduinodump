
#define PushButtonb_1 = 7;
#define PushButtonb_2 = 8;
#define PushButtonb_3 = 9;
#define PushButtonb_4 = 10;

#define RPin2 =  5;      
#define RPin3 =  6;      
#define RPin1 =  3;  
#define RPin4 =  4;      


int PushButtonbState_1 = 0; 
int PushButtonbState_2 = 0; 
int PushButtonbState_3 = 0; 
int PushButtonbState_4 = 0;     

int RPinstate1 =  0;   
int RPinstate2 =  0;   
int RPinstate3 =  0;   
int RPinstate4 =  0;      



void setup() {
  // initialize the LED pin as an output:
  Serial.begin(9600);

  // initialize the Relay pin as an input:
  pinMode(RPin1, OUTPUT);
  pinMode(RPin2, OUTPUT);
  pinMode(RPin3, OUTPUT);
  pinMode(RPin4, OUTPUT);
  
  // initialize the pushbutton pin as an input:
  pinMode(PushButtonb_1, INPUT);
  pinMode(PushButtonb_2, INPUT);
  pinMode(PushButtonb_3, INPUT);
  pinMode(PushButtonb_4, INPUT);
}

void buttoninput()
{
  PushButtonb_1 = digitalRead(PushButtonbState_1);
  PushButtonb_2 = digitalRead(PushButtonbState_2);
  PushButtonb_3 = digitalRead(PushButtonbState_3);
  PushButtonb_4 = digitalRead(PushButtonbState_4);
}

void toggle1()
{
  if (RPinstate1 == 1)
    {
      RPinstate1 = 0;
      digitalWrite(RPin1, LOW);
      Serial.println("LED LOW");

    }
    else if (RPinstate1 == LOW)
    {

      RPinstate1 = 1;
      digitalWrite(RPin1, HIGH);
      Serial.println("LED HIGH");
    }
   
}


void toggle2()
{
  if (RPinstate2 == 1)
    {
      RPinstate2 = 0;
      digitalWrite(RPin2, LOW);
      Serial.println("LED LOW");

    }
    else if (RPinstate2 == LOW)
    {

      RPinstate2 = 1;
      digitalWrite(RPin2, HIGH);
      Serial.println("LED HIGH");
    }
   
}


void toggle3()
{
  if (RPinstate3 == 1)
    {
      RPinstate3 = 0;
      digitalWrite(RPin3, LOW);
      Serial.println("LED LOW");

    }
    else if (RPinstate3 == LOW)
    {

      RPinstate3 = 1;
      digitalWrite(RPin3, HIGH);
      Serial.println("LED HIGH");
    }
   
}


void toggle4()
{
  if (RPinstate4 == 1)
    {
      RPinstate4 = 0;
      digitalWrite(RPin4, LOW);
      Serial.println("LED LOW");

    }
    else if (RPinstate4 == LOW)
    {

      RPinstate4 = 1;
      digitalWrite(RPin4, HIGH);
      Serial.println("LED HIGH");
    }
   
}


void loop() {
  // read the state of the pushbutton value:
  
  buttoninput();
    // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  
  
  if (PushButtonb_1 == HIGH) 
  { 
    if(PushButtonb_2 == LOW && PushButtonb_3 ==LOW && PushButtonb_4 && LOW)
    {
    toggle1();
    }
    else 
    Serial.println("LED HIGH");
  }
  else if (PushButtonb_2 == HIGH) 
  {
    if(PushButtonb_1 == LOW && PushButtonb_3 ==LOW && PushButtonb_4 && LOW)
    {
    toggle2();
    }
  }
    
    
    
  while ( rb1 == HIGH)
  {
     rb1 = digitalRead(buttonPin1);
     delay(10);
  }
    
  }
}
