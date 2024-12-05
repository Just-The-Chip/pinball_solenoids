#include "PiComm.h"
#include "BasicComponent.h"
#include "OutputComponent.h"
#include "TimedOutputComponent.h"
#include "DualOutputComponent.h"
#include "InputCommOutComponent.h"
#include "OutputCommInComponent.h"
#include "Interfaces.h"

#define BTN1_PIN 25 // left flipper in
#define BTN2_PIN 24 // right flipper in

#define FLIPPER_L 27
#define FLIPPER_R 26

#define START_IN 33
#define LAUNCHER 39 // solonoid 1 //48

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

#define LEFT_TARGET_1 18
#define LEFT_TARGET_2 19
#define LEFT_TARGET_3 20
#define LEFT_TARGET_4 21

#define UPPER_TARGET_1 56
#define UPPER_TARGET_2 60
#define UPPER_TARGET_3 64
#define UPPER_TARGET_4 68

#define RIGHT_SECONDARY_FLIPPER 38
#define RIGHT_SECONDARY_FLIPPER_LOW_POWER 48
#define LEFT_SECONDARY_FLIPPER 40
#define LEFT_SECONDARY_FLIPPER_LOW_POWER 43

#define RETURN_LANE 28
#define RIGHT_UPPER_LANE 36

#define MAG_BRIDGE_SENSOR 55
#define MAG_BRIDGE_REJECTOR 52

#define MULTI_BALL_SPINDLE_MOTOR 53
#define MULTI_BALL_BALL_DETECT 29

#define PLINKO_LIFT 42

#define PLINKO_LANE1 69
#define PLINKO_LANE2 65
#define PLINKO_LANE3 61
#define PLINKO_LANE4 56

MessageHandler* handlers[HANDLERS_LENGTH];

BasicComponent *leftFlipper;
BasicComponent *rightFlipper;
DualOutputComponent *leftSecondaryFlipper;
BasicComponent *rightSecondaryFlipper;

OutputComponent *leftSling;
OutputComponent *rightSling;

OutputComponent *launcher;
TimedOutputComponent *rampReturn;

OutputComponent *popBumper1;
OutputComponent *popBumper2;
OutputComponent *popBumper3;

InputCommOutComponent *leftTarget1;
InputCommOutComponent *leftTarget2;
InputCommOutComponent *leftTarget3;
InputCommOutComponent *leftTarget4;

InputCommOutComponent *returnLane;
InputCommOutComponent *rightUpperLane;

InputCommOutComponent *magBridgeSensor;

InputCommOutComponent *upperTarget1;
InputCommOutComponent *upperTarget2;
InputCommOutComponent *upperTarget3;
InputCommOutComponent *upperTarget4;

OutputCommInComponent *magBridgeRejector;

OutputCommInComponent *multiBallSpindleMotor;
InputCommOutComponent *multiBallBallDetect;

OutputCommInComponent *plinkoLift;

InputCommOutComponent *plinkoLane1;
InputCommOutComponent *plinkoLane2;
InputCommOutComponent *plinkoLane3;
InputCommOutComponent *plinkoLane4;

PiComm *comm;

