#include "miniunit.h"
#include "PressureTransducerTest.h"

using namespace RPL;

int main(){
  MU_RUN_SUITE(PressureTransducerTest::pressure_transducer_test);
	MU_REPORT();
	return minunit_status;
}
