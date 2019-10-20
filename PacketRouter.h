#ifndef PACKET_ROUTER_H
#define PACKET_ROUTER_H
#include "Settings.h"
#include "SCMPacket.h"
#include "Stream.h"
#include "Arduino.h"

namespace RPL{
namespace PacketRouter {
  void onPacket(SCMPacket &packet, Stream &otherSerial);
  void onFCBPacket(SCMPacket packet);
  void onCommandBoxPacket(SCMPacket packet);
};
}


#endif
