#include "PiComm.h"
#include "PopBumper.h"
#include "Interfaces.h"

#define POP_BUMPER_1_IN 37   // top
#define POP_BUMPER_1_OUT 46

#define POP_BUMPER_2_IN 34   // middle
#define POP_BUMPER_2_OUT 45

#define POP_BUMPER_3_IN 35   // bottom
#define POP_BUMPER_3_OUT 44

MessageHandler* handlers[3];

PopBumper *popBumper1;
PopBumper *popBumper2;
PopBumper *popBumper3;

PiComm *comm;

void setup() {
  delay(500);

  popBumper1 = new PopBumper(POP_BUMPER_1_IN, POP_BUMPER_1_OUT, 50, HIGH, HIGH);
  popBumper2 = new PopBumper(POP_BUMPER_2_IN, POP_BUMPER_2_OUT, 50, HIGH, HIGH);
  popBumper3 = new PopBumper(POP_BUMPER_3_IN, POP_BUMPER_3_OUT, 50, HIGH, HIGH);

  setupPopBumper(popBumper1, 0);
  setupPopBumper(popBumper2, 1);
  setupPopBumper(popBumper3, 2);

  comm = new PiComm();
}

void setupPopBumper(PopBumper *popbumper, uint8_t id) {
  popbumper->setComponentID(id);
  popbumper->setMessageQueue(comm);

  // this is to make sure that even if a component does not need to react to an incomming message, 
  // the IDs are still lined up to the component
  handlers[id] = NULL;
}

void loop() {
  comm->handleIncomingMessages(handlers);

  updateComponents();

  comm->writeQueuedMessages();
}

void updateComponents() {
  popBumper1->update();
  popBumper2->update();
  popBumper3->update();
}
