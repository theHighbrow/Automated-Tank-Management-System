#include <Arduino.h>
#include<ESP8266WiFi.h>
#include<PubSubClient.h>

const char* ssid = "Dlink";
const char* password = "DLINK100612";
const char* mqttuser = ;
const char* mqttpassword = ;
const char* mqttserver = ;
const char* device_id = "esp8266";

WiFiClient espClient; 
PubSubClient client(espClient);

const byte ledPin1 = ;

char msg_buff[100];

void setup_wifi()
{
  delay(100);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid,password);
  
 while (WiFi.status() != WL_CONNECTED)
 {
   delay(500);
   Serial.println("Connecting...");
   pinMode(BUILTIN_LED,HIGH);
 }
   randomSeed(micros());
   pinMode(LED_BUILTIN,LOW);
   Serial.print("Connected to ");
   Serial.println(ssid);
   Serial.println("Wifi IP :-");
   Serial.println(WiFi.localIP);
}

void reconnect()
{
  while (!client.connected())
  {
    Serial.println("Attempting to Connect to MQTT");
    if (client.connect(device_id,mqttuser,mqttpassword))
    {
      Serial.println("Connected");
      client.publish("OUTTOPIC","Hello world from esp");
      client.subscribe("INTOPIC");
    }
     else
    {
      Serial.println("Connection failed");
      Serial.println(client.state());
      Serial.println("Attempting connection in 5 sec");
      delay(5000);
    }
    
  }
  
}

void callback(char* topic, byte* payload, unsigned int length)
{
  Serial.print("Message arrived of TOPIC :-");
  Serial.println(topic);
  for (int i = 0; i < length; i++)
  {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void setup() {
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
}