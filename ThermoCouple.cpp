#include "ThermoCouple.h"
#include "SCMPacket.h"

using namespace RPL;

ThermoCouple::ThermoCouple(int id, int clkPin, int csPin, int doPin) :
  id(id),
  thermoCouple(clkPin, csPin, doPin) {

}

float ThermoCouple::writeValueToBuffer(char buffer[]){
  char packetId[2];
  char data[5];

  packetId[0] = 'T';
  if(this->id < 10){
    packetId[1] = '0' + this->id;
  } else {
    packetId[1] = 'A' + (this->id-10);
  }

  float temperature = this->thermoCouple.readInternal();
  this->writeFloatToBuffer(temperature, data);

  SCMPacket packet(packetId, data);
  packet.write(buffer);
  return temperature;
}

void ThermoCouple::writeFloatToBuffer(float toWrite, char buffer[]){
  int decimalLeftShifts = 0;
  int maxValue = 10000;
  for(decimalLeftShifts = 0; decimalLeftShifts<5; decimalLeftShifts++){
    if(toWrite >= (maxValue - 0.5 / (10000 / maxValue))){
      break;
    }
    maxValue /= 10;
  }

  int scaleFactor = 1;
  for(int i = 0; i<decimalLeftShifts-1; i++){
    scaleFactor *= 10;
  }

  float fixedPointFloat = toWrite * scaleFactor;
  int fixedPointInt = fixedPointFloat;
  if(fixedPointFloat - fixedPointInt > 0.5){
    fixedPointInt ++;
  }

  for(int i = 0; i<5; i++){
    if(i == (decimalLeftShifts-1)){
      buffer[4-i] = '.';
      continue;
    }
    buffer[4-i] = '0' + fixedPointInt%10;
    fixedPointInt /= 10;
  }
}
