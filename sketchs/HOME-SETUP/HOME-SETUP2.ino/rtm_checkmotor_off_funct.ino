
void checkrtmoff()
{
  Serial.println("Check Motor OFF");
  
  //motor Off
 if(rooftopmotorswitchs !=0)
 {
  rooftopmotorswitchs =0;
   Serial.println("Roof Top Motor : OFF");
    char rtms[10];
    dtostrf(rooftopmotorswitchs, 4, 2, rtms );
    client.publish("rtms", rtms, true);
    
}
}
