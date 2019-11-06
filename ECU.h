#ifndef ECU_H
#define ECU_H
#include "Sensors.h"
#include "SCMParser.h"
#include "PacketRouter.h"

namespace RPL{
class ECU{
  Sensors sensors;
  SCMParser fcbParser;
  SCMParser commandBoxParser;
public:
  ECU();
  void init();
  void tick();
};
}
#endif
