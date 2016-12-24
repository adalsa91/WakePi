#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <WiFiUdp.h>

const char* ssid = "HOME";
const char* password = "maBUR8Le.";

const int led = 2;

WiFiUDP Udp;
unsigned int localUdpPort = 9;
char incomingPacket[255];


void setup(void){
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  Udp.begin(localUdpPort);
  Serial.println("Waiting some magic");
}

void loop(void){
  int packetSize = Udp.parsePacket();
  if (packetSize)
  {
    int len = Udp.read(incomingPacket, 255);
    if (len > 0)
    {
      incomingPacket[len] = 0;
    }

    int i = 0;

    //Check for Synchronization Stream (6 bytes of FFh)
    while (i<6 && incomingPacket[i] == 0xff) {
      i++;
    }

    //If Synchronization Stream detected
    if (i == 6){
      uint8_t MAC_array[6];
      WiFi.macAddress(MAC_array);
      i = 0;
      // 16 duplications of MAC address (6 char) = 96 char to iterate 
      while (i<96 && (char)MAC_array[i%6] == incomingPacket[i+6]) { 
        i++;        
      }
      //Magic packet detected
      if (i == 96) {
        Serial.printf("uhhhh, Magic!\n");
        digitalWrite(led, 1);
        delay(500);
        digitalWrite(led, 0);
      }
    }    
  }

}
