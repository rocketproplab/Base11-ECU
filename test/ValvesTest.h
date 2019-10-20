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
      mu_assert_int_eq(HIGH, Mocks::getDigitalPin(Settings::VALVE_MAP[0]));
      mu_assert_int_eq(HIGH, Mocks::getDigitalPin(Settings::VALVE_MAP[1]));
      mu_assert_int_eq(HIGH, Mocks::getDigitalPin(Settings::VALVE_MAP[2]));
      mu_assert_int_eq(HIGH, Mocks::getDigitalPin(Settings::VALVE_MAP[3]));
      mu_assert_int_eq(HIGH, Mocks::getDigitalPin(Settings::VALVE_MAP[4]));
    }

    MU_TEST(valves_in_block_two_toggled_when_block_two_packet_recived){
      Mocks::resetPins();
      SCMPacket packet("V1", "11111");
      Valves::updateValveState(packet);
      for(int i = 0; i<Mocks::DIGITAL_PIN_COUNT; i++){
        int v5 = Settings::VALVE_MAP[5];
        int v6 = Settings::VALVE_MAP[6];
        int v7 = Settings::VALVE_MAP[7];
        if(i == v5 || i == v6 || i == v7){
          continue;
        }
        mu_assert_int_eq(LOW, Mocks::getDigitalPin(i));
      }

      mu_assert_int_eq(HIGH, Mocks::getDigitalPin(Settings::VALVE_MAP[5]));
      mu_assert_int_eq(HIGH, Mocks::getDigitalPin(Settings::VALVE_MAP[6]));
      mu_assert_int_eq(HIGH, Mocks::getDigitalPin(Settings::VALVE_MAP[7]));
    }

    MU_TEST(valves_are_not_badly_toggled_off){
      for(int i = 0; i<Mocks::DIGITAL_PIN_COUNT; i++){
        digitalWrite(i, HIGH);
      }
      SCMPacket packet("V1", "00011");
      Valves::updateValveState(packet);
      for(int i = 0; i<Mocks::DIGITAL_PIN_COUNT; i++){
        int v5 = Settings::VALVE_MAP[5];
        int v6 = Settings::VALVE_MAP[6];
        int v7 = Settings::VALVE_MAP[7];
        if(i == v5 || i == v6 || i == v7){
          continue;
        }
        mu_assert_int_eq(HIGH, Mocks::getDigitalPin(i));
      }

      mu_assert_int_eq(LOW, Mocks::getDigitalPin(Settings::VALVE_MAP[5]));
      mu_assert_int_eq(LOW, Mocks::getDigitalPin(Settings::VALVE_MAP[6]));
      mu_assert_int_eq(LOW, Mocks::getDigitalPin(Settings::VALVE_MAP[7]));
    }

    MU_TEST(valves_in_block_toggled_off_when_packet_recived){
      Mocks::resetPins();
      SCMPacket packet("V0", "11111");
      Valves::updateValveState(packet);
      SCMPacket packet2("V0", "11011");
      Valves::updateValveState(packet2);
      mu_assert_int_eq(HIGH, Mocks::getDigitalPin(Settings::VALVE_MAP[0]));
      mu_assert_int_eq(HIGH, Mocks::getDigitalPin(Settings::VALVE_MAP[1]));
      mu_assert_int_eq(LOW, Mocks::getDigitalPin(Settings::VALVE_MAP[2]));
      mu_assert_int_eq(HIGH, Mocks::getDigitalPin(Settings::VALVE_MAP[3]));
      mu_assert_int_eq(HIGH, Mocks::getDigitalPin(Settings::VALVE_MAP[4]));
    }

    MU_TEST_SUITE(valves_test){
      MU_RUN_TEST(valves_in_block_toggled_when_packet_recived);
      MU_RUN_TEST(valves_in_block_two_toggled_when_block_two_packet_recived);
      MU_RUN_TEST(valves_in_block_toggled_off_when_packet_recived);
      MU_RUN_TEST(valves_are_not_badly_toggled_off);
    }
  }
}
