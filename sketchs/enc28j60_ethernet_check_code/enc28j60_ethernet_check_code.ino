#include <EtherCard.h>

static byte mac[] = { 0x74, 0x69, 0x69, 0x2D, 0x30, 0x31 };
static byte ip[] = { 192, 168, 1, 10 };
byte Ethernet::buffer[500];

void setup () {
    if (ether.begin(sizeof Ethernet::buffer, mac, 8) == 0) 
        Serial.println("Failed to access Ethernet controller");
    if (!ether.staticSetup(ip))
        Serial.println("Failed to set IP address");
}
 
void loop() {
    ether.packetLoop(ether.packetReceive());  
}
