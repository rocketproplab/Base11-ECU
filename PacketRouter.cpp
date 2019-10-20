#include "PacketRouter.h"
#include "Valves.h"
using namespace RPL;

void PacketRouter::onPacket(SCMPacket packet){
  if(packet.getId()[0] == 'V'){
    Valves::updateValveState(packet);
  }
}
