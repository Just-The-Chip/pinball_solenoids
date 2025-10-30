#include "PiComm.h"
#include "BasicComponent.h"
#include "OutputComponent.h"
#include "TimedOutputComponent.h"
#include "DualOutputComponent.h"
#include "InputCommOutComponent.h"
#include "OutputCommInComponent.h"
#include "OutputCommInToggleComponent.h"
#include "OutputCommTimeInComponent.h"
#include "AnalogCommOutComponent.h"
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
#define MAG_BRIDGE_RETURN_ROLLOVER 36

#define MAG_BRIDGE_SPINNER 50
#define MAG_BRIDGE_SPINNER_STOP 30

#define SPINNER_TARGET_1 14
#define SPINNER_TARGET_2 15
#define SPINNER_TARGET_3 59 //A5
#define SPINNER_TARGET_4 63 //A9
#define SPINNER_TARGET_5 67 //A13
#define SPINNER_TARGET_6 58 //A4
#define SPINNER_TARGET_7 62 //A8
#define SPINNER_TARGET_8 66 //A12

#define MULTI_BALL_SPINDLE_MOTOR 53
#define MULTI_BALL_BALL_DETECT 29

#define PLINKO_LIFT 42

#define PLINKO_LANE1 69
#define PLINKO_LANE2 65
#define PLINKO_LANE3 61
#define PLINKO_LANE4 57

#define LEFT_DRAIN_LANE 11
#define RIGHT_DRAIN_LANE 31

#define LEFT_INNER_LANE_2 12
#define LEFT_INNER_LANE_1 13
#define RIGHT_INNER_LANE_1 16
#define RIGHT_INNER_LANE_2 17

#define SLIDER A0

MessageHandler* handlers[HANDLERS_LENGTH];

OutputComponent *leftFlipper;
OutputComponent *rightFlipper;
DualOutputComponent *leftSecondaryFlipper;
BasicComponent *rightSecondaryFlipper;

OutputComponent *leftSling;
OutputComponent *rightSling;

InputCommOutComponent *startButton;
OutputCommInComponent *launcher;
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
InputCommOutComponent *magBridgeReturnRollover;

InputCommOutComponent *upperTarget1;
InputCommOutComponent *upperTarget2;
InputCommOutComponent *upperTarget3;
InputCommOutComponent *upperTarget4;

OutputCommInComponent *magBridgeRejector;

OutputCommInToggleComponent *magBridgeSpinner;
InputCommOutComponent *magBridgeSpinnerStop;

InputCommOutComponent *spinnerTarget1;
InputCommOutComponent *spinnerTarget2;
InputCommOutComponent *spinnerTarget3;
InputCommOutComponent *spinnerTarget4;
InputCommOutComponent *spinnerTarget5;
InputCommOutComponent *spinnerTarget6;
InputCommOutComponent *spinnerTarget7;
InputCommOutComponent *spinnerTarget8;

OutputCommTimeInComponent *multiBallSpindleMotor;
InputCommOutComponent *multiBallBallDetect;

OutputCommInComponent *plinkoLift;

InputCommOutComponent *plinkoLane1;
InputCommOutComponent *plinkoLane2;
InputCommOutComponent *plinkoLane3;
InputCommOutComponent *plinkoLane4;

AnalogCommOutComponent *sliderSensor;

InputCommOutComponent *leftDrainRollover;
InputCommOutComponent *rightDrainRollover;

InputCommOutComponent *leftInnerRollover2;
InputCommOutComponent *leftInnerRollover1;
InputCommOutComponent *rightInnerRollover1;
InputCommOutComponent *rightInnerRollover2;

PiComm *comm;

