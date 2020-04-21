#include <Arduino.h>
#include<ESP8266WiFi.h>
#include<PubSubClient.h>

const char* ssid = "IEEEUSICT";
const char* password = "12345678";
const char* mqttuser = "ckbdtizs" ;
const char* mqttpassword = "hASIpo8xbF36";
const char* mqttserver = "soldier.cloudmqtt.com";
const char* device_id = "esp8266";

const int trigP = 2;  //D4 Or GPIO-2 of nodemcu
const int echoP = 0;  //D3 Or GPIO-0 of nodemcu
const int motorPin = 4; //D2 
long duration;
int distance;

int sensorPin = A0;
int enable2 = 13;
int sensorValue2 = 0;

WiFiClient espClient; 
PubSubClient client(espClient);

//const byte ledPin1  ;

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
   pinMode(LED_BUILTIN,HIGH);
 }
   randomSeed(micros());
   pinMode(LED_BUILTIN,LOW);
   Serial.print("Connected to ");
   Serial.println(ssid);
   Serial.println("Wifi IP :-");
   Serial.println(WiFi.localIP());
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
  Serial.begin(9600);
  setup_wifi();
  pinMode(trigP, OUTPUT);  // Sets the trigPin as an Output
  pinMode(echoP, INPUT);
  pinMode(motorPin,OUTPUT);   // Sets the echoPin as an Input
  pinMode(enable2, OUTPUT);
  client.setServer(mqttserver,17702);
  client.setCallback(callback);
  reconnect();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (!client.connected())
  {
    reconnect();
  }
  client.loop();
  digitalWrite(trigP, LOW);   // Makes trigPin low
  delayMicroseconds(2);       // 2 micro second delay 
  digitalWrite(trigP, HIGH);  // tigPin high
  delayMicroseconds(10);      // trigPin high for 10 micro seconds
  digitalWrite(trigP, LOW);   // trigPin low
  duration = pulseIn(echoP, HIGH);   //Read echo pin, time in microseconds
  //Serial.println(duration); 
  distance= duration*0.034/2;        //Calculating actual/real distance
  Serial.print("Distance = ");        //Output distance on arduino serial monitor 
  Serial.println(distance);
  delay(3000);
  char dist[16];   
  itoa(distance,dist,10);
  client.publish("distance",dist);
  if (distance < 40)
  {
    digitalWrite(motorPin,LOW);
  }
  //-------------------WATER SENSOR--------------
  delay(500);
  sensorValue2 = analogRead(sensorPin);
  sensorValue2 = constrain(sensorValue2, 150, 440);
  sensorValue2 = map(sensorValue2, 150, 440, 1023, 0);
  if(sensorValue2 > 20)
  {
    Serial.println("water detected");
    digitalWrite(enable2,HIGH);
  }else
  {
    Serial.println("No water");
    digitalWrite(enable2,LOW);
    Serial.print("water value: ");
    Serial.println(sensorValue2);
    delay(100);
  }
  
}