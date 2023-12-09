#include <Servo.h>

#include <HardwareSerial.h>
#include<stdio.h>
#include<string.h>
#include <WiFi.h>  
#include <PubSubClient.h>
#include <WiFiClientSecure.h>

static const int servoPin1 = 14; // pin printed as G14 or 14
static const int servoPin2 = 15; // pin printed as G27 or 27
static const int servoPin3 = 26; // pin printed as G26 or 26


  Servo servo1,servo2,servo3 ;
 

//---- WiFi settings
const char* ssid = "";
const char* password = "";

//---- MQTT Broker settings
const char* mqtt_server = ".hivemq.cloud"; // replace with your broker url
const char* mqtt_username = "";
const char* mqtt_password = "";
const int mqtt_port =;
WiFiClientSecure espClient;   // for no secure connection use WiFiClient instead of WiFiClientSecure 
//WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
HardwareSerial SerialPort(2); // use UART2
float newmumber;
char msg[10];
String sensor1 = "";
//int command1 =0;

const char* command1_topic="servo1";
const char* command2_topic="servo2";
const char* command3_topic="servo3";

static const char *root_ca PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIFazCCA1OgAwIBAgIRAIIQz7DSQONZRGPgu2OCiwAwDQYJKoZIhvcNAQELBQAw
TzELMAkGA1UEBhMCVVMxKTAnBgNVBAoTIEludGVybmV0IFNlY3VyaXR5IFJlc2Vh
cmNoIEdyb3VwMRUwEwYDVQQDEwxJU1JHIFJvb3QgWDEwHhcNMTUwNjA0MTEwNDM4
WhcNMzUwNjA0MTEwNDM4WjBPMQswCQYDVQQGEwJVUzEpMCcGA1UEChMgSW50ZXJu
ZXQgU2VjdXJpdHkgUmVzZWFyY2ggR3JvdXAxFTATBgNVBAMTDElTUkcgUm9vdCBY
MTCCAiIwDQYJKoZIhvcNAQEBBQADggIPADCCAgoCggIBAK3oJHP0FDfzm54rVygc
h77ct984kIxuPOZXoHj3dcKi/vVqbvYATyjb3miGbESTtrFj/RQSa78f0uoxmyF+
0TM8ukj13Xnfs7j/EvEhmkvBioZxaUpmZmyPfjxwv60pIgbz5MDmgK7iS4+3mX6U
A5/TR5d8mUgjU+g4rk8Kb4Mu0UlXjIB0ttov0DiNewNwIRt18jA8+o+u3dpjq+sW
T8KOEUt+zwvo/7V3LvSye0rgTBIlDHCNAymg4VMk7BPZ7hm/ELNKjD+Jo2FR3qyH
B5T0Y3HsLuJvW5iB4YlcNHlsdu87kGJ55tukmi8mxdAQ4Q7e2RCOFvu396j3x+UC
B5iPNgiV5+I3lg02dZ77DnKxHZu8A/lJBdiB3QW0KtZB6awBdpUKD9jf1b0SHzUv
KBds0pjBqAlkd25HN7rOrFleaJ1/ctaJxQZBKT5ZPt0m9STJEadao0xAH0ahmbWn
OlFuhjuefXKnEgV4We0+UXgVCwOPjdAvBbI+e0ocS3MFEvzG6uBQE3xDk3SzynTn
jh8BCNAw1FtxNrQHusEwMFxIt4I7mKZ9YIqioymCzLq9gwQbooMDQaHWBfEbwrbw
qHyGO0aoSCqI3Haadr8faqU9GY/rOPNk3sgrDQoo//fb4hVC1CLQJ13hef4Y53CI
rU7m2Ys6xt0nUW7/vGT1M0NPAgMBAAGjQjBAMA4GA1UdDwEB/wQEAwIBBjAPBgNV
HRMBAf8EBTADAQH/MB0GA1UdDgQWBBR5tFnme7bl5AFzgAiIyBpY9umbbjANBgkq
hkiG9w0BAQsFAAOCAgEAVR9YqbyyqFDQDLHYGmkgJykIrGF1XIpu+ILlaS/V9lZL
ubhzEFnTIZd+50xx+7LSYK05qAvqFyFWhfFQDlnrzuBZ6brJFe+GnY+EgPbk6ZGQ
3BebYhtF8GaV0nxvwuo77x/Py9auJ/GpsMiu/X1+mvoiBOv/2X/qkSsisRcOj/KK
NFtY2PwByVS5uCbMiogziUwthDyC3+6WVwW6LLv3xLfHTjuCvjHIInNzktHCgKQ5
ORAzI4JMPJ+GslWYHb4phowim57iaztXOoJwTdwJx4nLCgdNbOhdjsnvzqvHu7Ur
TkXWStAmzOVyyghqpZXjFaH3pO3JLF+l+/+sKAIuvtd7u+Nxe5AW0wdeRlN8NwdC
jNPElpzVmbUq4JUagEiuTDkHzsxHpFKVK7q4+63SM1N95R1NbdWhscdCb+ZAJzVc
oyi3B43njTOQ5yOf+1CceWxG1bQVs5ZufpsMljq4Ui0/1lvh+wjChP4kqKOJ2qxq
4RgqsahDYVvTH9w7jXbyLeiNdd8XM2w9U/t7y0Ff/9yi0GE44Za4rF2LN9d11TPA
mRGunUHBcnWEvgJBQl9nJEiU0Zsnvgc/ubhPgXRR4Xq37Z0j4r7g1SgEEzwxA57d
emyPxgcYxn/eR44/KJ4EBs+lVDR3veyJm+kXQ99b21/+jh5Xos1AnX5iItreGCc=
-----END CERTIFICATE-----
)EOF";



