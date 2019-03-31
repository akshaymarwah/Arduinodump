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
      undergroundtankwaterlevel += 25;
    }
   if(undergroundtankwaterlevells != undergroundtankwaterlevel)
  {
      char ugwl[10];
      dtostrf(undergroundtankwaterlevel, 4, 2, ugwl);
      client.publish("ugtwl", ugwl, true);
        Serial.print("undergroundtankwaterlevel: ");
    Serial.println(undergroundtankwaterlevel);
      undergroundtankwaterlevells = undergroundtankwaterlevel;


     
  }


  
 if(rooftoptankwaterlevels!=rooftoptankwaterlevel )
  {
      char rtwl[10];
      dtostrf(rooftoptankwaterlevel, 4, 2, rtwl );
      client.publish("rttwl", rtwl, true);
      Serial.print("rooftoptankwaterlevel: ");
    Serial.println(rooftoptankwaterlevel);




    char testpub[10];
    
    int dummys;
    if(rooftoptankwaterlevel <=50){
    dummys =0;
    }
    else {dummys =1;}
          dtostrf(dummys, 4, 2, testpub );
          client.publish("mrs2", testpub, true);



          
      rooftoptankwaterlevels = rooftoptankwaterlevel;
      //========Call  funtions at regular interval
  
  }
lastMsg = now;
  }
}
