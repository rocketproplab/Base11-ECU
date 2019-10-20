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
  }
  namespace MockConstants {
    const int HIGH = 1;
    const int LOW = 0;
  }
  namespace MockSerial {
    extern Stream Serial;
    extern Stream Serial1;
    extern Stream Serial2;
    extern Stream Serial3;

    void resetSerials();
  }
}

using RPL::Mocks::analogRead;
using RPL::Mocks::digitalWrite;
using RPL::MockConstants::HIGH;
using RPL::MockConstants::LOW;

using RPL::MockSerial::Serial;
using RPL::MockSerial::Serial1;
using RPL::MockSerial::Serial2;
using RPL::MockSerial::Serial3;
