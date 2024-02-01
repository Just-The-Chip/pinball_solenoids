#include "PopBumper.h"
// #include "TimedOutputComponent.h"

PopBumper::PopBumper(int _pinIn, int _pinOut, unsigned long _outputDuration, bool _inputRestValue, bool _outputRestValue) :
  BasicComponent(_pinIn, _pinOut, _inputRestValue, _outputRestValue) {
    alreadyTriggered = false;
}

void PopBumper::setMessageQueue(MessageQueue* queue) {
  writeQueue = queue;
}

void PopBumper::setComponentID(uint8_t id) {
  component_id = id;
}

void PopBumper::triggerOutput() {
  BasicComponent::triggerOutput();

  if(!alreadyTriggered) {
    alreadyTriggered = true; 
    char message = char(1);
    writeQueue->queueOutgoingMessage(component_id, message);
  }
}

void PopBumper::untriggerOutput() {
  BasicComponent::untriggerOutput();
  alreadyTriggered = false;
}