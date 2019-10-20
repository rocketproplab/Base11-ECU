#include "Valves.h"
#include "Arduino.h"
#include "Settings.h"

using namespace RPL;

void Valves::updateValveState(SCMPacket &packet){
  int offset = packet.getId()[1] - '0';
  offset *= 5;

  for(int i = 0; i<RPL::SCM_PACKET_DATA_LEN; i++){
    int valveIndex = i + offset;
    if(valveIndex >= Settings::VALVE_MAP_LEN){
      break;
    }

    int valvePin = Settings::VALVE_MAP[i + offset];
    if(packet.getData()[i] == '1'){
      digitalWrite(valvePin, HIGH);
    } else {
      digitalWrite(valvePin, LOW);
    }
  }
}
