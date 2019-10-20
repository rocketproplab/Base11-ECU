#ifndef PACKET_ROUTER_H
#define PACKET_ROUTER_H
#include "SCMPacket.h"

namespace RPL{
namespace PacketRouter {
  void onPacket(SCMPacket packet);
}
}

#endif
