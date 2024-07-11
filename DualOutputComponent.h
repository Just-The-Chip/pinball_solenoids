#pragma once
#include <stdint.h>
#include "TimedOutputComponent.h"

class DualOutputComponent : public TimedOutputComponent {
  public:
    DualOutputComponent(
      int _pinIn, 
      int _pinOut,  //  Output for high power
      int _lowPinOut, //  Output for low power
      unsigned long _outputDuration,
      bool _inputRestValue = HIGH,
      bool _outputRestValue = LOW,
      unsigned long _debounceDelay = 10
    );
    virtual void triggerOutput();
    virtual void untriggerOutput();
    virtual bool shouldTriggerOutput();

  protected:
    int lowPowerPin;
};