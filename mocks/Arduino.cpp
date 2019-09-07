#include "Arduino.h"

using namespace RPL;

int analogStates[16]; //16 analog pins

void Mocks::resetPins(){
  for(int i = 0; i<sizeof(analogStates)/sizeof(analogStates[0]); i++){
    analogStates[i] = 0;
  }
}

void Mocks::setAnalogWrite(int pin, int value){
  analogStates[pin] = value;
}

int Mocks::analogRead(int pin){
  return analogStates[pin];
}
