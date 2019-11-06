#pragma once
#include "miniunit.h"
#include "ECU.h"
#include "../mocks/Arduino.h"

namespace RPL {
  namespace ECUTest{
    MU_TEST(init_starts_serial_streams){
      MockSerial::resetSerials();
      ECU ecu;
      ecu.init();
      mu_assert_int_eq(Settings::SERIAL_RATE, Settings::FCB_STREAM->getRate());
      mu_assert_int_eq(Settings::SERIAL_RATE, Settings::COMMAND_BOX_STREAM->getRate());
    }

    MU_TEST(sets_valve_states){
      Mocks::resetPins();
      ECU ecu;
      ecu.init();
      mu_assert_int_eq(OUTPUT, Mocks::getPinmode(Settings::VALVE_MAP[0]));
    }

    MU_TEST_SUITE(ecu_test){
      MU_RUN_TEST(init_starts_serial_streams);
      MU_RUN_TEST(sets_valve_states);
    }
  }
}