void setup() {
  delay(500);

  Serial.begin(115200);
  
  comm = new PiComm();

  // flippers don't need to do any communication
  leftFlipper = new BasicComponent(BTN1_PIN, FLIPPER_L);
  rightFlipper = new BasicComponent(BTN2_PIN, FLIPPER_R);

  leftSecondaryFlipper = new DualOutputComponent(BTN1_PIN, LEFT_SECONDARY_FLIPPER, LEFT_SECONDARY_FLIPPER_LOW_POWER, 150);
  rightSecondaryFlipper = new DualOutputComponent(BTN2_PIN, RIGHT_SECONDARY_FLIPPER, RIGHT_SECONDARY_FLIPPER_LOW_POWER, 150);

  // slingshots - output only
  leftSling = new OutputComponent(LEFT_SLING_IN, LEFT_SLING_OUT, HIGH, LOW);
  rightSling = new OutputComponent(RIGHT_SLING_IN, RIGHT_SLING_OUT, HIGH, LOW);

  setupOutputComponent(leftSling, 0);
  setupOutputComponent(rightSling, 1);

  // ball return and launch - output only
  launcher = new OutputComponent(START_IN, LAUNCHER, LOW, LOW, 20);
  rampReturn = new TimedOutputComponent(RAMP_RETURN_IN, RAMP_RETURN_OUT, 150, HIGH, LOW, 20);

  setupOutputComponent(launcher, 2); // round start
  setupOutputComponent(rampReturn, 3); // round end or multiball stuff idk

  // pop bumpers - output only
  popBumper1 = new OutputComponent(POP_BUMPER_1_IN, POP_BUMPER_1_OUT, HIGH, LOW);
  popBumper2 = new OutputComponent(POP_BUMPER_2_IN, POP_BUMPER_2_OUT, HIGH, LOW);
  popBumper3 = new OutputComponent(POP_BUMPER_3_IN, POP_BUMPER_3_OUT, HIGH, LOW);

  setupOutputComponent(popBumper1, 4);
  setupOutputComponent(popBumper2, 5);
  setupOutputComponent(popBumper3, 6);

  // static targets
  leftTarget1 = new InputCommOutComponent(LEFT_TARGET_1, HIGH, 4);
  leftTarget2 = new InputCommOutComponent(LEFT_TARGET_2, HIGH, 4);
  leftTarget3 = new InputCommOutComponent(LEFT_TARGET_3, HIGH, 4);
  leftTarget4 = new InputCommOutComponent(LEFT_TARGET_4, HIGH, 4);

  setupInputOutComm(leftTarget1, 7);
  setupInputOutComm(leftTarget2, 8);
  setupInputOutComm(leftTarget3, 9);
  setupInputOutComm(leftTarget4, 11); // 10 correspons to \n in ascii so we skip it

  // lane buttons
  returnLane = new InputCommOutComponent(RETURN_LANE, HIGH, 4);
  rightUpperLane = new InputCommOutComponent(RIGHT_UPPER_LANE, HIGH, 4);

  setupInputOutComm(returnLane, 15);
  setupInputOutComm(rightUpperLane, 16);

  // mag bridge static targets
  upperTarget1 = new InputCommOutComponent(UPPER_TARGET_1, HIGH, 4);
  upperTarget2 = new InputCommOutComponent(UPPER_TARGET_2, HIGH, 4);
  upperTarget3 = new InputCommOutComponent(UPPER_TARGET_3, HIGH, 4);
  upperTarget4 = new InputCommOutComponent(UPPER_TARGET_4, HIGH, 4);

  setupInputOutComm(upperTarget1, 17);
  setupInputOutComm(upperTarget2, 18);
  setupInputOutComm(upperTarget3, 19);
  setupInputOutComm(upperTarget4, 20);

  magBridgeSensor = new InputCommOutComponent(MAG_BRIDGE_SENSOR, HIGH, 500);
  setupInputOutComm(magBridgeSensor, 21);

  magBridgeRejector = new OutputCommInComponent(MAG_BRIDGE_REJECTOR, 250, LOW);
  setupMessageHandler(magBridgeRejector, 22);
  
  multiBallSpindleMotor = new OutputCommInComponent(MULTI_BALL_SPINDLE_MOTOR, 1000, LOW);
  setupMessageHandler(multiBallSpindleMotor, 24);

  multiBallBallDetect = new InputCommOutComponent(MULTI_BALL_BALL_DETECT, HIGH, 50);
  setupInputOutComm(multiBallBallDetect, 25);

  plinkoLift = new OutputCommInComponent(PLINKO_LIFT, 10000, LOW);
  setupMessageHandler(plinkoLift, 26)

  plinkoLane1 = new InputCommOutComponent(PLINKO_LANE1, HIGH, 4);
  plinkoLane2 = new InputCommOutComponent(PLINKO_LANE2, HIGH, 4);
  plinkoLane3 = new InputCommOutComponent(PLINKO_LANE3, HIGH, 4);
  plinkoLane4 = new InputCommOutComponent(PLINKO_LANE4, HIGH, 4);

  setupInputOutComm(plinkoLane1, 27);
  setupInputOutComm(plinkoLane2, 28);
  setupInputOutComm(plinkoLane3, 29);
  setupInputOutComm(plinkoLane4, 30);
}

void setupOutputComponent(OutputComponent *component, uint8_t id) {
  component->setComponentID(id);
  component->setMessageQueue(comm);

  // this is to make sure that even if a component does not need to react to an incomming message, 
  // the IDs are still lined up to the component. OutputComponents are output only.
  handlers[id] = NULL;
}

void setupInputOutComm(InputCommOutComponent *component, uint8_t id) {
  component->setComponentID(id);
  component->setMessageQueue(comm);

  // this is to make sure that even if a component does not need to react to an incomming message, 
  // the IDs are still lined up to the component. OutputComponents are output only.
  handlers[id] = NULL;
}

void setupMessageHandler(MessageHandler *component, uint8_t id) {
  handlers[id] = component;
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

  leftSecondaryFlipper->update();
  rightSecondaryFlipper->update();

  rampReturn->update();

  leftSling->update();
  rightSling->update();

  popBumper1->update();
  popBumper2->update();
  popBumper3->update();

  leftTarget1->update();
  leftTarget2->update();
  leftTarget3->update();
  leftTarget4->update();

  returnLane->update();
  rightUpperLane->update();

  upperTarget1->update();
  upperTarget2->update();
  upperTarget3->update();
  upperTarget4->update();

  magBridgeSensor->update();
  magBridgeRejector->update();

  multiBallSpindleMotor->update();
  multiBallBallDetect->update();
}
