#include "PressureTransducer.h"

using namespace RPL;

PressureTransducer::PressureTransducer(int id){

}

int PressureTransducer::writeValueToBuffer(const char buffer[]){
  return analogRead(0);
}
