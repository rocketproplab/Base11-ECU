#include "Arduino.h"

using namespace RPL;

int analogStates[16]; //16 analog pins
int digitalStates[52];

void Mocks::resetPins(){
  for(int i = 0; i<sizeof(analogStates)/sizeof(analogStates[0]); i++){
    analogStates[i] = 0;
  }
  for(int i = 0; i<sizeof(digitalStates)/sizeof(digitalStates[0]); i++){
    digitalStates[i] = 0;
  }
}

void Mocks::setAnalogWrite(int pin, int value){
  analogStates[pin] = value;
}

int Mocks::analogRead(int pin){
  return analogStates[pin];
}

int Mocks::getDigitalPin(int pin){
  if(pin >=0 && pin < (sizeof(digitalStates)/sizeof(digitalStates[0]))){
    return digitalStates[pin];
  }
  return -1;
}

void Mocks::digitalWrite(int pin, int value){
  if(pin >=0 && pin < (sizeof(digitalStates)/sizeof(digitalStates[0]))){
    digitalStates[pin] = value;
  }
}

Stream RPL::MockSerial::Serial;
Stream RPL::MockSerial::Serial1;
Stream RPL::MockSerial::Serial2;
Stream RPL::MockSerial::Serial3;

void MockSerial::resetSerials(){
  Serial.reset();
  Serial1.reset();
  Serial2.reset();
  Serial3.reset();
}
