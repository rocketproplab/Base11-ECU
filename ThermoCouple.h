#ifndef THERMO_COUPLE_H
#define THERMO_COUPLE_H

#include <Arduino.h>
#include "Adafruit_MAX31855.h"

namespace RPL{
  class ThermoCouple {
  public:
    ThermoCouple(int id, int clkPin, int csPin, int doPin);
    float writeValueToBuffer(char buffer[]);

  private:
    int id;
    Adafruit_MAX31855 thermoCouple;

    void writeFloatToBuffer(float toWrite, char buffer[]);
  };
}

#endif
