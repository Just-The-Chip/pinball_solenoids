// #include "BasicComponent.h"
#include "DualOutputComponent.h"

DualOutputComponent::DualOutputComponent(int _pinIn, int _pinOut, int _lowPinOut, unsigned long _outputDuration, bool _inputRestValue, bool _outputRestValue, unsigned long _debounceDelay) :
  TimedOutputComponent(_pinIn, _pinOut, _outputDuration, _inputRestValue, _outputRestValue, _debounceDelay) {
  
  outputDuration = _outputDuration;
  lowPowerPin = _lowPinOut;
  pinMode(lowPowerPin, OUTPUT);
}

void DualOutputComponent::triggerOutput() { 
  if (TimeElapsed()) {
    digitalWrite(pinOut, !outputRestValue);
    digitalWrite(lowPowerPin, outputRestValue);
  } else {
    digitalWrite(pinOut, outputRestValue);
    digitalWrite(lowPowerPin, !outputRestValue);
  }
}

void DualOutputComponent::untriggerOutput() {
  digitalWrite(lowPowerPin, outputRestValue);
  TimedOutputComponent::untriggerOutput();
}

bool DualOutputComponent::shouldTriggerOutput() {
  return BasicComponent::shouldTriggerOutput();
}