#pragma once
#include <memory>

namespace RPL{
namespace Mocks {
  const int STREAM_DATA_LEN = 200;
class Stream{
public:
  Stream();
  void write(uint8_t);
  void write(uint8_t*, size_t);
  uint8_t read();
  int avaliable();

  void setReadableData(const char * data, size_t len);
  void reset();

  char writeBuffer[STREAM_DATA_LEN];
  char readBuffer[STREAM_DATA_LEN];
  int readIndex;
  int writeIndex;
  int avaliableCount;
};
}
}


using RPL::Mocks::Stream;
