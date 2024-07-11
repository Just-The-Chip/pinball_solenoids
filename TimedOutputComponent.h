#pragma once
#include <stdint.h>
#include "OutputComponent.h"

class TimedOutputComponent : public OutputComponent {
  public:
    TimedOutputComponent(
      int _pinIn, 
      int _pinOut,
      unsigned long _outputDuration,
      bool _inputRestValue = HIGH,
      bool _outputRestValue = LOW,
      unsigned long _debounceDelay = 10
    );
    virtual void update();
    virtual bool shouldTriggerOutput();

  protected:
    unsigned long outputDuration;
    unsigned long outputOnTime;
    unsigned long lastUpdateTime;
    bool TimeElapsed();
    bool timeSet = false;
    void untriggerOutput();
};