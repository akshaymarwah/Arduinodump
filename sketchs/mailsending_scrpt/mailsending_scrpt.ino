#include <UIPEthernet.h>
#include <ESPMail.h>

ESPMail mail;
int send = 1;
void setup() 
{


Serial.begin(9600);
  
uint8_t mac[6] = {0x00,0x01,0x02,0x03,0x04,0x05};

  Ethernet.begin(mac,IPAddress(192,168,1,6));
  mail.begin();
}

void loop() {

  if (send == 0)
    return;

  mail.setSubject("akshay.marwah@innovatiview.com", "EMail Subject");
  mail.addTo("akshay.marwah1989@gmail.com");

  mail.setBody("This is an example e-mail.\nRegards Grzesiek");

  Serial.print("Mail subject:");
  
  if (mail.send("smtp.google.com", 587, "akshay.marwah@innovatiview.com", "Trail@12345") == 0)
  {
    Serial.print("Mail send OK");
  }
  else 
  Serial.print("Mail NOT SENT");

  send = 0;
}
