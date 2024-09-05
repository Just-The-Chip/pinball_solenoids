#pragma once
#include "Interfaces.h"

class OutputCommInComponent : public MessageHandler {
  public:
    OutputCommInComponent(
      int _pinOut,
      unsigned long _outputDuration,
      bool _outputRestValue = LOW
    );
    virtual void handleMessage(uint8_t id, unsigned char content);
    virtual void update();
    virtual bool shouldTriggerOutput();
    virtual void triggerOutput();
    virtual void untriggerOutput();

  protected:
    int	pinOut;
    bool outputRestValue;
    unsigned long outputDuration;
    unsigned long outputOnTime;
    unsigned long lastUpdateTime;
    bool timeElapsed();
    bool messageReceived;
};