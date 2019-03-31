
// ==================Message received through MQTT
void callback(char* topic, byte* payload, unsigned int length)
{



  //=========print received message

  Serial.print("Message arrived on topic:");
  Serial.print(topic);
  Serial.print(" : ");

  for (int i = 0; i < length; i++)
  {
    Serial.print((char)payload[i]);
  }
  Serial.println();




  //========== Switch on the MISC RELAY 1

  if (strcmp(topic, "mrs1") == 0)
  {

    //Serial.println("Topic recognized");
    if ((char)payload[0] == '1') {

      Serial.println("Misc Relay 1 : ON");
      //client.publish("mrs1", "1");
      digitalWrite(mrsPin1, HIGH);   // Turn the Relay on
      mrspin1s = 1;
    }
    else if ((char)payload[0] == '0')
    {
      Serial.println("Misc Relay 1 : OFF");
      digitalWrite(mrsPin1, LOW);  // Turn the Relay off
      mrspin1s = 0;
    }

  }
  // ========Switch on the MISC RELAY 2
  if (strcmp(topic, "mrs2") == 0)
  {

    //Serial.println("Topic recognized");
    if ((char)payload[0] == '1') {

      Serial.println("Misc Relay 2 : ON");
      //client.publish("mrs2", "1");
      digitalWrite(mrsPin2, LOW);   // Turn the Relay on
      mrspin2s = 1;
    }
    else if ((char)payload[0] == '0')
    {
      Serial.println("Misc Relay 2 : OFF");
      digitalWrite(mrsPin2, HIGH);  // Turn the Relay off
      mrspin2s = 0;
    }

  }


  // ========Switch on the Roof top Motor
  if (strcmp(topic, "rtm") == 0)
  {
    //    Serial.println("RTM Topic ");
    if ((char)payload[0] == '1')
    {
      if (undergroundtankwaterlevel >= 25)
      {
        //Motor pin on
        if (rooftopmotorswitchs == 1)
        {
          Serial.println("RTM rtt swicth : 1");
        }
        else
        {

          rooftopmotorswitchs = 1;
          Serial.println("Roof Top Motor NOW : ON");
          char rtms[10];
          dtostrf(rooftopmotorswitchs, 4, 2, rtms );
          client.publish("rtm", rtms, true);
        }

      }
      else if (undergroundtankwaterlevel < 25)
      {
        if (rooftopmotorswitchs == 0)
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
          rooftopmotorswitchs = 0;
          Serial.println("Low water Level in Underground Tank");
          char rtms[10];
          dtostrf(rooftopmotorswitchs, 4, 2, rtms );
          client.publish("rtm", rtms, true);
        }


      }
    }
      else if ((char)payload[0] == '0')
      {

        Serial.println("Check Motor OFF");
  
  //motor Off
                 if(rooftopmotorswitchs !=0)
                 {
                  rooftopmotorswitchs =0;
                   Serial.println("Roof Top Motor : OFF");
                    char rtms[10];
                    dtostrf(rooftopmotorswitchs, 4, 2, rtms );
                    client.publish("rtm", rtms, true);
                    
                }
                        //        Serial.println("RTM Topic :0 ");
      }

    }



    // ========LED Controll
    if (strcmp(topic, "led1") == 0)
    {

      led1s = (int)payload;
      Serial.println(led1s);
      analogWrite(led1, led1s);

    }
    delay(50);


  }
