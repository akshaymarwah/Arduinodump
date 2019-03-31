#include <UIPEthernet.h>
#include <SPI.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
//byte ip[] = { 10, 0, 0, 177 };
char server[] = { "www.google.com"}; // Google

EthernetClient client;

void setup()
{
  Serial.begin(9600);
  Serial.println("Start...");
  Ethernet.begin(mac);

  client.connect(server, 80);
  delay(1000);

  Serial.println("connecting...");

  if (client.connected()) {
    Serial.println("connected");
    client.println("GET / HTTP/1.0");
    client.println();
  } else {
    Serial.println("connection failed");
  }
}

void loop()
{
  if (client.available()>0) {
    char c = client.read();
    Serial.print(c);
  }
if (0 == (millis()%1000))
  Serial.println(millis()); //debug output

  if (!client.connected()) { //never true
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();
    for(;;)
      ;
  }
}