void setup() {
  delay(500);

  Serial.begin(115200);
  
  comm = new PiComm();

  leftFlipper = new OutputComponent(BTN1_PIN, FLIPPER_L);
  rightFlipper = new OutputComponent(BTN2_PIN, FLIPPER_R);
  setupCommOutComponent(leftFlipper, 52);
  setupCommOutComponent(rightFlipper, 53);

  leftSecondaryFlipper = new DualOutputComponent(BTN1_PIN, LEFT_SECONDARY_FLIPPER, LEFT_SECONDARY_FLIPPER_LOW_POWER, 150);
  rightSecondaryFlipper = new DualOutputComponent(BTN2_PIN, RIGHT_SECONDARY_FLIPPER, RIGHT_SECONDARY_FLIPPER_LOW_POWER, 150);

  // slingshots - output only
  leftSling = new OutputComponent(LEFT_SLING_IN, LEFT_SLING_OUT, HIGH, LOW);
  rightSling = new OutputComponent(RIGHT_SLING_IN, RIGHT_SLING_OUT, HIGH, LOW);

  setupCommOutComponent(leftSling, 0);
  setupCommOutComponent(rightSling, 1);

  // ball return and launch - output only
  startButton = new InputCommOutComponent(START_IN, LOW, 20);
  launcher = new OutputCommInComponent(LAUNCHER, 100, LOW);

  // launcher = new OutputComponent(START_IN, LAUNCHER, LOW, LOW, 20);
  rampReturn = new TimedOutputComponent(RAMP_RETURN_IN, RAMP_RETURN_OUT, 150, HIGH, LOW, 20);

  setupCommOutComponent(startButton, 2); // round start
  setupMessageHandler(launcher, 32); // launch ball
  setupCommOutComponent(rampReturn, 3); // round end or multiball stuff idk

  // pop bumpers - output only
  popBumper1 = new OutputComponent(POP_BUMPER_1_IN, POP_BUMPER_1_OUT, HIGH, LOW);
  popBumper2 = new OutputComponent(POP_BUMPER_2_IN, POP_BUMPER_2_OUT, HIGH, LOW);
  popBumper3 = new OutputComponent(POP_BUMPER_3_IN, POP_BUMPER_3_OUT, HIGH, LOW);

  setupCommOutComponent(popBumper1, 4);
  setupCommOutComponent(popBumper2, 5);
  setupCommOutComponent(popBumper3, 6);

  // static targets
  leftTarget1 = new InputCommOutComponent(LEFT_TARGET_1, HIGH, 4);
  leftTarget2 = new InputCommOutComponent(LEFT_TARGET_2, HIGH, 4);
  leftTarget3 = new InputCommOutComponent(LEFT_TARGET_3, HIGH, 4);
  leftTarget4 = new InputCommOutComponent(LEFT_TARGET_4, HIGH, 4);

  setupCommOutComponent(leftTarget1, 7);
  setupCommOutComponent(leftTarget2, 8);
  setupCommOutComponent(leftTarget3, 9);
  handlers[10] = NULL; // 10 correspons to \n in ascii so we skip it
  setupCommOutComponent(leftTarget4, 11);

  handlers[12] = NULL;
  handlers[13] = NULL;
  handlers[14] = NULL;

  // lane buttons
  returnLane = new InputCommOutComponent(RETURN_LANE, HIGH, 4);
  rightUpperLane = new InputCommOutComponent(RIGHT_UPPER_LANE, HIGH, 4);

  setupCommOutComponent(returnLane, 15);
  setupCommOutComponent(rightUpperLane, 16);

  // mag bridge static targets
  upperTarget1 = new InputCommOutComponent(UPPER_TARGET_1, HIGH, 4);
  upperTarget2 = new InputCommOutComponent(UPPER_TARGET_2, HIGH, 4);
  upperTarget3 = new InputCommOutComponent(UPPER_TARGET_3, HIGH, 4);
  upperTarget4 = new InputCommOutComponent(UPPER_TARGET_4, HIGH, 4);

  setupCommOutComponent(upperTarget1, 17);
  setupCommOutComponent(upperTarget2, 18);
  setupCommOutComponent(upperTarget3, 19);
  setupCommOutComponent(upperTarget4, 20);

  magBridgeSensor = new InputCommOutComponent(MAG_BRIDGE_SENSOR, HIGH, 500);
  setupCommOutComponent(magBridgeSensor, 21);

  magBridgeRejector = new OutputCommInComponent(MAG_BRIDGE_REJECTOR, 250, LOW);
  setupMessageHandler(magBridgeRejector, 22);

  handlers[23] = NULL;
  
  multiBallSpindleMotor = new OutputCommTimeInComponent(MULTI_BALL_SPINDLE_MOTOR, LOW);
  setupMessageHandler(multiBallSpindleMotor, 24);

  multiBallBallDetect = new InputCommOutComponent(MULTI_BALL_BALL_DETECT, HIGH, 10);
  setupCommOutComponent(multiBallBallDetect, 25);

  plinkoLift = new OutputCommInComponent(PLINKO_LIFT, 8500, LOW);
  setupMessageHandler(plinkoLift, 26);

  plinkoLane1 = new InputCommOutComponent(PLINKO_LANE1, HIGH, 4);
  plinkoLane2 = new InputCommOutComponent(PLINKO_LANE2, HIGH, 4);
  plinkoLane3 = new InputCommOutComponent(PLINKO_LANE3, HIGH, 4);
  plinkoLane4 = new InputCommOutComponent(PLINKO_LANE4, HIGH, 4);

  setupCommOutComponent(plinkoLane1, 27);
  setupCommOutComponent(plinkoLane2, 28);
  setupCommOutComponent(plinkoLane3, 29);
  setupCommOutComponent(plinkoLane4, 30);

  int sliderMinVal = 15; // 39; // 50
  int sliderMaxVal = 420; // 640
  unsigned long readInterval = 20;
  sliderSensor = new AnalogCommOutComponent(SLIDER, sliderMinVal, sliderMaxVal, readInterval);
  setupCommOutComponent(sliderSensor, 31);

  handlers[33] = NULL; // on solonoid board

  // max spin time is 2 minutes
  magBridgeSpinner = new OutputCommInToggleComponent(MAG_BRIDGE_SPINNER, 120000, LOW);
  magBridgeSpinnerStop = new InputCommOutComponent(MAG_BRIDGE_SPINNER_STOP, HIGH);
  setupMessageHandler(magBridgeSpinner, 34);
  setupCommOutComponent(magBridgeSpinnerStop, 35);

  spinnerTarget1 = new InputCommOutComponent(SPINNER_TARGET_1, HIGH, 4);
  spinnerTarget2 = new InputCommOutComponent(SPINNER_TARGET_2, HIGH, 4);
  spinnerTarget3 = new InputCommOutComponent(SPINNER_TARGET_3, HIGH, 4);
  spinnerTarget4 = new InputCommOutComponent(SPINNER_TARGET_4, HIGH, 4);
  spinnerTarget5 = new InputCommOutComponent(SPINNER_TARGET_5, HIGH, 4);
  spinnerTarget6 = new InputCommOutComponent(SPINNER_TARGET_6, HIGH, 4);
  spinnerTarget7 = new InputCommOutComponent(SPINNER_TARGET_7, HIGH, 4);
  spinnerTarget8 = new InputCommOutComponent(SPINNER_TARGET_8, HIGH, 4);

  setupCommOutComponent(spinnerTarget1, 36);
  setupCommOutComponent(spinnerTarget2, 37);
  setupCommOutComponent(spinnerTarget3, 38);
  setupCommOutComponent(spinnerTarget4, 39);
  setupCommOutComponent(spinnerTarget5, 40);
  setupCommOutComponent(spinnerTarget6, 41);
  setupCommOutComponent(spinnerTarget7, 42);
  setupCommOutComponent(spinnerTarget8, 43);

  magBridgeReturnRollover = new InputCommOutComponent(MAG_BRIDGE_RETURN_ROLLOVER, HIGH, 10);
  setupCommOutComponent(magBridgeReturnRollover, 44);

  leftDrainRollover = new InputCommOutComponent(LEFT_DRAIN_LANE, HIGH, 4);
  rightDrainRollover = new InputCommOutComponent(RIGHT_DRAIN_LANE, HIGH, 4);
  setupCommOutComponent(leftDrainRollover, 45);
  setupCommOutComponent(rightDrainRollover, 46);

  leftInnerRollover2 = new InputCommOutComponent(LEFT_INNER_LANE_2, HIGH, 4);
  leftInnerRollover1 = new InputCommOutComponent(LEFT_INNER_LANE_1, HIGH, 4);
  rightInnerRollover1 = new InputCommOutComponent(RIGHT_INNER_LANE_1, HIGH, 4);
  rightInnerRollover2 = new InputCommOutComponent(RIGHT_INNER_LANE_2, HIGH, 4);

  setupCommOutComponent(leftInnerRollover2, 47);
  setupCommOutComponent(leftInnerRollover1, 48);
  setupCommOutComponent(rightInnerRollover1, 49);
  setupCommOutComponent(rightInnerRollover2, 50);

  handlers[51] = NULL; // on servo board
  // 52 and 53 are the flippers and are defined at the top
}

void setupCommOutComponent(CommOutInterface *component, uint8_t id) {
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

  startButton->update();
  launcher->update();

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
  magBridgeSpinner->update();
  magBridgeSpinnerStop->update();

  spinnerTarget1->update();
  spinnerTarget2->update();
  spinnerTarget3->update();
  spinnerTarget4->update();
  spinnerTarget5->update();
  spinnerTarget6->update();
  spinnerTarget7->update();
  spinnerTarget8->update();

  multiBallSpindleMotor->update();
  multiBallBallDetect->update();

  plinkoLift->update();
  plinkoLane1->update();
  plinkoLane2->update();
  plinkoLane3->update();
  plinkoLane4->update();

  sliderSensor->update();

  magBridgeReturnRollover->update();

  leftDrainRollover->update();
  rightDrainRollover->update();

  leftInnerRollover2->update();
  leftInnerRollover1->update();
  rightInnerRollover1->update();
  rightInnerRollover2->update();
}
