#include "miniunit.h"
#include "PressureTransducer.h"
#include "TEST_HELP_MACROS.h"
#include "../mocks/Arduino.h"

namespace RPL {
  namespace PressureTransducerTest{
    MU_TEST(pt_reads_value_via_analog_read){
      Mocks::resetPins();
      char buf[20];
      PressureTransducer pt(0);
      Mocks::setAnalogWrite(0, 10);
      pt.aquire();
      mu_assert_int_eq(10, pt.writeValueToBuffer(buf));
      Mocks::setAnalogWrite(0, 1000);
      pt.resetAccumulator();
      pt.aquire();
      mu_assert_int_eq(1000, pt.writeValueToBuffer(buf));
    }

    MU_TEST(pt_discriminates_differnt_pins){
      Mocks::resetPins();
      char buf[20];
      PressureTransducer pt0(0);
      PressureTransducer pt1(1);
      Mocks::setAnalogWrite(0, 10);
      Mocks::setAnalogWrite(1, 11);
      pt0.aquire();
      pt1.aquire();
      mu_assert_int_eq(10, pt0.writeValueToBuffer(buf));
      mu_assert_int_eq(11, pt1.writeValueToBuffer(buf));
    }

    MU_TEST(pt_writes_accurate_packet_for_id_zero){
      Mocks::resetPins();
      char buf[20];
      ZERO_MEM(buf);
      const char * expectedPacket = "P0,00010,57;";
      PressureTransducer pt(0);
      Mocks::setAnalogWrite(0, 10);
      pt.aquire();
      mu_assert_int_eq(10, pt.writeValueToBuffer(buf));
      mu_assert_string_eq(expectedPacket, buf);
    }

    MU_TEST(pt_writes_accurate_packet_for_id_one){
      Mocks::resetPins();
      char buf[20];
      ZERO_MEM(buf);
      const char * expectedPacket = "P1,00011,59;";
      PressureTransducer pt(1);
      Mocks::setAnalogWrite(1, 11);
      pt.aquire();
      mu_assert_int_eq(11, pt.writeValueToBuffer(buf));
      mu_assert_string_eq(expectedPacket, buf);
    }

    MU_TEST(pt_writes_accurate_packet_for_id_eleven){
      Mocks::resetPins();
      char buf[20];
      ZERO_MEM(buf);
      const char * expectedPacket = "PB,01023,80;";
      PressureTransducer pt(11);
      Mocks::setAnalogWrite(11, 1023);
      pt.aquire();
      mu_assert_int_eq(1023, pt.writeValueToBuffer(buf));
      mu_assert_string_eq(expectedPacket, buf);
    }

    MU_TEST(pt_reports_const_value_when_aquire_same_twice){
      Mocks::resetPins();
      char buf[20];
      PressureTransducer pt(0);
      Mocks::setAnalogWrite(0, 10);
      pt.aquire();
      pt.aquire();
      mu_assert_int_eq(10, pt.writeValueToBuffer(buf));
    }

    MU_TEST(pt_reports_average_value_when_aquire_differing){
      Mocks::resetPins();
      char buf[20];
      PressureTransducer pt(0);
      Mocks::setAnalogWrite(0, 10);
      pt.aquire();
      Mocks::setAnalogWrite(0, 100);
      pt.aquire();
      mu_assert_int_eq(55, pt.writeValueToBuffer(buf));
    }

    MU_TEST(pt_reports_zero_with_no_aquires){
      Mocks::resetPins();
      char buf[20];
      PressureTransducer pt(0);
      Mocks::setAnalogWrite(0, 10);
      mu_assert_int_eq(0, pt.writeValueToBuffer(buf));
    }

    MU_TEST_SUITE(pressure_transducer_test){
      MU_RUN_TEST(pt_reads_value_via_analog_read);
      MU_RUN_TEST(pt_discriminates_differnt_pins);
      MU_RUN_TEST(pt_writes_accurate_packet_for_id_zero);
      MU_RUN_TEST(pt_writes_accurate_packet_for_id_one);
      MU_RUN_TEST(pt_writes_accurate_packet_for_id_eleven);
      MU_RUN_TEST(pt_reports_const_value_when_aquire_same_twice);
      MU_RUN_TEST(pt_reports_average_value_when_aquire_differing);
      MU_RUN_TEST(pt_reports_zero_with_no_aquires);
    }
  }
}
