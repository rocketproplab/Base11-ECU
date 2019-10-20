#ifndef THERMO_COUPLE_H
#define THERMO_COUPLE_H

#include <Arduino.h>
#include "Adafruit_MAX31855.h"
#include "Settings.h"

namespace RPL{
  class ThermoCouple {
  public:
    ThermoCouple();
    ThermoCouple(int id);
    ThermoCouple(int id, int clkPin);
    ThermoCouple(int id, int clkPin, int csPin, int doPin);
    float writeValueToBuffer(char buffer[]);

    void aquire();
    void resetAccumulator();

  private:
    int id;
    Adafruit_MAX31855 thermoCouple;
    float accumulator;
    int accumulatorCount;

    void writeFloatToBuffer(float toWrite, char buffer[]);
  };
}

#endif
