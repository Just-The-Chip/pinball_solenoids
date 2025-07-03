#pragma once
#include "Arduino.h"
#include "OutputCommInComponent.h"

class OutputCommInToggleComponent : public OutputCommInComponent {
  public:
    OutputCommInToggleComponent(
      int _pinOut,
      unsigned long _maxDuration,
      bool _outputRestValue = LOW
    );
    virtual void handleMessage(uint8_t id, unsigned char content);
    virtual bool shouldTriggerOutput();

  protected:
    bool toggleState;
};