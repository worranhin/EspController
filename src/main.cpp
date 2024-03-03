#include <AccelStepper.h>
#include <Arduino.h>
#include <ArduinoJson.h>
#include "CmdCode.h"
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
  if (Serial.available() > 1) {
    // read the incoming byte:
    // incomingByte = Serial.read();

    uint8_t inBytes[2];
    Serial.readBytes(inBytes, 2);

    // say what you got:
    // Serial.println("I received: ");
    // Serial.println(inBytes[0], HEX);
    // Serial.println(inBytes[1], HEX);

    handleCommand(inBytes[0], inBytes[1]);
  }
}

void handleCommand(uint8_t cmd, uint8_t data) {
  uint8_t cmdType = cmd & 0x0f;
  uint8_t deviceId = (cmd & 0xf0) >> 4;
  Serial.write(cmd);

  // 检查设备码合法性
  if (deviceId < 1 || deviceId > (sizeof(deviceList) / sizeof(deviceList[0]))) {
    Serial.write((int)ErrorCode::ERRCODE_DEVICE_ID);
    return;
  } else {
    Serial.write((int)ErrorCode::ERRCODE_OK);
  }

  LinearStepper* lStepper = (LinearStepper*)deviceList[deviceId - 1];
  JsonDocument doc;
  LinearStepper::Status stat;

  switch (cmdType) {
    case CmdCode::E_STOP:
      // 紧急停止
      lStepper->stop();
      break;

    case CmdCode::GET_STATUS:
      // print the status to serial
      stat = lStepper->getStatus();
      doc["position"] = stat.position;
      doc["speed"] = stat.speed;
      doc["acceleration"] = stat.acceleration;
      doc["target"] = stat.target;
      serializeJson(doc, Serial);
      Serial.println("");
      break;

    case CmdCode::SET_ZERO:
      // set the current location as zero
      lStepper->setZero();
      break;

    case CmdCode::SET_TAR:
      // TODO: set the target
      break;

    case CmdCode::SET_SPEED:
      // set the speed
      lStepper->setSpeed_mm(data);
      lStepper->setMaxSpeed_mm(data);
      break;

    case CmdCode::SET_ACC:
      // set the acceleration
      lStepper->setAcc_mm(data);
      break;

    case CmdCode::CTRL_RUN:
      // let the motor run
      lStepper->setState(LinearStepper::RUN_SPEED);
      break;

    case CmdCode::CTRL_STOP:
      // stop the motor
      lStepper->stop();
      lStepper->setState(LinearStepper::STOP);
      break;

    case CmdCode::CTRL_GO_MM:
      // control the motor to go x mm
      lStepper->moveTo_mm(data);
      break;

    case CmdCode::CTRL_GO_ZERO:
      // cotrol the motor to go to zero position
      lStepper->moveTo_mm(0);
      break;

    default:
      break;
  }
}
