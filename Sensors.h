#ifndef SENSORS_H
#define SENSORS_H
#include "PressureTransducer.h"
#include "Settings.h"

namespace RPL{
class Sensors{
public:
  Sensors();
  void tick();

private:
  PressureTransducer pts[Settings::PT_PIN_MAP_LEN];
  unsigned long ptUpdateCount;

  void writePTToSerials(int ptIndex);
};
}

#endif
