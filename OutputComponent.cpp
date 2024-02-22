#include "OutputComponent.h"
// #include "TimedOutputComponent.h"

OutputComponent::OutputComponent(int _pinIn, int _pinOut, bool _inputRestValue, bool _outputRestValue, unsigned long _debounceDelay) :
  BasicComponent(_pinIn, _pinOut, _inputRestValue, _outputRestValue, _debounceDelay) {
    alreadyTriggered = false;
}

void OutputComponent::setMessageQueue(MessageQueue* queue) {
  writeQueue = queue;
}

void OutputComponent::setComponentID(uint8_t id) {
  component_id = id;
}

void OutputComponent::triggerOutput() {
  BasicComponent::triggerOutput();

  if(!alreadyTriggered) {
    alreadyTriggered = true; 
    char message = char(1);
    writeQueue->queueOutgoingMessage(component_id, message);
  }
}

void OutputComponent::untriggerOutput() {
  BasicComponent::untriggerOutput();
  alreadyTriggered = false;
}