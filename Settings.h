#ifndef SETTINGS_H
#define SETTINGS_H
#include "Stream.h"
#include "Arduino.h"

namespace RPL{
  namespace Settings{
    const int VALVE_MAP[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    Stream * const FCB_STREAM = &Serial;
    Stream * const COMMAND_BOX_STREAM = &Serial1;
  }
}

#endif
