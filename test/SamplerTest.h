#include "miniunit.h"
#include "TEST_HELP_MACROS.h"
#include "Settings.h"
#include "Sampler.h"
#include "Arduino.h"

namespace RPL {
  namespace SamplerTest{
    MU_TEST(sampler_outputs_pt_values_every_period){
      MockSerial::resetSerials();
      Sampler sampler;
      for(int i = 0; i<Settings::PT_PIN_MAP_LEN; i++){
        int pin = Settings::PT_PIN_MAP[i];
        Mocks::setAnalogWrite(pin, i*10+10);
      }

      Mocks::setMillis(0);
      sampler.tick();
      mu_assert_int_eq(0, Settings::FCB_STREAM->writeIndex);
      Mocks::setMillis(Settings::PT_UPDATE_RATE+1);
      sampler.tick();
      mu_assert_int_eq(12*Settings::PT_PIN_MAP_LEN,
        Settings::FCB_STREAM->writeIndex);
      Settings::FCB_STREAM->writeBuffer[RPL::SCM_PACKET_LEN] = '\0';
      const char* expectedPacket = "P0,00010,57;";
      mu_assert_string_eq(expectedPacket, Settings::FCB_STREAM->writeBuffer);


      MockSerial::resetSerials();
      for(int i = 0; i<Settings::PT_PIN_MAP_LEN; i++){
        int pin = Settings::PT_PIN_MAP[i];
        Mocks::setAnalogWrite(pin, i*10+110);
      }

      Mocks::setMillis(Settings::PT_UPDATE_RATE*3/2);
      sampler.tick();
      mu_assert_int_eq(0, Settings::FCB_STREAM->writeIndex);
      Mocks::setMillis(Settings::PT_UPDATE_RATE*2+1);
      sampler.tick();
      mu_assert_int_eq(12*Settings::PT_PIN_MAP_LEN,
        Settings::FCB_STREAM->writeIndex);
      Settings::FCB_STREAM->writeBuffer[RPL::SCM_PACKET_LEN] = '\0';
      expectedPacket = "P0,00110,58;";
      mu_assert_string_eq(expectedPacket, Settings::FCB_STREAM->writeBuffer);
    }

    MU_TEST_SUITE(sampler_test){
      MU_RUN_TEST(sampler_outputs_pt_values_every_period);
    }
  }
}
