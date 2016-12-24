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
    Serial.printf("Received %d bytes from %s, port %d\n", packetSize, Udp.remoteIP().toString().c_str(), Udp.remotePort());
    int len = Udp.read(incomingPacket, 255);
    if (len > 0)
    {
      incomingPacket[len] = 0;
    }

    if(incomingPacket[0] == 255) {
      Serial.printf("uhhhh, Magic!");
    }
    /*int i = 0;
    for (i=0; i<255; i++) {
      Serial.printf("UDP packet contents: %x\n", incomingPacket[i]);
    }
    Serial.printf("\n");*/
  }

}
