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
  pinMode(trigP, OUTPUT);  // Sets the trigPin as an Output
pinMode(echoP, INPUT);   // Sets the echoPin as an Input

  Serial.begin(9600);
  setup_wifi();
  client.setServer(mqttserver,);
  client.setCallback(callback);
  reconnect();
}

void loop() {
digitalWrite(trigP, LOW);   // Makes trigPin low
delayMicroseconds(2);       // 2 micro second delay 
digitalWrite(trigP, HIGH);  // tigPin high
delayMicroseconds(10);      // trigPin high for 10 micro seconds
digitalWrite(trigP, LOW);   // trigPin low
duration = pulseIn(echoP, HIGH);   //Read echo pin, time in microseconds
distance= duration*0.034/2;        //Calculating actual/real distance
Serial.print("Distance = ");        //Output distance on arduino serial monitor 
Serial.println(distance);
delay(3000);   
  if (!client.connected())
  {
    reconnect();
  }
  client.loop();
  //.
 // .
 // .

  client.publish("distance",)
}
