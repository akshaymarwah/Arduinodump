
//========funtions to individual activities
void rtwaterlevel()
{

  readrttwaterlevelsensor();
  if (isnan(rooftoptankwaterlevel)) 
  {
    Serial.println("Failed to read from Roof Top Water Level Sensors !");
    return;
  }
  else
  {

    if (rooftoptankwaterlevel < 25 && rooftopmotorswitchs ==0)
    {
      checkrtmon();
    }

    else if (rooftoptankwaterlevel >= 100 && rooftopmotorswitchs == 1)
    {
      checkrtmoff();
    }
  }

  //  sprintf (msg, "{\"humidity\": %s, \"temp_celsius\": %s }", hum, temp); // message formatting
  //  Serial.print("Info sent: ");
  //  Serial.println(msg);

}
