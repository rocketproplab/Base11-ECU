#ifndef SETTINGS_H
#define SETTINGS_H
#include "Stream.h"
#include "Arduino.h"

namespace RPL{
  namespace Settings{
    const int VALVE_MAP[] = {0, 1, 10, 3, 4, 5, 6, 7};
    const size_t VALVE_MAP_LEN = sizeof(VALVE_MAP)/sizeof(VALVE_MAP[0]);
    Stream * const FCB_STREAM = &Serial;
    Stream * const COMMAND_BOX_STREAM = &Serial1;
    const int SERIAL_RATE = 115200;

    const int PT_PIN_MAP[] = {0, 1, 2, 3, 4, 5, 6, 7};
    const size_t PT_PIN_MAP_LEN = sizeof(PT_PIN_MAP)/sizeof(PT_PIN_MAP[0]);
    const int PT_UPDATE_RATE = 1000;
    const int PT_OVERSAMPLE_MULTIPLIER = 10;

    const int TC_PIN_MAP[] = {0, 1, 2, 3, 4, 5, 6, 7};
    const size_t TC_PIN_MAP_LEN = sizeof(TC_PIN_MAP)/sizeof(TC_PIN_MAP[0]);
    const int TC_UPDATE_RATE = 2000;
    const int TC_OVERSAMPLE_MULTIPLIER = 5;
    const int TC_DO_PIN = 1;
    const int TC_CLK_PIN = 2;
    const int TC_CS_MAP[] = {0, 1, 2, 3, 4, 5, 6, 7};
  }
}

#endif
