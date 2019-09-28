#pragma once
namespace RPL {
  namespace Mocks{
    void setThermoCoupleValue(int cs, float value);
  }
}

class Adafruit_MAX31855 {
public:
  Adafruit_MAX31855(int clk, int cs, int doPin);
  float readInternal();
private:
  int cs;
};
