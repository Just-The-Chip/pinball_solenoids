#include "HardwareSerial.h"
#include "Arduino.h"
#include "PiComm.h"
#include <ArduinoQueue.h>

PiComm::PiComm() {
  writeQueue = new ArduinoQueue<PiMessage>(25);
  Serial.begin(115200);
}

// expected message format: 
void PiComm::handleIncomingMessages(MessageHandler* handlers[]) {
  uint8_t max_id = HANDLERS_LENGTH;
  while(available() > 0) {
    unsigned char message[MESSAGE_LENGTH];

    int bytesRead = Serial.readBytesUntil(MESSAGE_TERMINATOR, message, MESSAGE_LENGTH);

    if(bytesRead == (MESSAGE_LENGTH - 1)) {
      uint8_t handler_id = uint8_t(message[0]);
      unsigned char message_content = message[1];

      // if handler_id is within bounds of the handlers array
      if(handler_id < max_id && handlers[handler_id] != NULL) {
        handlers[handler_id]->handleMessage(handler_id, message_content);
      } else {
        Serial.print("Handler ID ");
        Serial.print(handler_id);
        Serial.println(" is missing.");
      }
    } else {
      Serial.print("Invalid num of bytes: ");
      Serial.print(bytesRead);

      if(bytesRead >= MESSAGE_LENGTH) {
        Serial.print(", Byte0=");
        Serial.print(uint8_t(message[0]));

        Serial.print(", Byte1=");
        Serial.print(uint8_t(message[1]));

        Serial.print(", Byte3=");
        Serial.print(uint8_t(message[2]));

        int remaining_messages = available();
        flushSerialBuffer(remaining_messages * MESSAGE_LENGTH);
      } else {
        Serial.print(", msg too small");
      }

      Serial.println("...end");
    }
  }
}

void PiComm::flushSerialBuffer(uint8_t flush_until = 0) {
  while(Serial.available() > flush_until) {
    char t = Serial.read();
    Serial.print(" flushed: ");
    Serial.print(uint8_t(t));
    Serial.print(", ");
  }
}

// not sure what happens when queue gets to max size
void PiComm::queueOutgoingMessage(uint8_t component_id, unsigned char message_content) {
  // Serial.println("queue boo");
  struct PiMessage message;
  message.id = component_id;
  message.content = message_content;
  
  writeQueue->enqueue(message);
}

void PiComm::writeQueuedMessages() {
  while(!writeQueue->isEmpty()) {
    writeMessage(writeQueue->dequeue());
  }
}

int PiComm::available() {
  return Serial.available() / MESSAGE_LENGTH;
}

void PiComm::writeMessage(PiMessage message) {
  char outgoing_message[3] = {message.id, message.content, MESSAGE_TERMINATOR};
  Serial.write(outgoing_message, 3);
}