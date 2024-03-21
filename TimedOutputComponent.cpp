// #include "BasicComponent.h"
#include "TimedOutputComponent.h"

TimedOutputComponent::TimedOutputComponent(int _pinIn, int _pinOut, unsigned long _outputDuration, bool _inputRestValue, bool _outputRestValue, unsigned long _debounceDelay) :
  BasicComponent(_pinIn, _pinOut, _inputRestValue, _outputRestValue, _debounceDelay) {

  outputDuration = _outputDuration;
  outputOnTime = 0;
  lastUpdateTime = 0;
}

void TimedOutputComponent::update() {
  lastUpdateTime = millis();

  if(inputActivated()) {
    outputOnTime = lastUpdateTime;
  }

  BasicComponent::update();
}

bool TimedOutputComponent::shouldTriggerOutput() {
  return outputDuration >= lastUpdateTime - outputOnTime;
}