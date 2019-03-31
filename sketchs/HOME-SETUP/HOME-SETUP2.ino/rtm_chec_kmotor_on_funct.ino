void checkrtmon()
{
//  Serial.println("Check Motor ON");
  
if(undergroundtankwaterlevel>=25)
{
  
  
    //Motor pin on
    if(rooftopmotorswitchs == 1)
    {
      //Serial.println("RTM rtt swicth : 1");
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
      int nowu = millis();
      if (nowu - lastMsgu > interval)
      {
            Serial.println("UG water level less than 25");
            lastMsgu = nowu;
      }
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
