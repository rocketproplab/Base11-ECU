#include "miniunit.h"
#include "PressureTransducer.h"
#include "TEST_HELP_MACROS.h"

namespace RPL {
  namespace PressureTransducerTest{
    MU_TEST(dummy){
      mu_check(false);
    }

    MU_TEST_SUITE(pressure_transducer_test){
      MU_RUN_TEST(dummy);
    }
  }
}
