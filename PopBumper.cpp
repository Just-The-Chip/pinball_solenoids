#include "PopBumper.h"
// #include "TimedOutputComponent.h"

PopBumper::PopBumper(int _pinIn, int _pinOut, unsigned long _outputDuration, bool _inputRestValue, bool _outputRestValue) :
  TimedOutputComponent(_pinIn, _pinOut, _outputDuration, _inputRestValue, _outputRestValue) {
}

void PopBumper::setMessageQueue(MessageQueue* queue) {
  writeQueue = queue;
}

void PopBumper::setComponentID(uint8_t id) {
  component_id = id;
}

void PopBumper::triggerOutput() {
  TimedOutputComponent::triggerOutput();

  char message = char(1);
  writeQueue->queueOutgoingMessage(component_id, message);
}