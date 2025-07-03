#pragma once
#include "Arduino.h"
#include "OutputCommInComponent.h"

class OutputCommTimeInComponent : public OutputCommInComponent {
  public:
    OutputCommTimeInComponent(
      int _pinOut,
      bool _outputRestValue = LOW
    );
    virtual void handleMessage(uint8_t id, unsigned char content);
};