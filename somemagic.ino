#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <WiFiUdp.h>

//Wifi characteristics
const char* ssid = "WLAN_XXXX";
const char* password = "xxxxxxxxxxxxxxxx";

const unsigned int localUdpPort = 9; //listen port for magic packet

const byte led = 2; //Integrated led in Nodemcu
const byte relay = 5;//Pin to activate relay to power anything you want (D1 in Nodemcu)

WiFiUDP Udp;
char incomingPacket[255];
byte mac[6];

void setup(void){
  //ESP led output on
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);
  //Relay Pin off
  pinMode(relay, OUTPUT);
  digitalWrite(relay, 0); //First value for relay state
  
  Serial.begin(115200);//Serial debug

  //Print MAC address of Nodemcu
  WiFi.macAddress(mac);
  for(int i = 0; i < 5; i++)
  {
    if(mac[i] < 0x10)
      Serial.print("0");
    Serial.print(mac[i],HEX);
    Serial.print(":");
  }
  Serial.println(mac[5],HEX);

  //Connect to AP
  WiFi.begin(ssid, password);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  //Led off, connected
  pinMode(led, OUTPUT);
  digitalWrite(led, 1);
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
  //Iniciate udp listening for magic packets
  Udp.begin(localUdpPort);
  Serial.println("Waiting some magic");
}

void loop(void){
  //Reading Udp packet
  int packetSize = Udp.parsePacket();
  
  if (packetSize)
  {
    char len = Udp.read(incomingPacket, 255);
    
    //Check for Synchronization Stream (6 bytes of FF)
    uint8_t i = 0;
    while (i < 6 && incomingPacket[i] == 0xff)
      i++;

    //If Synchronization Stream detected
    if (i == 6)
    {
      // 16 duplications of MAC ADDRESS (6 char) = 96 char to iterate, start at i = 6, end i = 96 + 6 = 102
      while (i < 102 && mac[i % 6] == incomingPacket[i])
        i++;
        
      //Magic packet detected
      if (i == 102)
      {      
        Serial.printf("uhhhh, Magic!\n");
        
        //Visual light to show received packet
        digitalWrite(led, 0);
        delay(500);
        digitalWrite(led, 1);
        delay(500);

        //Doing command
        if(len == 108)
        {
          
          //Save command contained in wol password
          char command[6] = {0, 0, 0, 0, 0, 0};
          while (i < len)
          {
            command[i % 6] = incomingPacket[i];
            i++;
          }
          
          //Turn on-off relay stablished in the first byte of the command
          if(command[0] == 1)
          {
            Serial.println("Toggle relay");
            if (digitalRead(relay) == 0)
              digitalWrite(relay, 1);
            else
              digitalWrite(relay, 0);
          }

/*
          if(command[0] == X)
          {
            
          }
          if(command[1] == X)
          {
            
          }

          ...........
*/
        }
        
      }
    }    
  }

}
