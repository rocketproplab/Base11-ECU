#pragma once
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
