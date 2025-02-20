#pragma once
#include <stdint.h>

class MessageHandler {
  public:
    virtual void handleMessage(uint8_t id, unsigned char content) = 0;
};

class MessageQueue {
  public:
    virtual void queueOutgoingMessage(uint8_t handler_id, unsigned char message_content) = 0;
};

class CommOutInterface {
  public:
    virtual void setComponentID(uint8_t id) = 0;
    virtual void setMessageQueue(MessageQueue* queue) = 0;
};