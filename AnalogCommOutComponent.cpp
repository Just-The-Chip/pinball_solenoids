#include "Arduino.h"
#include "AnalogCommOutComponent.h"
#include "Interfaces.h"

AnalogCommOutComponent::AnalogCommOutComponent(int _pinIn, unsigned int _minValue, unsigned int _maxValue, unsigned long _readInterval) {
  pinIn = _pinIn;
  minValue = _minValue;
  maxValue = _maxValue;
  readInterval = _readInterval;

  lastReadTime = 0;
}

void AnalogCommOutComponent::setMessageQueue(MessageQueue* queue) {
  writeQueue = queue;
}

void AnalogCommOutComponent::setComponentID(uint8_t id) {
  component_id = id;
}

void AnalogCommOutComponent::update() {
  unsigned long now = millis();

  if(now - lastReadTime < readInterval) {
    return;
  }

  lastReadTime = now;
  unsigned char currentValue = scaledInputRead();

  if(shouldTriggerComm(currentValue)) {
    triggerComm(currentValue);
  }
}

void AnalogCommOutComponent::triggerComm(unsigned char value) {
  // add 100 to the value in case the base value is 10 which is not allowed
  writeQueue->queueOutgoingMessage(component_id, value + 100);
}

bool AnalogCommOutComponent::shouldTriggerComm(unsigned char value) {
  return value > 0;
}

unsigned char AnalogCommOutComponent::scaledInputRead() {
  unsigned int pinVal = analogRead(pinIn);

  // if(pinVal > minValue) {
  //   Serial.print("ANALOG READ: ");
  //   Serial.println(pinVal);
  //   // Serial.print(" SCALED VALUE: ");
  //   // Serial.println(maxValue - minValue);
  // }

  pinVal = pinVal < minValue ? minValue : (pinVal > maxValue ? maxValue : pinVal);

  unsigned int scaledValue = (100 * (pinVal - minValue)) / (maxValue - minValue);

  return uint8_t(scaledValue);
}