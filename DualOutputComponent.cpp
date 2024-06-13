// #include "BasicComponent.h"
#include "DualOutputComponent.h"

DualOutputComponent::DualOutputComponent(int _pinIn, int _pinOut, int _lowPinOut, unsigned long _outputDuration, bool _inputRestValue, bool _outputRestValue, unsigned long _debounceDelay) :
  TimedOutputComponent(_pinIn, _pinOut, _outputDuration, _inputRestValue, _outputRestValue, _debounceDelay) {

  lowPowerPin = _lowPinOut;
}

void DualOutputComponent::triggerOutput() {
  if (!TimeElapsed()) {
    digitalWrite(pinOut, !outputRestValue);
    digitalWrite(lowPowerPin, outputRestValue);
  } else {
    digitalWrite(pinOut, outputRestValue);
    digitalWrite(lowPowerPin, !outputRestValue);
  }
}

bool DualOutputComponent::shouldTriggerOutput() {
  return BasicComponent::shouldTriggerOutput();
}