#include <FS.h>                   //this needs to be first, or it all crashes and burns...
#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
//needed for library
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager
#include <PubSubClient.h>         //https://github.com/knolleary/pubsubclient
#include <MQTTClient.h>


#include <ArduinoJson.h>          //https://github.com/bblanchon/ArduinoJson


// what pin we're connected to


// Relay Pin
const int mrsPin1 = 2;
const int mrsPin2 = 2;
const int rooftopmotorswitch = 2;
const int mainmotorswitch = 2;
const int led1 = 2;
const int led2 = D2;
const int led3 = D2;
const int led4 = D2;

int mrspin1s = 0;
int mrspin2s = 0;
int rooftopmotorswitchs = 0;
int mainmotorswitchs = 0;
int led1s = 0;
int led2s = 0;
int led3s = 0;
int led4s = 0;
int rooftoptankwaterlevel = 0;
int undergroundtankwaterlevel = 0;
int undergroundtankwaterlevells = -10;
int rooftoptankwaterlevels = -10;
int lastMsgu =0;


char deviceid[40] = "ESPDEVICE1111";




// MQTT settings
WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[128];
long interval = 5000;     // interval at which to send mqtt messages (milliseconds)


//------ MQTT broker settings and topics
char mqtt_server[40] = "broker.shiftr.io";
char username[34] = "virtuinot";
char password[34] = "1234567890";
char mqtt_port[6] = "1883";


//----------topics
const char* willTopic = "ALLAHABAD-Home-COntrolsystem";

const char* apName = "Alld-Home-default-Ap";

//flag for saving data
bool shouldSaveConfig = false;

//callback notifying us of the need to save config
void saveConfigCallback () {
  Serial.println("Should save config");
  shouldSaveConfig = true;
}






//==================LOOP Function





void loop()
{
  // put your main code here, to run repeatedly:

  if (!client.connected())
  {
    reconnect();
  }
  client.loop();

 rtwaterlevel();
  //ugwaterlevel();


}


//==================LOOP Function



//==================SETUP Function

void setup()
{
  pinMode(mrsPin2, OUTPUT);
  pinMode(mrsPin1, OUTPUT);
  pinMode(rooftopmotorswitch, OUTPUT);
  pinMode(mainmotorswitch, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  
  Serial.begin(115200);
  Serial.println();

  //clean FS, for testing
  //SPIFFS.format();

  //read configuration from FS json
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
          strcpy(username, json["username"]);
          strcpy(password, json["password"]);

        } else {
          Serial.println("failed to load json config");
        }
      }
    }
  } else {
    Serial.println("failed to mount FS");
  }
  //end read

  // The extra parameters to be configured (can be either global or just in the setup)
  // After connecting, parameter.getValue() will get you the configured value
  // id/name placeholder/prompt default length
  WiFiManagerParameter custom_mqtt_server("server", "mqtt server", mqtt_server, 40);
  WiFiManagerParameter custom_mqtt_port("port", "mqtt port", mqtt_port, 5);
  WiFiManagerParameter custom_username("username", "username", username, 32);
  WiFiManagerParameter custom_password("password", "password", password, 32);

  //WiFiManager
  //Local intialization. Once its business is done, there is no need to keep it around
  WiFiManager wifiManager;

  //set config save notify callback
  wifiManager.setSaveConfigCallback(saveConfigCallback);

  //set static ip
  //wifiManager.setSTAStaticIPConfig(IPAddress(192,168,1,99), IPAddress(10,0,1,1), IPAddress(255,255,255,0));

  //add all your parameters here
  wifiManager.addParameter(&custom_mqtt_server);
  wifiManager.addParameter(&custom_mqtt_port);
  wifiManager.addParameter(&custom_username);
  wifiManager.addParameter(&custom_password);

  //reset settings
  //wifiManager.resetSettings();

  //set minimu quality of signal so it ignores AP's under that quality
  //defaults to 8%
  //wifiManager.setMinimumSignalQuality();

  //sets timeout until configuration portal gets turned off
  //useful to make it all retry or go to sleep
  //in seconds
  wifiManager.setTimeout(120);

  //fetches ssid and pass and tries to connect
  //if it does not connect it starts an access point with the specified name
  //here  "AutoConnectAP"
  //and goes into a blocking loop awaiting configuration
  if (!wifiManager.autoConnect(apName)) {
    Serial.println("failed to connect and hit timeout");
    delay(3000);
    //reset and try again, or maybe put it to deep sleep
    ESP.reset();
    delay(5000);
  }

  //if you get here you have connected to the WiFi
  Serial.println("connected...yeey :)");

  //read updated parameters
  strcpy(mqtt_server, custom_mqtt_server.getValue());
  strcpy(mqtt_port, custom_mqtt_port.getValue());
  strcpy(username, custom_username.getValue());
  strcpy(password, custom_password.getValue());

  //save the custom parameters to FS
  if (shouldSaveConfig) {
    Serial.println("saving config");
    DynamicJsonBuffer jsonBuffer;
    JsonObject& json = jsonBuffer.createObject();
    json["mqtt_server"] = mqtt_server;
    json["mqtt_port"] = mqtt_port;
    json["username"] = username;
    json["password"] = password;

    File configFile = SPIFFS.open("/config.json", "w");
    if (!configFile) {
      Serial.println("failed to open config file for writing");
    }

    json.printTo(Serial);
    json.printTo(configFile);
    configFile.close();
    //end save
  }

  Serial.println("local ip");
  Serial.println(WiFi.localIP());

  // mqtt
  client.setServer(mqtt_server, atoi(mqtt_port)); // parseInt to the port
  client.setCallback(callback);

}

//==================SETUP Function
