#include "Stream.h"

using namespace RPL::Mocks;

Stream::Stream() :
writeIndex(0),
readIndex(0),
avaliableCount(0),
rate(0) {

}

void Stream::write(uint8_t data){
  if(this->writeIndex >= STREAM_DATA_LEN){
    return;
  }
  this->writeBuffer[this->writeIndex] = data;
  this->writeIndex++;
  this->writeBuffer[this->writeIndex+1] = '\0';
}

void Stream::write(uint8_t * data, size_t len){
  for(int i = 0; i<len; i++){
    this->write(data[i]);
  }
}

void Stream::setReadableData(const char * data, size_t len){
  this->readIndex = 0;
  for(int i = 0; i<len && i<STREAM_DATA_LEN; i++){
    this->readBuffer[i] = data[i];
  }
  this->avaliableCount = len;
}

uint8_t Stream::read(){
  uint8_t readData = (uint8_t) this->readBuffer[this->readIndex];
  this->readIndex ++;
  this->avaliableCount --;
  return readData;
}

int Stream::available(){
  return this->avaliableCount;
}

void Stream::begin(int rate){
  this->rate = rate;
}

int Stream::getRate(){
  return this->rate;
}

void Stream::reset(){
  this->readIndex = 0;
  this->writeIndex = 0;
  this->avaliableCount = 0;
  this->rate = 0;
}
