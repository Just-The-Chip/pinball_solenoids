#include "Arduino.h"
#include "OutputCommInComponent.h"

OutputCommInComponent::OutputCommInComponent(int _pinOut, unsigned long _outputDuration, bool _outputRestValue) {
  pinOut = _pinOut;
  outputRestValue = _outputRestValue;
  outputDuration = _outputDuration;
  outputOnTime = 0;
  lastUpdateTime = 0;
  messageReceived = false;

  pinMode(pinOut, OUTPUT);
}

void OutputCommInComponent::handleMessage(uint8_t id, unsigned char content) {
  messageReceived = true;
}

void OutputCommInComponent::update() {
  lastUpdateTime = millis();

  if(messageReceived) {
    outputOnTime = lastUpdateTime;
    messageReceived = false;
  }

  if(shouldTriggerOutput()) {
    triggerOutput();
  } else {
    untriggerOutput();
  }
}

bool OutputCommInComponent::shouldTriggerOutput() {
  // Serial.println(TimeElapsed());
  return !timeElapsed();
}

bool OutputCommInComponent::timeElapsed() {
  // Serial.print(lastUpdateTime);
  // Serial.print(' ');
  // Serial.println(outputOnTime);
  return outputDuration <= lastUpdateTime - outputOnTime;
}

void OutputCommInComponent::triggerOutput() {
  digitalWrite(pinOut, !outputRestValue);
}

void OutputCommInComponent::untriggerOutput() {
  digitalWrite(pinOut, outputRestValue);
}