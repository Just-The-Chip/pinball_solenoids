#include "BasicComponent.h"

BasicComponent::BasicComponent(int _pinIn, int _pinOut, bool _inputRestValue, bool _outputRestValue) {
  pinIn = _pinIn;
  pinOut = _pinOut;
  inputRestValue = _inputRestValue;
  outputRestValue = _outputRestValue;

  pinMode(pinIn, INPUT_PULLUP);
  pinMode(pinOut, OUTPUT);
}

void BasicComponent::update() {
  if(shouldTriggerOutput()) {
    triggerOutput();
  } else {
    untriggerOutput();
  }
}

void BasicComponent::triggerOutput() {
  digitalWrite(pinOut, !outputRestValue);
}

void BasicComponent::untriggerOutput() {
  digitalWrite(pinOut, outputRestValue);
}

bool BasicComponent::shouldTriggerOutput() {
  return inputActivated();
}

bool BasicComponent::inputActivated() {
  bool pinVal = digitalRead(pinIn);
  return inputRestValue == LOW ? pinVal : !pinVal;
}