#pragma once
#include "miniunit.h"
#include "PacketRouter.h"
#include "TEST_HELP_MACROS.h"
#include "../mocks/Arduino.h"
#include "Settings.h"

namespace RPL {
  namespace PacketRouterTest{
    MU_TEST(valves_toggled_on_valve_state_packet_to_router){
      Mocks::resetPins();
      SCMPacket packet("V0", "11111");
      PacketRouter::onPacket(packet);
      mu_assert_int_eq(1, Mocks::getDigitalPin(Settings::VALVE_MAP[0]));
      mu_assert_int_eq(1, Mocks::getDigitalPin(Settings::VALVE_MAP[1]));
      mu_assert_int_eq(1, Mocks::getDigitalPin(Settings::VALVE_MAP[2]));
      mu_assert_int_eq(1, Mocks::getDigitalPin(Settings::VALVE_MAP[3]));
      mu_assert_int_eq(1, Mocks::getDigitalPin(Settings::VALVE_MAP[4]));
    }

    MU_TEST_SUITE(packet_router_test){
      MU_RUN_TEST(valves_toggled_on_valve_state_packet_to_router);
    }
  }
}
