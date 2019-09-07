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
      mu_assert_int_eq(pt.writeValueToBuffer(buf), 10);
      Mocks::setAnalogWrite(0, 1000);
      mu_assert_int_eq(pt.writeValueToBuffer(buf), 1000);
    }

    MU_TEST_SUITE(pressure_transducer_test){
      MU_RUN_TEST(pt_reads_value_via_analog_read);
    }
  }
}
