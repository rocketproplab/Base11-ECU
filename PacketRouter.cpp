#include "PacketRouter.h"
#include "Valves.h"
using namespace RPL;

void PacketRouter::onPacket(SCMPacket &packet, Stream &otherSerial){
  if(packet.getId()[0] == 'V'){
    Valves::updateValveState(packet);
    return;
  }

  char packetBuf[RPL::SCM_PACKET_LEN];
  packet.write(packetBuf);
  otherSerial.write((uint8_t*)packetBuf, RPL::SCM_PACKET_LEN);
}

void PacketRouter::onCommandBoxPacket(SCMPacket packet){
  PacketRouter::onPacket(packet, *Settings::FCB_STREAM);
}

void PacketRouter::onFCBPacket(SCMPacket packet){
  PacketRouter::onPacket(packet, *Settings::COMMAND_BOX_STREAM);
}
