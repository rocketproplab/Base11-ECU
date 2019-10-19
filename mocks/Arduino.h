#pragma once
#include "MemTypes.h"

namespace RPL {
  namespace Mocks {
    void resetPins();
    void setAnalogWrite(int pin, int value);
    int analogRead(int pin);
    int getDigitalPin(int pin);
    void digitalWrite(int pin, int value);
  }
  namespace MockConstants {
    const int HIGH = 1;
  }
}

using RPL::Mocks::analogRead;
using RPL::Mocks::digitalWrite;
using RPL::MockConstants::HIGH;
