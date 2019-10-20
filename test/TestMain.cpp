#include "miniunit.h"
#include "PressureTransducerTest.h"
#include "ThermoCoupleTest.h"
#include "ValvesTest.h"
#include "PacketRouterTest.h"
#include "SamplerTest.h"

using namespace RPL;

int main(){
  MU_RUN_SUITE(PressureTransducerTest::pressure_transducer_test);
  MU_RUN_SUITE(ThermoCoupleTest::thermo_couple_test);
  MU_RUN_SUITE(ValvesTest::valves_test);
  MU_RUN_SUITE(PacketRouterTest::packet_router_test);
  MU_RUN_SUITE(SamplerTest::sampler_test);
	MU_REPORT();
	return minunit_status;
}
