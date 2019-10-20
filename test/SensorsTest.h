#include "miniunit.h"
#include "TEST_HELP_MACROS.h"
#include "Settings.h"
#include "Sensors.h"
#include "Arduino.h"

namespace RPL {
  namespace SensorsTest{
    void setAnalogs(int start){
      for(int i = 0; i<Settings::PT_PIN_MAP_LEN; i++){
        int pin = Settings::PT_PIN_MAP[i];
        Mocks::setAnalogWrite(pin, i*10+start);
      }
    }

    MU_TEST(sensors_outputs_pt_values_every_period){
      MockSerial::resetSerials();
      Sensors sensors;
      setAnalogs(10);

      Mocks::setMillis(0);
      sensors.tick();
      mu_assert_int_eq(0, Settings::FCB_STREAM->writeIndex);
      Mocks::setMillis(Settings::PT_UPDATE_RATE+1);
      sensors.tick();
      mu_assert_int_eq(12*Settings::PT_PIN_MAP_LEN,
        Settings::FCB_STREAM->writeIndex);
      Settings::FCB_STREAM->writeBuffer[RPL::SCM_PACKET_LEN] = '\0';
      const char* expectedPacket = "P0,00010,57;";
      mu_assert_string_eq(expectedPacket, Settings::FCB_STREAM->writeBuffer);


      MockSerial::resetSerials();
      setAnalogs(110);

      Mocks::setMillis(Settings::PT_UPDATE_RATE*3/2);
      sensors.tick();
      mu_assert_int_eq(0, Settings::FCB_STREAM->writeIndex);
      Mocks::setMillis(Settings::PT_UPDATE_RATE*2+1);
      sensors.tick();
      mu_assert_int_eq(12*(Settings::PT_PIN_MAP_LEN+Settings::TC_PIN_MAP_LEN),
        Settings::FCB_STREAM->writeIndex);
      Settings::FCB_STREAM->writeBuffer[RPL::SCM_PACKET_LEN] = '\0';
      expectedPacket = "P0,00110,58;";
      mu_assert_string_eq(expectedPacket, Settings::FCB_STREAM->writeBuffer);
    }

    MU_TEST(sensor_samples_tcs){
      Sensors sensors;
      Mocks::setMillis(Settings::TC_UPDATE_RATE*2-1);
      sensors.tick();
      MockSerial::resetSerials();
      mu_assert_int_eq(0, Settings::FCB_STREAM->writeIndex);
      Mocks::setMillis(Settings::TC_UPDATE_RATE*2+1);
      sensors.tick();
      mu_assert_int_eq(12*(Settings::PT_PIN_MAP_LEN+Settings::TC_PIN_MAP_LEN),
        Settings::FCB_STREAM->writeIndex);
    }

    MU_TEST_SUITE(sensors_test){
      MU_RUN_TEST(sensors_outputs_pt_values_every_period);
      MU_RUN_TEST(sensor_samples_tcs);
    }
  }
}
