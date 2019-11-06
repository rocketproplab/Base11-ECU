#include "ECU.h"
using namespace RPL;
ECU ecu;

void setup() {
  ecu.init();
}

void loop() {
  ecu.tick();
}
