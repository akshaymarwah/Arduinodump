void reconnect()

{
  // Loop until we're reconnected to the MQTT server
  if (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect(deviceid, username, password, willTopic, 0, 1, (String("I'm Live: ") + username).c_str())) 
    { // username as client ID
      Serial.println("connected");
      // Once connected, publish an announcement... (if not authorized to publish the connection is closed)
      //.publish("all", (String("hello from ") + username).c_str());
      // ... and resubscribe
      //client.subscribe("plant/pump");
      client.subscribe("mrs2");
      client.subscribe("mrs1");
      client.subscribe("led1");
      client.subscribe("led2");
      client.subscribe("led3");
      client.subscribe("led4");
      client.subscribe("rtm");
      client.subscribe("mm");
//      client.subscribe("rttwl");
//      client.subscribe("ugtwl");
      //client.subscribe((String("sensors/") + username + String("/")).c_str());
    }
    else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(50);
    }
  }
}
