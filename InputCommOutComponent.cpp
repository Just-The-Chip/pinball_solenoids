#include "Arduino.h"
#include "InputCommOutComponent.h"
#include "Interfaces.h"

InputCommOutComponent::InputCommOutComponent(int _pinIn, bool _inputRestValue, unsigned long _debounceDelay) {
  pinIn = _pinIn;
  inputRestValue = _inputRestValue;
  debounceDelay = _debounceDelay;

  lastInputState = inputRestValue;
  currentInputState = inputRestValue;
  debounceTime = 0;
  alreadyTriggered = false;

  pinMode(pinIn, INPUT_PULLUP);
}

void InputCommOutComponent::setMessageQueue(MessageQueue* queue) {
  writeQueue = queue;
}

void InputCommOutComponent::setComponentID(uint8_t id) {
  component_id = id;
}

void InputCommOutComponent::update() {
  if(shouldTriggerComm()) {
    triggerComm();
  } else {
    untriggerComm();
  }
}

void InputCommOutComponent::triggerComm() {
  if(!alreadyTriggered) {
    alreadyTriggered = true; 
    char message = char(1);
    writeQueue->queueOutgoingMessage(component_id, message);
  }
}

void InputCommOutComponent::untriggerComm() {
  alreadyTriggered = false;
}

bool InputCommOutComponent::shouldTriggerComm() {
  return inputActivated();
}

bool InputCommOutComponent::inputActivated() {
  bool pinVal = debouncedInputRead();
  return inputRestValue == LOW ? pinVal : !pinVal;
}

bool InputCommOutComponent::debouncedInputRead() {
  bool pinVal = digitalRead(pinIn);

  if (pinVal != lastInputState) {
    debounceTime = millis();
    lastInputState = pinVal;
  }

  if (currentInputState != pinVal && (millis() - debounceTime) >= debounceDelay) {
    currentInputState = pinVal;
  }

  return currentInputState;
}