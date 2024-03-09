#include <AccelStepper.h>
#include <Arduino.h>
#include <ArduinoJson.h>
#include "CmdCode.h"
#include "Communication.h"
#include "ErrorCode.h"
#include "LinearStepper.h"
#include "pinConfig.h"

LinearStepper stepper1(stepPin1, dirPin1);
LinearStepper stepper2(stepPin2, dirPin2);
LinearStepper stepper3(stepPin3, dirPin3);
// LinearStepper stepper4(stepPin4, dirPin4);
LinearStepper *deviceList[] = {&stepper1, &stepper2, &stepper3};

// put function declarations here:

void communicateRoutine();  // 通讯例程

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  while (!Serial)
    ;

  Serial.println("Esp setup done!");
}

void loop() {
  // put your main code here, to run repeatedly:

  // 步进电机运行例程
  stepper1.routine();
  stepper2.routine();
  stepper3.routine();

  communicateRoutine(); // 通讯例程
}

// put function definitions here:

/// @brief 通讯例行程序
void communicateRoutine() {
  if (Serial.available() == 0) {
    return;
  }

  String s = Serial.readStringUntil('\n');
  JsonDocument doc;
  deserializeJson(doc, s);
  serializeJson(doc, Serial);
  Serial.println();

  Comm_Mode mode = doc["Mode"];
  byte id = doc["DeviceId"];
  LinearStepper *pStepper = deviceList[id - 1];

  // 根据 mode 的值，做出相应的行为

  if (mode == Comm_Mode::COMM_STOP) {  // Mode: COMM_STOP
      pStepper->stop();
      pStepper->setSpeed_mm(0.0);
    // if (pStepper->runMode == LinearStepper::RUN)
    // else if (pStepper->runMode == LinearStepper::RUN_SPEED)

  } else if (mode == Comm_Mode::COMM_RUN) {  // Mode: COMM_RUN
    // float mspd = doc["MaxSpeed"];
    // float acc = doc["Acceleration"];
    float spd = doc["Speed"];
    float tar = doc["Target"];
    pStepper->setState(LinearStepper::RunMode::RUN);
    // pStepper->setMaxSpeed_mm(mspd);
    // pStepper->setAcc_mm(acc);
    if(spd > pStepper->maxSpeed_mm())
      pStepper->setMaxSpeed_mm(spd);
    pStepper->setTarget_mm(tar);
    pStepper->setSpeed_mm(spd);
    
    
    // float mspd = doc["MaxSpeed"];
    // float acc = doc["Acceleration"];
    // float tar = doc["Target"];
    // pStepper->setState(LinearStepper::RunMode::RUN);
    // pStepper->setMaxSpeed_mm(mspd);
    // pStepper->setAcc_mm(acc);
    // pStepper->setTarget_mm(tar);

  } else if (mode == Comm_Mode::COMM_RUN_SPEED) {  // Mode: COMM_RUN_SPEED
    float spd = doc["Speed"];
    pStepper->setState(LinearStepper::RunMode::RUN_SPEED);
    if (pStepper->maxSpeed_mm() < spd)
      pStepper->setMaxSpeed_mm(spd);
    pStepper->setSpeed_mm(spd);

  } else if (mode == Comm_Mode::COMM_STATUS) {  // Mode: COMM_STATUS
    // auto stat = pStepper->getStatus();
    JsonDocument statusDoc = doc;
    statusDoc["Speed"] = pStepper->speed_mm();
    statusDoc["MaxSpeed"] = pStepper->maxSpeed_mm();
    statusDoc["Acceleration"] = pStepper->acceleration_mm();
    statusDoc["Target"] = pStepper->target_mm();
    statusDoc["Position"] = pStepper->positon_mm();
    serializeJson(statusDoc, Serial);
    Serial.println();

  } else if (mode == Comm_Mode::COMM_ZERO) { // Mode: COMM_ZERO
    pStepper->setZero();
  }
}