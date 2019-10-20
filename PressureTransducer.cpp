#include "PressureTransducer.h"
#include <SCMPacket.h>

using namespace RPL;

PressureTransducer::PressureTransducer(int id) :
id(id),
sum(0),
accumulatorCount(0){

}

int PressureTransducer::writeValueToBuffer(char buffer[]){
  char packetId[2];
  char data[5];
  int analogValue = 0;
  if(this->accumulatorCount != 0){
    analogValue = this->sum/this->accumulatorCount;
  }
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

void PressureTransducer::aquire(){
  this->sum += analogRead(this->id);
  this->accumulatorCount ++;
}

void PressureTransducer::resetAccumulator(){
  this->sum = 0;
  this->accumulatorCount = 0;
}
