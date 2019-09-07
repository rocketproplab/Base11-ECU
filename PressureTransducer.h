#ifndef PRESSURE_TRANSDUCER_H
#define PRESSURE_TRANSDUCER_H

#include <Arduino.h>

namespace RPL{
  class PressureTransducer {
  public:
    PressureTransducer(int id);
    int writeValueToBuffer(char buffer[]);

  private:
    int id;
  };
}

#endif
