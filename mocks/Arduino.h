#pragma once
#include "MemTypes.h"
#include "Stream.h"

namespace RPL {
  namespace Mocks {
    void resetPins();
    void setAnalogWrite(int pin, int value);
    int analogRead(int pin);
    int getDigitalPin(int pin);
    void digitalWrite(int pin, int value);
    const int DIGITAL_PIN_COUNT = 52;

    unsigned long millis();
    void setMillis(unsigned long);

    int getPinmode(int pin);
    void pinMode(int pin, int direction);
  }
  namespace MockConstants {
    const int HIGH = 1;
    const int LOW = 0;
    const int OUTPUT = 1;
    const int INPUT = 0;
    const int NOT_DEFINED = -1;
  }
  namespace MockSerial {
    extern HardwareSerial Serial;
    extern HardwareSerial Serial1;
    extern HardwareSerial Serial2;
    extern HardwareSerial Serial3;

    void resetSerials();
  }
}

using RPL::Mocks::analogRead;
using RPL::Mocks::digitalWrite;
using RPL::Mocks::millis;
using RPL::Mocks::pinMode;
using RPL::MockConstants::HIGH;
using RPL::MockConstants::LOW;
using RPL::MockConstants::OUTPUT;
using RPL::MockConstants::INPUT;

using RPL::MockSerial::Serial;
using RPL::MockSerial::Serial1;
using RPL::MockSerial::Serial2;
using RPL::MockSerial::Serial3;
