#include "Adafruit_MAX31855.h"

using namespace RPL;

float csMap[100];

void Mocks::setThermoCoupleValue(int cs, float value){
  if(cs >= 0 && cs < sizeof(csMap)/sizeof(csMap[0])){
    csMap[cs] = value;
  }
}

Adafruit_MAX31855::Adafruit_MAX31855(int clk, int cs, int doPin):
  cs(cs){

}

float Adafruit_MAX31855::readInternal(){
  if(this->cs >= 0 && this->cs < sizeof(csMap)/sizeof(csMap[0])){
    return csMap[this->cs];
  }
  return 0/0.0;
}
