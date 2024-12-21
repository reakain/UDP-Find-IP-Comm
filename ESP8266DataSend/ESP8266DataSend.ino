#include "UDPFunctions.h"

void setup() {
  // put your setup code here, to run once:
  // Start your UDP setup, which starts up the udp packet listener for reading packets
  udpSetup();
}

void loop() {
  // put your main code here, to run repeatedly:
  // Check if there's packets to read
  if (!haveRemoteInfo) {
    checkPacketContent();
    delay(2);
  }
  else {
    //Read your pin data, or get your data to send
    char dataBits = 0;
    // Then send your data to the remote pc
    sendPacket(dataBits);
    // Currently only delaying a second, adjust as needed
    delay(1000);
  }
  
}
