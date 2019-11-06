#include "ECU.h"
#include "Settings.h"
#include "PacketRouter.h"

using namespace RPL;

ECU::ECU() :
fcbParser([] {return Settings::FCB_STREAM->avaliable();},
  [] {return (char)Settings::FCB_STREAM->read();},
  PacketRouter::onFCBPacket),
commandBoxParser([] {return Settings::COMMAND_BOX_STREAM->avaliable();},
  [] {return (char)Settings::COMMAND_BOX_STREAM->read();},
  PacketRouter::onCommandBoxPacket){

}

void ECU::init(){
  Settings::FCB_STREAM->begin(Settings::SERIAL_RATE);
  Settings::COMMAND_BOX_STREAM->begin(Settings::SERIAL_RATE);
}

void ECU::tick(){
  this->sensors.tick();
  this->commandBoxParser.read();
  this->fcbParser.read();
}
