#include "Arduino.h"

using namespace RPL;

int analogStates[16]; //16 analog pins
int digitalStates[Mocks::DIGITAL_PIN_COUNT];
int pinModeStates[Mocks::DIGITAL_PIN_COUNT];

void Mocks::resetPins(){
  for(int i = 0; i<sizeof(analogStates)/sizeof(analogStates[0]); i++){
    analogStates[i] = 0;
  }
  for(int i = 0; i<DIGITAL_PIN_COUNT; i++){
    digitalStates[i] = 0;
    pinModeStates[i] = MockConstants::NOT_DEFINED;
  }
}

void Mocks::setAnalogWrite(int pin, int value){
  analogStates[pin] = value;
}

int Mocks::analogRead(int pin){
  return analogStates[pin];
}

int Mocks::getDigitalPin(int pin){
  if(pin >=0 && pin < DIGITAL_PIN_COUNT){
    return digitalStates[pin];
  }
  return MockConstants::NOT_DEFINED;
}

void Mocks::digitalWrite(int pin, int value){
  if(pin >=0 && pin < DIGITAL_PIN_COUNT){
    digitalStates[pin] = value;
  }
}

HardwareSerial RPL::MockSerial::Serial;
HardwareSerial RPL::MockSerial::Serial1;
HardwareSerial RPL::MockSerial::Serial2;
HardwareSerial RPL::MockSerial::Serial3;

void MockSerial::resetSerials(){
  Serial.reset();
  Serial1.reset();
  Serial2.reset();
  Serial3.reset();
}

unsigned long millisValue;

unsigned long Mocks::millis(){
  return millisValue;
}

void Mocks::setMillis(unsigned long newValue){
  millisValue = newValue;
}

void Mocks::pinMode(int pin, int value){
  if(pin >=0 && pin < DIGITAL_PIN_COUNT){
    pinModeStates[pin] = value;
  }
}

int Mocks::getPinmode(int pin){
  if(pin >=0 && pin < DIGITAL_PIN_COUNT){
    return pinModeStates[pin];
  }
  return MockConstants::NOT_DEFINED;
}
