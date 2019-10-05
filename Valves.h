#ifndef VAVLES_H
#define VALVES_H

#include <SCMPacket.h>

namespace RPL{
class Valves{
public:
  void updateValveState(SCMPacket &packet);
};
}

#endif
