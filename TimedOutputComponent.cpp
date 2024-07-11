// #include "BasicComponent.h"
#include "TimedOutputComponent.h"

TimedOutputComponent::TimedOutputComponent(int _pinIn, int _pinOut, unsigned long _outputDuration, bool _inputRestValue, bool _outputRestValue, unsigned long _debounceDelay) :
  OutputComponent(_pinIn, _pinOut, _inputRestValue, _outputRestValue, _debounceDelay) {

  outputDuration = _outputDuration;
  outputOnTime = 0;
  lastUpdateTime = 0;
}

void TimedOutputComponent::update() {
  lastUpdateTime = millis();

  if(inputActivated() && !timeSet) {
    outputOnTime = lastUpdateTime;
    timeSet = true;
  }

  BasicComponent::update();
}

bool TimedOutputComponent::shouldTriggerOutput() {
  Serial.println(TimeElapsed());
  return TimeElapsed();
}

bool TimedOutputComponent::TimeElapsed() {
  
  return outputDuration >= lastUpdateTime - outputOnTime;
}

// this is for overriding
// void TimedOutputComponent::resetLatch() {
//   if(TimeElapsed()) timeSet = false;
// }

void TimedOutputComponent::untriggerOutput() {
  timeSet = false;
  BasicComponent::untriggerOutput();
}