#pragma once
#include <stdint.h>
#include "Arduino.h"

class BasicComponent {
  public:
    BasicComponent(
      int _pinIn, 
      int _pinOut,
      bool _inputRestValue = HIGH,
      bool _outputRestValue = LOW      
    );
    virtual void update();
    virtual bool shouldTriggerOutput();
    virtual bool inputActivated();
    virtual void triggerOutput();
    virtual void untriggerOutput();

  protected:
    int	pinIn;
    int	pinOut;
    bool inputRestValue;
    bool outputRestValue;
  };