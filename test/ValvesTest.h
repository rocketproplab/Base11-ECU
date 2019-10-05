#include "miniunit.h"
#include "Valves.h"
#include "TEST_HELP_MACROS.h"
#include "../mocks/Arduino.h"
#include "Settings.h"

namespace RPL {
  namespace ValvesTest{
    MU_TEST(valves_in_block_toggled_when_packet_recived){
      Mocks::resetPins();
      SCMPacket packet("V0", "11111");
      Valves valves;
      valves.updateValveState(packet);
      mu_assert_int_eq(1, Mocks::getDigitalPin(Settings::VALVE_MAP[0]));
      mu_assert_int_eq(1, Mocks::getDigitalPin(Settings::VALVE_MAP[1]));
      mu_assert_int_eq(1, Mocks::getDigitalPin(Settings::VALVE_MAP[2]));
      mu_assert_int_eq(1, Mocks::getDigitalPin(Settings::VALVE_MAP[3]));
      mu_assert_int_eq(1, Mocks::getDigitalPin(Settings::VALVE_MAP[4]));
    }

    MU_TEST_SUITE(valves_test){
      MU_RUN_TEST(valves_in_block_toggled_when_packet_recived);
    }
  }
}
