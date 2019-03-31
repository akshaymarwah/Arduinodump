
unsigned long now;
//========funtions to individual activities

void readrttwaterlevelsensor()
{


  now = millis();

  if (now - lastMsg > interval)
  {
    if (rooftoptankwaterlevel == 100)
    {
      rooftoptankwaterlevel = 0;

    }
    else
    {
      rooftoptankwaterlevel += 10;
    }

    if (undergroundtankwaterlevel == 100)
    {
      undergroundtankwaterlevel = 0;

    }
    else
    {
      undergroundtankwaterlevel += 50;
    }
  }
  if(undergroundtankwaterlevells != undergroundtankwaterlevel || rooftoptankwaterlevels!=rooftoptankwaterlevel)
  {
      char rtwl[10];
      char ugwl[10];
  
  
      dtostrf(rooftoptankwaterlevel, 4, 2, rtwl );
      dtostrf(undergroundtankwaterlevel, 4, 2, ugwl);
      client.publish("rttwl", rtwl, true);
      client.publish("ugtwl", ugwl, true);
  
      // save the last time you blinked the LED
      lastMsg = now;
      undergroundtankwaterlevells=undergroundtankwaterlevel;
      //========Call  funtions at regular interval
  
  }

}

void checkrtmon()
{
  
if(undergroundtankwaterlevel>=25)
{
  
  
    //Motor pin on
    if(rooftopmotorswitchs == 1)
    {
      
    }
    else
    {
    rooftopmotorswitchs = 1;
    Serial.println("Roof Top Motor : ON");
    char rtms[10];
    dtostrf(rooftopmotorswitchs, 4, 2, rtms );
    client.publish("rtm", rtms, true);
    }
  
}
else if(undergroundtankwaterlevel<25)
{ 
  if(rooftopmotorswitchs == 0)
    {
      
    }
    else
    { 
    //motor OFF
    rooftopmotorswitchs=0;
    Serial.println("Low water Level in Underground Tank");
    char rtms[10];
    dtostrf(rooftopmotorswitchs, 4, 2, rtms );
    client.publish("rtm", rtms, true);
    }
  } 
}


void checkrtmoff()
{
Serial.println("motor Off debug function");

  //motor Off
 if(rooftopmotorswitchs == 0)
    {
      
    }
    else
    {  
      rooftopmotorswitchs =0;
    
   Serial.println("Roof Top Motor : OFF");
    char rtms[10];
    dtostrf(rooftopmotorswitchs, 4, 2, rtms );
    client.publish("rtm", rtms, true);
    }
}