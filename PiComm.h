#pragma once
#include <stdint.h>
#include "Arduino.h"
#include "Interfaces.h"
#include <ArduinoQueue.h>

#define MESSAGE_TERMINATOR '\n'
#define MESSAGE_LENGTH 3

struct PiMessage {
  uint8_t id;
  unsigned char content;
};

class PiComm : public MessageQueue {
  public:
    PiComm();
    void handleIncomingMessages(MessageHandler* handlers[]);
    void queueOutgoingMessage(uint8_t component_id, unsigned char message_content);
    void writeQueuedMessages();

  protected:
    int available();
    void writeMessage(PiMessage message);

    ArduinoQueue<PiMessage> *writeQueue;
};