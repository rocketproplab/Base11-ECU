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
      Valves::updateValveState(packet);
      mu_assert_int_eq(1, Mocks::getDigitalPin(Settings::VALVE_MAP[0]));
      mu_assert_int_eq(1, Mocks::getDigitalPin(Settings::VALVE_MAP[1]));
      mu_assert_int_eq(1, Mocks::getDigitalPin(Settings::VALVE_MAP[2]));
      mu_assert_int_eq(1, Mocks::getDigitalPin(Settings::VALVE_MAP[3]));
      mu_assert_int_eq(1, Mocks::getDigitalPin(Settings::VALVE_MAP[4]));
    }

    MU_TEST(valves_in_block_two_toggled_when_block_two_packet_recived){
      Mocks::resetPins();
      SCMPacket packet("V1", "11111");
      Valves::updateValveState(packet);
      mu_assert_int_eq(0, Mocks::getDigitalPin(Settings::VALVE_MAP[0]));
      mu_assert_int_eq(0, Mocks::getDigitalPin(Settings::VALVE_MAP[1]));
      mu_assert_int_eq(0, Mocks::getDigitalPin(Settings::VALVE_MAP[2]));
      mu_assert_int_eq(0, Mocks::getDigitalPin(Settings::VALVE_MAP[3]));
      mu_assert_int_eq(0, Mocks::getDigitalPin(Settings::VALVE_MAP[4]));

      mu_assert_int_eq(1, Mocks::getDigitalPin(Settings::VALVE_MAP[5]));
      mu_assert_int_eq(1, Mocks::getDigitalPin(Settings::VALVE_MAP[6]));
      mu_assert_int_eq(1, Mocks::getDigitalPin(Settings::VALVE_MAP[7]));
      mu_assert_int_eq(1, Mocks::getDigitalPin(Settings::VALVE_MAP[8]));
      mu_assert_int_eq(1, Mocks::getDigitalPin(Settings::VALVE_MAP[9]));
    }

    MU_TEST_SUITE(valves_test){
      MU_RUN_TEST(valves_in_block_toggled_when_packet_recived);
      MU_RUN_TEST(valves_in_block_two_toggled_when_block_two_packet_recived);
    }
  }
}
