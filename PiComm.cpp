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

    // Serial.print("MESSAGE RECEIVED BYTES: ");
    // Serial.print(bytesRead);

    if(bytesRead == (MESSAGE_LENGTH - 1)) {
      uint8_t handler_id = uint8_t(message[0]);
      unsigned char message_content = message[1];

      // Serial.print(" HANDLER ID: ");
      // Serial.print(handler_id);

      // if handler_id is within bounds of the handlers array
      if(handler_id < max_id && handlers[handler_id] != NULL) {
        // Serial.print(" SUCCESS???");
        handlers[handler_id]->handleMessage(handler_id, message_content);
      }
    }

    // Serial.println(" Donesies.");
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