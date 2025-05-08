#include "OutputCommTimeInComponent.h"

OutputCommTimeInComponent::OutputCommTimeInComponent(int _pinOut, bool _outputRestValue) :
  OutputCommInComponent(_pinOut, 0, _outputRestValue){
}

void OutputCommTimeInComponent::handleMessage(uint8_t id, unsigned char content) {
  OutputCommInComponent::handleMessage(id, content);
  // max message value is 255 and we can't use 10, 
  // so python sends value in tenths of a second (+1 if it's >= 10)
  // resolution = 100 milliseconds to 25.4 seconds
  unsigned int tenthsOfSecond = content > 10 ? content - 1 : content;
  outputDuration = tenthsOfSecond * 100;
}