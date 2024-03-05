#include <AccelStepper.h>
#include <Arduino.h>
#include <ArduinoJson.h>
#include "CmdCode.h"
#include "Communication.h"
#include "ErrorCode.h"
#include "LinearStepper.h"
#include "pinConfig.h"

// int incomingByte = 0; // 用于存储串口接收的消息
// AccelStepper stepper(AccelStepper::DRIVER, stepPin1, dirPin1);
LinearStepper stepper1(stepPin1, dirPin1);
LinearStepper stepper2(stepPin2, dirPin2);
LinearStepper stepper3(stepPin3, dirPin3);
LinearStepper stepper4(stepPin4, dirPin4);
LinearStepper* deviceList[] = {&stepper1, &stepper2, &stepper3, &stepper4};

// put function declarations here:
void communicateRoutine();
void handleCommand(uint8_t cmd, uint8_t data);

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  while (!Serial)
    ;

  Serial.println("Esp setup done!");
}

void loop() {
  // put your main code here, to run repeatedly:
  stepper1.routine();
  communicateRoutine();
}

// put function definitions here:

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

  // 根据 mode 的值，做出相应的行为

  if (mode == Comm_Mode::COMM_STOP) {  // Mode: COMM_STOP
    if (stepper1.runMode == LinearStepper::RUN)
      stepper1.stop();
    else if (stepper1.runMode == LinearStepper::RUN_SPEED)
      stepper1.setSpeed_mm(0.0);

  } else if (mode == Comm_Mode::COMM_RUN) {  // Mode: COMM_RUN
    float mspd = doc["MaxSpeed"];
    float acc = doc["Acceleration"];
    float tar = doc["Target"];
    stepper1.setState(LinearStepper::RunMode::RUN);
    stepper1.setMaxSpeed_mm(mspd);
    stepper1.setAcc_mm(acc);
    stepper1.setTarget_mm(tar);

  } else if (mode == Comm_Mode::COMM_RUN_SPEED) {  // Mode: COMM_RUN_SPEED
    float spd = doc["Speed"];
    stepper1.setState(LinearStepper::RunMode::RUN_SPEED);
    if (stepper1.maxSpeed_mm() < spd)
      stepper1.setMaxSpeed_mm(spd);
    stepper1.setSpeed_mm(spd);

  } else if (mode == Comm_Mode::COMM_STATUS) {  // Mode: COMM_STATUS
    // auto stat = stepper1.getStatus();
    JsonDocument statusDoc = doc;
    statusDoc["Speed"] = stepper1.speed_mm();
    statusDoc["MaxSpeed"] = stepper1.maxSpeed_mm();
    statusDoc["Acceleration"] = stepper1.acceleration_mm();
    statusDoc["Target"] = stepper1.target_mm();
    statusDoc["Position"] = stepper1.positon_mm();
    serializeJson(statusDoc, Serial);
    Serial.println();
  }
}