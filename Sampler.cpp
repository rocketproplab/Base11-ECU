#include "Sampler.h"
#include "SCMPacket.h"

using namespace RPL;

Sampler::Sampler():
ptUpdateCount(1){

}

void Sampler::tick(){
  unsigned long currentTime = millis();
  unsigned long wantedTime = ptUpdateCount*Settings::PT_UPDATE_RATE;
  if(currentTime > wantedTime){
    ptUpdateCount++;
    for(int i = 0; i<Settings::PT_PIN_MAP_LEN; i++){
      this->writePTToSerials(i);
    }
  }
}

void Sampler::writePTToSerials(int ptIndex){
  PressureTransducer &pt = this->pts[ptIndex];
  char buffer[RPL::SCM_PACKET_LEN];
  pt.writeValueToBuffer(buffer);
  Settings::FCB_STREAM->write((uint8_t*)buffer, RPL::SCM_PACKET_LEN);
}
