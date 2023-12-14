#pragma once

class MessageHandler {
  public:
    virtual void handleMessage(uint8_t id, unsigned char content) = 0;
};