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
    // virtual void update();
    // virtual bool shouldTriggerOutput();
    // virtual void triggerOutput();
    // virtual void untriggerOutput();

  // protected:
  //   int	pinOut;
  //   bool outputRestValue;
  //   unsigned long outputDuration;
  //   unsigned long outputOnTime;
  //   unsigned long lastUpdateTime;
  //   virtual bool timeElapsed();
  //   bool messageReceived;
};