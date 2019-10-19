#include "Valves.h"
#include "Arduino.h"

using namespace RPL;

void Valves::updateValveState(SCMPacket &packet){
  int offset = packet.getId()[1] - '0';
  offset *= 5;
  for(int i = 0; i<RPL::SCM_PACKET_DATA_LEN; i++){
    if(packet.getData()[i] == '1'){
      digitalWrite(i + offset, HIGH);
    }
  }
}
