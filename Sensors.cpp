#include "Sensors.h"
#include "SCMPacket.h"

using namespace RPL;

Sensors::Sensors():
ptSampler(Settings::PT_UPDATE_RATE, Settings::PT_OVERSAMPLE_MULTIPLIER,
   Settings::PT_PIN_MAP),
tcSampler(Settings::TC_UPDATE_RATE, Settings::TC_OVERSAMPLE_MULTIPLIER,
   Settings::TC_PIN_MAP){

}

void Sensors::tick(){
  this->ptSampler.tick();
  this->tcSampler.tick();
}
