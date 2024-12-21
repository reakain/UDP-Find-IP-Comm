#ifndef UDP_FUNCTIONS_H
#define UDP_FUNCTIONS_H

//packet structure, 3 characters long, check that our data starts with the start character, comma splits
// start character
// S
// Mood (0) or distance (1)
// 0
// Value (0-3 for mood, 0-1 for distance)
// 0

// distance value 0 is no person, 1 is person

// So example:
// S00
// S01
// S10


#include <ESP8266WiFi.h>
#include <Ticker.h>
#include <WiFiUdp.h>

// SSID/WIFI info for whatever network you are communicating over
#define WIFI_SSID "Wifi_Name"
#define WIFI_PASSWORD "Wifi_Password"

WiFiEventHandler wifiConnectHandler;
WiFiEventHandler wifiDisconnectHandler;
Ticker wifiReconnectTimer;
WiFiUDP Udp;
unsigned int localUdpPort = 4210;
// Packet to hold data coming into the chip. 
// It was size 4, as a 3 byte message packet + 1 extra for ~safety~
char incomingPacket[7];
char initCommSetupRecvPacket[] = "hello?";
char initCommSetupSendPacket[] = "hello!";
bool haveRemoteInfo = false;

// Variable to hold the ip addr?
IPAddress remoteIPAddr(0,0,0,0);
// Variable to hold the port addr
int remotePortAddr = 4211;

// Variable to hold the data to send out to controlling computer
// It should basically be the length of the packet info you want to send
char replyPacket[] = "Hi there! Got the message :-)";


// Our function for connecting to the wifi
void connectToWifi() {
  //Serial.println("Connecting to Wi-Fi...");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
}

// Once we've connected, we can start our udp port for reading/writing data
void onWifiConnect(const WiFiEventStationModeGotIP& event) {
  //Serial.println("Connected to Wi-Fi.");
  Udp.begin(localUdpPort);
}

// If the wifi disconnects, we'll try to reconnect
void onWifiDisconnect(const WiFiEventStationModeDisconnected& event) {
  //Serial.println("Disconnected from Wi-Fi.");
  wifiReconnectTimer.once(2, connectToWifi);
}

// Call this function in your Sketch setup() function to handle initial wifi setup
void udpSetup()
{
  wifiConnectHandler = WiFi.onStationModeGotIP(onWifiConnect);
  wifiDisconnectHandler = WiFi.onStationModeDisconnected(onWifiDisconnect);
  connectToWifi();
  // WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  // while (WiFi.status() != WL_CONNECTED)
  // {
  //   delay(500);
  //   //Serial.print(".");
  // }
  //Serial.println(" connected");

  //Udp.begin(localUdpPort);
  //Serial.printf("Now listening at IP %s, UDP port %d\n", WiFi.localIP().toString().c_str(), localUdpPort);
}

// Reading packet data
void checkPacketContent()
{
  // If we're not connected to wifi, stop trying to read packets
  if( WiFi.status() != WL_CONNECTED) { return; }
  // This is pulling a packet from your buffer of packets
  int packetSize = Udp.parsePacket();
  if (packetSize)
  {
    // receive incoming UDP packets. the 3 here is assuming your packet length is 3 bytes
    // And it spits those bytes into the incomingPacket array
    //Serial.printf("Received %d bytes from %s, port %d\n", packetSize, Udp.remoteIP().toString().c_str(), Udp.remotePort());
    int len = Udp.read(incomingPacket, 6);

    // Then you handle parsing your packet here
    for (int i = 0; i < 6; i++)
    {
      if(incomingPacket[i] != initCommSetupRecvPacket[i]) {return;}
    }

    remoteIPAddr = Udp.remoteIP();

    Udp.beginPacket(remoteIPAddr, remotePortAddr);
    Udp.write(initCommSetupSendPacket);
    Udp.endPacket();
    
    haveRemoteInfo = true;


    // If you want to send a reply, back to the IP address that sent the packet
    // Then you use the below.
    // send back a reply, to the IP address and port we got the packet from
    //Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    //Udp.write(replyPacket);
    //Udp.endPacket();
}
}

// Writing packet out (if sending more than one byte, get rid of the dataToSend variable)
void sendPacket(char dataToSend)
{
  // To send a packet, you define the IP address (192.168.4.1)you want to send it to,
  // And the port (8888) you want to send it to
  Udp.beginPacket(remoteIPAddr, remotePortAddr);
  // And then you send your packet data, which can be predefined as a variable,
  //Udp.write(replyPacket);
  // Or it can be defined in the moment
  //Udp.write("hello");
  // Or if you're just sending one byte
  Udp.write(dataToSend);
  // I think you can also actually do multiple write calls, because...
  // You signal you're done writing so that the packet sends.
  Udp.endPacket();
}

#endif
