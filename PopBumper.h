#pragma once
#include <stdint.h>
#include "Arduino.h"
#include "Interfaces.h"
#include "TimedOutputComponent.h"

class PopBumper : public TimedOutputComponent {
  public:
    PopBumper(
      int _pinIn, 
      int _pinOut,
      unsigned long _outputDuration,
      bool _inputRestValue = HIGH,
      bool _outputRestValue = LOW      
    );
    virtual void setComponentID(uint8_t id);
    virtual void setMessageQueue(MessageQueue* queue);
    virtual void triggerOutput();

  protected:
    uint8_t component_id;
    MessageQueue* writeQueue;
};
