#include "PressureTransducer.h"
#include <SCMPacket.h>

using namespace RPL;

PressureTransducer::PressureTransducer(int id) : id(id){

}

int PressureTransducer::writeValueToBuffer(char buffer[]){
  char packetId[2];
  char data[5];
  int analogValue = analogRead(this->id);
  int originalAnalogValue = analogValue;

  packetId[0] = 'P';
  if(this->id < 10){
    packetId[1] = '0' + this->id;
  } else {
    packetId[1] = 'A' + (this->id-10);
  }

  for(int i = 0; i<5; i++){
    data[4-i] = '0' + analogValue%10;
    analogValue /= 10;
  }
  
  SCMPacket packet(packetId, data);
  packet.write(buffer);
  return originalAnalogValue;
}
