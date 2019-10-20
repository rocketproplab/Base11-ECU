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
      Stream serial;
      PacketRouter::onPacket(packet, serial);
      mu_assert_int_eq(1, Mocks::getDigitalPin(Settings::VALVE_MAP[0]));

      mu_assert_int_eq(0, serial.writeIndex);
    }

    MU_TEST(unknown_packet_is_redirected_to_opposite_stream){
      Mocks::resetPins();
      SCMPacket packet("Z-", "11111");
      Stream serial;
      PacketRouter::onPacket(packet, serial);
      mu_assert_int_eq(0, Mocks::getDigitalPin(Settings::VALVE_MAP[0]));

      char expectedPacket[RPL::SCM_PACKET_LEN+1];
      packet.write(expectedPacket);
      expectedPacket[RPL::SCM_PACKET_LEN] = '\0';
      mu_assert_int_eq(12, serial.writeIndex);
      mu_assert_string_eq(expectedPacket, serial.writeBuffer);
    }

    MU_TEST(unknown_packet_is_redirected_to_fcb_stream_from_cb){
      Mocks::resetPins();
      MockSerial::resetSerials();
      SCMPacket packet("Z-", "11111");
      PacketRouter::onCommandBoxPacket(packet);
      mu_assert_int_eq(0, Mocks::getDigitalPin(Settings::VALVE_MAP[0]));

      char expectedPacket[RPL::SCM_PACKET_LEN+1];
      packet.write(expectedPacket);
      expectedPacket[RPL::SCM_PACKET_LEN] = '\0';
      mu_assert_int_eq(12, Settings::FCB_STREAM->writeIndex);
      mu_assert_string_eq(expectedPacket,
        Settings::FCB_STREAM->writeBuffer);
    }

    MU_TEST(unknown_packet_is_redirected_to_cb_stream_from_fcb){
      Mocks::resetPins();
      MockSerial::resetSerials();
      SCMPacket packet("Z-", "11111");
      PacketRouter::onFCBPacket(packet);
      mu_assert_int_eq(0, Mocks::getDigitalPin(Settings::VALVE_MAP[0]));

      char expectedPacket[RPL::SCM_PACKET_LEN+1];
      packet.write(expectedPacket);
      expectedPacket[RPL::SCM_PACKET_LEN] = '\0';
      mu_assert_int_eq(12, Settings::COMMAND_BOX_STREAM->writeIndex);
      mu_assert_string_eq(expectedPacket,
        Settings::COMMAND_BOX_STREAM->writeBuffer);
    }

    MU_TEST_SUITE(packet_router_test){
      MU_RUN_TEST(valves_toggled_on_valve_state_packet_to_router);
      MU_RUN_TEST(unknown_packet_is_redirected_to_opposite_stream);
      MU_RUN_TEST(unknown_packet_is_redirected_to_fcb_stream_from_cb);
      MU_RUN_TEST(unknown_packet_is_redirected_to_cb_stream_from_fcb);
    }
  }
}
