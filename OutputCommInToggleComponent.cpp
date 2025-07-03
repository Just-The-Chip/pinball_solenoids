#include "OutputCommInToggleComponent.h"

OutputCommInToggleComponent::OutputCommInToggleComponent(int _pinOut, unsigned long _maxDuration, bool _outputRestValue) :
  OutputCommInComponent(_pinOut, _maxDuration, _outputRestValue){
    toggleState = false;
}

void OutputCommInToggleComponent::handleMessage(uint8_t id, unsigned char content) {
  OutputCommInComponent::handleMessage(id, content);

  // message can turn it both on and off
  toggleState = content > 0;
}

bool OutputCommInToggleComponent::shouldTriggerOutput() {
  // if(toggleState) {
  //   Serial.print("last update time > outputduration: ");
  //   Serial.print(lastUpdateTime > outputDuration);
  //   Serial.print(" duration: ");
  //   Serial.println(lastUpdateTime - outputOnTime);
  // }
  return toggleState && OutputCommInComponent::shouldTriggerOutput();
}