void setup_wifi() {
  delay(10);
  Serial.print("\nConnecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  randomSeed(micros());
  Serial.println("\nWiFi connected\nIP address: ");
  Serial.println(WiFi.localIP());
}




void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "ESP8266Client-";   // Create a random client ID
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str(), mqtt_username, mqtt_password)) {
      Serial.println("connected");

      client.subscribe(command1_topic);   // subscribe the topics here
      client.subscribe(command2_topic);   // subscribe the topics here
      client.subscribe(command3_topic);   // subscribe the topics here
 
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");   // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}



void callback(char* topic, byte* payload, unsigned int length) {
  String incommingMessage = "";
   Serial.println("Message arrived ["+String(topic)+"]"+incommingMessage);
  for (int i = 0; i < length; i++) {incommingMessage+=(char)payload[i];}
  Serial.print("incommingMessage");
 
    
      
    
 
  
      if( strcmp(topic,command1_topic) == 0){
     Serial.print("  ");
     int deg1 = incommingMessage.toInt();
       Serial.println(deg1);
       servo1.write(deg1);
      delay(15);}
        if( strcmp(topic,command2_topic) == 0){
     Serial.print("  ");
     int deg2 = incommingMessage.toInt();
       Serial.println(deg2);
       servo2.write(deg2);
      delay(15);}
        if( strcmp(topic,command3_topic) == 0){
     Serial.print("  ");
     int deg3 = incommingMessage.toInt();
       Serial.println(deg3);
       servo3.write(deg3);
      delay(15);}
  
  
}


void publishMessage(const char* topic, String payload , boolean retained){
  if (client.publish(topic, payload.c_str(), true))
      Serial.println("Message publised ["+String(topic)+"]: "+payload);
}
void setup()
{
   servo1.attach(servoPin1);
   servo2.attach(servoPin2);
   servo3.attach(servoPin3);

  Serial.begin(115200);
  SerialPort.begin(115200, SERIAL_8N1, 16, 17);
  while (!Serial){delay(1);}
  setup_wifi();
  espClient.setCACert(root_ca);      // enable this line and the the "certificate" code for secure connection.
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}


void loop()
{
if (!client.connected()) reconnect();
  client.loop();

     if (SerialPort.available())
  {
     sensor1 = SerialPort.readString();
     //Serial.print(sensor1);
     publishMessage(sensor1_topic,sensor1,true); 
 }
  }
