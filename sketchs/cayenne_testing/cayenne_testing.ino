// A simple web server that shows temperature and controlls an LED

#include <UIPEthernet.h>

int celsius,celsiusF;
int outputPin = 3; //the LED pin
static uint8_t mac[6] = {
 0x54, 0x55, 0x58, 0x10, 0x00, 0x24};   // this just needs to be unique for your network, 
// so unless you have more than one of these boards
// connected, you should be fine with this value.

static uint8_t ip[4] = {
 192, 168, 1, 15};                       // the IP address for your board. Check your home hub
// to find an IP address not in use and pick that
// this or 10.0.0.15 are likely formats for an address
// that will work.

static uint16_t port = 80;                                      // Use port 80 - the standard for HTTP

ETHER_28J60 e;

void setup()
{ 
 Serial.begin(9600);
 e.setup(mac, ip, port);
}

void loop()
{
 char* params;

 if (params = e.serviceRequest())
 {
   e.print("<H1>Temperature<br/>");
   e.print(celsius);
   e.print(",");
   e.print(celsiusF);
   e.print(" C</H1>");
   e.print("<br><br>");
   e.print("<br><br>");
   e.print("<H1>LED control</H1>");

   e.print("<A HREF='?cmd=off'>Turn off</A><br>");
   e.print("<A HREF='?cmd=on'>Turn on</A><br><br>");

   if (strcmp(params, "?cmd=on") == 0)
   {
     digitalWrite(outputPin, HIGH);
     e.print("LED is ON");

   }
   else if (strcmp(params, "?cmd=off") == 0) 
   {
     digitalWrite(outputPin, LOW);
     e.print("LED is OFF");

   }





   e.respond();
   delay(100);
 }
 else
 {
   { 
     byte i;
     byte present = 0;
     byte type_s;
     byte data[12];
     byte addr[8];


     if ( !ds.search(addr)) {
       Serial.println("No more addresses.");
       Serial.println();
       ds.reset_search();
       delay(250);
       return;
     }

     Serial.print("ROM =");
     for( i = 0; i < 8; i++) {
       Serial.write(' ');
       Serial.print(addr[i], HEX);
     }

     if (OneWire::crc8(addr, 7) != addr[7]) {
       Serial.println("CRC is not valid!");
       return;
     }
     Serial.println();

     // the first ROM byte indicates which chip
     switch (addr[0]) {
     case 0x10:
       Serial.println("  Chip = DS18S20");  // or old DS1820
       type_s = 1;
       break;
     case 0x28:
       Serial.println("  Chip = DS18B20");
       type_s = 0;
       break;
     case 0x22:
       Serial.println("  Chip = DS1822");
       type_s = 0;
       break;
     default:
       Serial.println("Device is not a DS18x20 family device.");
       return;
     } 

     ds.reset();
     ds.select(addr);
     ds.write(0x44,1);         // start conversion, with parasite power on at the end

     delay(10);     // maybe 750ms is enough, maybe not
     // we might do a ds.depower() here, but the reset will take care of it.

     present = ds.reset();
     ds.select(addr);    
     ds.write(0xBE);         // Read Scratchpad

     Serial.print("  Data = ");
     Serial.print(present,HEX);
     Serial.print(" ");
     for ( i = 0; i < 9; i++) {           // we need 9 bytes
       data[i] = ds.read();
       Serial.print(data[i], HEX);
       Serial.print(" ");
     }
     Serial.print(" CRC=");
     Serial.print(OneWire::crc8(data, 8), HEX);
     Serial.println();

     // convert the data to actual temperature

     unsigned int raw = (data[1] << 8) | data[0];
     if (type_s) {
       raw = raw << 3; // 9 bit resolution default
       if (data[7] == 0x10) {
         // count remain gives full 12 bit resolution
         raw = (raw & 0xFFF0) + 12 - data[6];
       }
     } 
     else {
       byte cfg = (data[4] & 0x60);
       if (cfg == 0x00) raw = raw << 3;  // 9 bit resolution, 93.75 ms
       else if (cfg == 0x20) raw = raw << 2; // 10 bit res, 187.5 ms
       else if (cfg == 0x40) raw = raw << 1; // 11 bit res, 375 ms
       // default is 12 bit resolution, 750 ms conversion time
     }
     celsius = abs(raw / 16.0);
     celsiusF= (raw / 16.0 - celsius) * 100;
     Serial.print("  Temperature = ");
     Serial.print(celsius);
     Serial.print(",");
     Serial.println(celsiusF);
   }
 }
}
