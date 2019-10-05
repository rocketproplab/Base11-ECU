#pragma once
#include "MemTypes.h"

namespace RPL {
  namespace Mocks {
    void resetPins();
    void setAnalogWrite(int pin, int value);
    int analogRead(int pin);
    int getDigitalPin(int pin);
  }
}

using RPL::Mocks::analogRead;
