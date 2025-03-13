#pragma once
#include "Interfaces.h"

class AnalogCommOutComponent : public CommOutInterface {
  public:
    AnalogCommOutComponent(int _pinIn, unsigned int _minValue = 0, unsigned int _maxValue = 1023, unsigned long _readInterval = 10);
    virtual void setComponentID(uint8_t id);
    virtual void setMessageQueue(MessageQueue* queue);
    virtual void update();
    virtual bool shouldTriggerComm(unsigned char readValue);
    virtual unsigned char scaledInputRead();
    virtual void triggerComm(unsigned char readValue);

  protected:
    int	pinIn;

    unsigned int readInterval;
    int minValue;
    int maxValue;
    bool currentInputState;
    unsigned long lastReadTime;

    uint8_t component_id;
    MessageQueue* writeQueue;    
};