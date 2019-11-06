#pragma once
#include <memory>

namespace RPL{
namespace Mocks {
  const int STREAM_DATA_LEN = 200;
class Stream{
public:
  Stream();
  virtual void write(uint8_t);
  void write(uint8_t*, size_t);
  virtual uint8_t read();
  virtual int available();
  void begin(int rate);

  void setReadableData(const char * data, size_t len);
  void reset();

  int getRate();

  char writeBuffer[STREAM_DATA_LEN];
  char readBuffer[STREAM_DATA_LEN];
  int readIndex;
  int writeIndex;
  int avaliableCount;
  int rate;
};
class HardwareSerial : public Stream{

};
}
}


using RPL::Mocks::Stream;
using RPL::Mocks::HardwareSerial;
