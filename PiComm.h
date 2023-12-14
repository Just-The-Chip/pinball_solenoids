#pragma once
#include "Arduino.h"
#include "MessageHandler.h"
#include <ArduinoQueue.h>

#define MESSAGE_TERMINATOR '\n'
#define MESSAGE_LENGTH 3

struct PiMessage {
  uint8_t id;
  unsigned char content;
};

class PiComm {
  public:
    PiComm();
    void handleIncomingMessages(MessageHandler* handlers[]);
    void queueOutgoingMessage(PiMessage message);
    void writeQueuedMessages();

  protected:
    int available();
    void writeMessage(PiMessage message);

    ArduinoQueue<PiMessage> *writeQueue;
};