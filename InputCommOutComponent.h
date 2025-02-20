#pragma once
#include "Interfaces.h"

class InputCommOutComponent: public CommOutInterface {
  public:
    InputCommOutComponent(int _pinIn, bool _inputRestValue = HIGH, unsigned long _debounceDelay = 10);
    virtual void setComponentID(uint8_t id);
    virtual void setMessageQueue(MessageQueue* queue);
    virtual void update();
    virtual bool shouldTriggerComm();
    virtual bool inputActivated();
    virtual bool debouncedInputRead();
    virtual void triggerComm();
    virtual void untriggerComm();


  protected:
    int	pinIn;
    bool inputRestValue;

    unsigned int debounceDelay;
    bool lastInputState;
    bool currentInputState;
    unsigned long debounceTime;

    uint8_t component_id;
    bool alreadyTriggered; 
    MessageQueue* writeQueue;
    
};