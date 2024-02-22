#pragma once
#include <stdint.h>
#include "Arduino.h"
#include "Interfaces.h"
#include "BasicComponent.h"

class OutputComponent : public BasicComponent {
  public:
    OutputComponent(
      int _pinIn, 
      int _pinOut,
      bool _inputRestValue = HIGH,
      bool _outputRestValue = LOW,
      unsigned long _debounceDelay = 10
    );
    virtual void setComponentID(uint8_t id);
    virtual void setMessageQueue(MessageQueue* queue);
    virtual void triggerOutput();
    virtual void untriggerOutput();

  protected:
    uint8_t component_id;
    bool alreadyTriggered; 
    MessageQueue* writeQueue;
};
