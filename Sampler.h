#ifndef SAMPLER_H
#define SAMPLER_H
#include "PressureTransducer.h"
#include "Settings.h"

namespace RPL{

template<typename Sensor, int sensorCount>
class Sampler{
public:
  Sampler(unsigned long updateRate, int oversampleRate,
    const int * sensorMapings):
    updateRate(updateRate),
    updateCount(0),
    sampleRate(oversampleRate),
    sampleCount(0){
    for(int i = 0; i<sensorCount; i++){
      sensors[i] = Sensor(sensorMapings[i]);
    }
  };

  void tick(){
    unsigned long currentTime = millis();
    unsigned long writeTime = (this->updateCount+1)*this->updateRate;
    unsigned long sampleTime = (this->sampleCount+1)*this->updateRate;
    sampleTime /= this->sampleRate;
    sampleTime += (this->updateCount) * this->updateRate;
    
    if(currentTime >= writeTime){
      this->updateCount++;
      this->sampleCount = 0;
      for(int i = 0; i<sensorCount; i++){
        this->writeSensorToSerials(i);
      }
    } else if(currentTime >= sampleTime){
      this->sampleCount ++;
      for(int i = 0; i<sensorCount; i++){
        this->sensors[i].aquire();
      }
    }
  };

private:
  Sensor sensors[sensorCount];
  unsigned long updateRate;
  unsigned long updateCount;
  unsigned long sampleRate;
  unsigned int  sampleCount;

  void writeSensorToSerials(int sensorIndex){
    Sensor &sensor = this->sensors[sensorIndex];
    char buffer[RPL::SCM_PACKET_LEN];
    sensor.aquire();
    sensor.writeValueToBuffer(buffer);
    Settings::FCB_STREAM->write((uint8_t*)buffer, RPL::SCM_PACKET_LEN);
    sensor.resetAccumulator();
  };
};
}

#endif
