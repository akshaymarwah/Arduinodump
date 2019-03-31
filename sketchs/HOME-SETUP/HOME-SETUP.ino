//---------------------------------------------------------------
// This example uses an ESP8266 or ESP32 Board to connect to shiftr.io.
// Modified by Ilias Lamprou at sep/25/2018
// You can check on your device after a successful connection here: https://shiftr.io/try.
// Original example by Joël Gähwiler https://github.com/256dpi/arduino-mqtt
//---------------------------------------------------------------
#include <FS.h>                   //this needs to be first, or it all crashes and burns...
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager
#include <ArduinoJson.h>          //https://github.com/bblanchon/ArduinoJson
#include <ESP8266WiFi.h>  // ESP8266
#include <MQTTClient.h>

//------ wifi settings

const char ssid[] = "BahubaliThing-Fiber";
const char pass[] = "anything";


//------ wifi settings save in FS
bool shouldSaveConfig = false;
bool initialConfig = false;


//------ wifi settings Call function
void saveConfigCallback () {
  Serial.println("Should save config");
  shouldSaveConfig = true;
}

int timeout           = 120; // seconds to run for


//------ MQTT broker settings and topics
const char* broker = "broker.shiftr.io"; 
char mqttUserName[] = "virtuinot";         
char mqttPass[] = "1234567890";               

//=========WIFI manager


void ondemandwifiCallback () {
  ticker.attach(0.2, tick);
  //WiFiManager
  //Local intialization. Once its business is done, there is no need to keep it around
  WiFiManager wifiManager;
wifiManager.setAPStaticIPConfig(IPAddress(192,168,1,11), IPAddress(192,168,1,1), IPAddress(255,255,255,0)); 

  //set config save notify callback
  wifiManager.setSaveConfigCallback(saveConfigCallback);
  

  wifiManager.setCustomHeadElement("<style>html{ background-color: #01DF3A;}</style><div class='s'><svg version='1.1' id='l' x='0' y='0' viewBox='0 0 200 200' xml:space='preserve'><path d='M59.3,2.5c18.1,0.6,31.8,8,40.2,23.5c3.1,5.7,4.3,11.9,4.1,18.3c-0.1,3.6-0.7,7.1-1.9,10.6c-0.2,0.7-0.1,1.1,0.6,1.5c12.8,7.7,25.5,15.4,38.3,23c2.9,1.7,5.8,3.4,8.7,5.3c1,0.6,1.6,0.6,2.5-0.1c4.5-3.6,9.8-5.3,15.7-5.4c12.5-0.1,22.9,7.9,25.2,19c1.9,9.2-2.9,19.2-11.8,23.9c-8.4,4.5-16.9,4.5-25.5,0.2c-0.7-0.3-1-0.2-1.5,0.3c-4.8,4.9-9.7,9.8-14.5,14.6c-5.3,5.3-10.6,10.7-15.9,16c-1.8,1.8-3.6,3.7-5.4,5.4c-0.7,0.6-0.6,1,0,1.6c3.6,3.4,5.8,7.5,6.2,12.2c0.7,7.7-2.2,14-8.8,18.5c-12.3,8.6-30.3,3.5-35-10.4c-2.8-8.4,0.6-17.7,8.6-22.8c0.9-0.6,1.1-1,0.8-2c-2-6.2-4.4-12.4-6.6-18.6c-6.3-17.6-12.7-35.1-19-52.7c-0.2-0.7-0.5-1-1.4-0.9c-12.5,0.7-23.6-2.6-33-10.4c-8-6.6-12.9-15-14.2-25c-1.5-11.5,1.7-21.9,9.6-30.7C32.5,8.9,42.2,4.2,53.7,2.7c0.7-0.1,1.5-0.2,2.2-0.2C57,2.4,58.2,2.5,59.3,2.5z M76.5,81c0,0.1,0.1,0.3,0.1,0.6c1.6,6.3,3.2,12.6,4.7,18.9c4.5,17.7,8.9,35.5,13.3,53.2c0.2,0.9,0.6,1.1,1.6,0.9c5.4-1.2,10.7-0.8,15.7,1.6c0.8,0.4,1.2,0.3,1.7-0.4c11.2-12.9,22.5-25.7,33.4-38.7c0.5-0.6,0.4-1,0-1.6c-5.6-7.9-6.1-16.1-1.3-24.5c0.5-0.8,0.3-1.1-0.5-1.6c-9.1-4.7-18.1-9.3-27.2-14c-6.8-3.5-13.5-7-20.3-10.5c-0.7-0.4-1.1-0.3-1.6,0.4c-1.3,1.8-2.7,3.5-4.3,5.1c-4.2,4.2-9.1,7.4-14.7,9.7C76.9,80.3,76.4,80.3,76.5,81z M89,42.6c0.1-2.5-0.4-5.4-1.5-8.1C83,23.1,74.2,16.9,61.7,15.8c-10-0.9-18.6,2.4-25.3,9.7c-8.4,9-9.3,22.4-2.2,32.4c6.8,9.6,19.1,14.2,31.4,11.9C79.2,67.1,89,55.9,89,42.6z M102.1,188.6c0.6,0.1,1.5-0.1,2.4-0.2c9.5-1.4,15.3-10.9,11.6-19.2c-2.6-5.9-9.4-9.6-16.8-8.6c-8.3,1.2-14.1,8.9-12.4,16.6C88.2,183.9,94.4,188.6,102.1,188.6z M167.7,88.5c-1,0-2.1,0.1-3.1,0.3c-9,1.7-14.2,10.6-10.8,18.6c2.9,6.8,11.4,10.3,19,7.8c7.1-2.3,11.1-9.1,9.6-15.9C180.9,93,174.8,88.5,167.7,88.5z'/></svg>");

  //set minimu quality of signal so it ignores AP's under that quality
  //defaults to 8%
  wifiManager.setMinimumSignalQuality();

  // set configportal timeout
    wifiManager.setConfigPortalTimeout(timeout);

    if (!wifiManager.startConfigPortal("HomeControl-OnDemandAP")) {
      Serial.println("failed to connect and hit timeout");
      delay(3000);
      //reset and try again, or maybe put it to deep sleep
      ESP.restart();
      delay(5000);
    }
    //if you get here you have connected to the WiFi
    Serial.println("connected...yeey :)");
 
  
}







