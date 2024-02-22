#include "PiComm.h"
#include "BasicComponent.h"
#include "OutputComponent.h"
#include "Interfaces.h"

#define BTN1_PIN 25 // left flipper
#define BTN2_PIN 24 // right flipper

#define FLIPPER_L 27
#define FLIPPER_R 26

#define START_IN 33
#define LAUNCHER 48

#define POP_BUMPER_1_IN 37   // top
#define POP_BUMPER_1_OUT 46

#define POP_BUMPER_2_IN 34   // middle
#define POP_BUMPER_2_OUT 45

#define POP_BUMPER_3_IN 35   // bottom
#define POP_BUMPER_3_OUT 44

#define LEFT_SLING_IN 23
#define LEFT_SLING_OUT 49

#define RIGHT_SLING_IN 22
#define RIGHT_SLING_OUT 47 //50

#define RAMP_RETURN_OUT 51
#define RAMP_RETURN_IN 32

#define LAUNCHER 48

MessageHandler* handlers[7];

BasicComponent *leftFlipper;
BasicComponent *rightFlipper;

OutputComponent *leftSling;
OutputComponent *rightSling;

OutputComponent *launcher;
OutputComponent *rampReturn;

OutputComponent *popBumper1;
OutputComponent *popBumper2;
OutputComponent *popBumper3;

PiComm *comm;

void setup() {
  delay(500);

  Serial.begin(115200);

  comm = new PiComm();

  // flippers don't need to do any communication
  leftFlipper = new BasicComponent(BTN1_PIN, FLIPPER_L);
  rightFlipper = new BasicComponent(BTN2_PIN, FLIPPER_R);

  // slingshots - output only
  leftSling = new OutputComponent(LEFT_SLING_IN, LEFT_SLING_OUT, HIGH, HIGH);
  rightSling = new OutputComponent(RIGHT_SLING_IN, RIGHT_SLING_OUT, HIGH, HIGH);

  setupOutputComponent(leftSling, 0);
  setupOutputComponent(rightSling, 1);

  // ball return and launch - output only
  launcher = new OutputComponent(START_IN, LAUNCHER, LOW, HIGH, 20);
  rampReturn = new OutputComponent(RAMP_RETURN_IN, RAMP_RETURN_OUT, HIGH, HIGH, 20);

  setupOutputComponent(launcher, 2); // round start
  setupOutputComponent(rampReturn, 3); // round end or multiball stuff idk

  // pop bumpers - output only
  popBumper1 = new OutputComponent(POP_BUMPER_1_IN, POP_BUMPER_1_OUT, HIGH, HIGH);
  popBumper2 = new OutputComponent(POP_BUMPER_2_IN, POP_BUMPER_2_OUT, HIGH, HIGH);
  popBumper3 = new OutputComponent(POP_BUMPER_3_IN, POP_BUMPER_3_OUT, HIGH, HIGH);

  setupOutputComponent(popBumper1, 4);
  setupOutputComponent(popBumper2, 5);
  setupOutputComponent(popBumper3, 6);
}

void setupOutputComponent(OutputComponent *component, uint8_t id) {
  component->setComponentID(id);
  component->setMessageQueue(comm);

  // this is to make sure that even if a component does not need to react to an incomming message, 
  // the IDs are still lined up to the component. OutputComponents are output only.
  handlers[id] = NULL;
}

void loop() {
  comm->handleIncomingMessages(handlers);

  // at some point we will keep track of game mode to decide which components to update
  // but for now we will just update everything
  updateStartGameComponents();
  updatePlayModeComponents();

  comm->writeQueuedMessages();
}

void updateStartGameComponents() {
  launcher->update();
}

void updatePlayModeComponents() {
  leftFlipper->update();
  rightFlipper->update();

  rampReturn->update();

  leftSling->update();
  rightSling->update();

  popBumper1->update();
  popBumper2->update();
  popBumper3->update();
}
