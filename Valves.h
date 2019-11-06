#ifndef VAVLES_H
#define VALVES_H

#include <SCMPacket.h>

namespace RPL{
namespace Valves{
  void updateValveState(SCMPacket &packet);
  void initPinModes();
}
}

#endif