//------ MQTT Topic initialisations

const char* topic_pub_temperature = "temperature"; 
const char* topic_pub_humidity = "humidity"; 
const char* topic_sub_motor_command = "motor_command"; 





WiFiClient net;
MQTTClient client;
unsigned long lastMillis = 0;



//========================================= connect
void connect() {
  Serial.print("\nconnecting to wifi.");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(5000);
  }
  //--- create a random client id
  char clientID[] ="ALLDMOTOR_001";  // For random generation of client ID.
//  for (int i = 10; i <18 ; i++) clientID[i]=  char(48+random(10));
//    
  Serial.print("\nconnecting to broker...");
  while (!client.connect(clientID,mqttUserName,mqttPass)) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("\nconnected!");
  
  
  
  //=============================Topic subscrition 
  
  
  client.subscribe(topic_sub_motor_command);
  // client.unsubscribe("motor_command");
}

//========================================= messageReceived



void messageReceived(String &topic, String &payload) {
  Serial.println("incoming: " + topic + " - " + payload);
  
  
  //========================================= filter messageReceived topic vise and call respective Function
  
  
  
  if (topic==topic_sub_motor_command){
    int v = payload.toInt();
    if (v==0) digitalWrite(2,HIGH);
    else digitalWrite(2,LOW);
  }
  }









//========================================= setup


void setup() {

  //========================================= Begin Serial
  Serial.begin(9600);
  
  
 //========================================= read configuration from FS json

 if (WiFi.SSID()==""){   
    initialConfig = true;
  }
  Serial.println("mounting FS...");

  if (SPIFFS.begin()) {
    Serial.println("mounted file system");
    if (SPIFFS.exists("/config.json")) {
      //file exists, reading and loading
      Serial.println("reading config file");
      File configFile = SPIFFS.open("/config.json", "r");
      if (configFile) {
        Serial.println("opened config file");
        size_t size = configFile.size();
        // Allocate a buffer to store contents of the file.
        std::unique_ptr<char[]> buf(new char[size]);

        configFile.readBytes(buf.get(), size);
        DynamicJsonBuffer jsonBuffer;
        JsonObject& json = jsonBuffer.parseObject(buf.get());
        json.printTo(Serial);
        if (json.success()) {
          Serial.println("\nparsed json");

          strcpy(mqtt_server, json["mqtt_server"]);
          strcpy(mqtt_port, json["mqtt_port"]);
          strcpy(blynk_token, json["blynk_token"]);

        } else {
          Serial.println("failed to load json config");
        }
        configFile.close();
      }
    }
  } else {
    Serial.println("failed to mount FS");
  }








  
  
  
  //========================================= Begin WIFI
  
  WiFi.begin(ssid, pass); // Note: Local domain names (e.g. "Computer.local" on OSX) are not supported by Arduino. You need to set the IP address directly.
  
  
  
  //========================================= Begin MQTT
  client.begin(broker, net);
  
  
  //========================================= Initialise Pins
  pinMode(2,OUTPUT);
    //========================================= CHeck Ussage
  client.onMessage(messageReceived);
    //========================================= CHeck Ussage
  connect();
}



//========================================= loop

void loop() {
  client.loop();
  delay(10);  // <- fixes some issues with WiFi stability
//========================================= Check Wifi Connection or connect auto  
  if (!client.connected())connect();

//========================================= WORKING CODE   (call all functions)
  if (millis() - lastMillis > 5000) {
    int sensorValue_1=random(100);  // replace with your sensor value
    int sensorValue_2=random(100);  // replace with your sensor value
    client.publish(topic_pub_temperature, String(sensorValue_1),true,1);
    client.publish(topic_pub_humidity, String(sensorValue_1),true,1);
//    if(sensorValue_1<50)
//    {
//      client.publish(topic_sub_motor_command, "0",true,1);
//    }
//    if(sensorValue_1>50)
//    {
//      client.publish(topic_sub_motor_command, "1",true,1);
//    }
    lastMillis = millis();
  }
}



//========================================= Write functions to work upon
