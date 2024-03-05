#include "LinearStepper.h"

LinearStepper::LinearStepper(uint8_t step,
                             uint8_t dir,
                             uint ms,
                             uint travel,
                             uint spr,
                             uint spm)
    : AccelStepper(DRIVER, step, dir),
      _stepPin(step),
      _dirPin(dir),
      _ms(ms),
      _travel(travel),
      _SPR(spr),
      _SPM(spm) {
  _position = 0;
  runMode = RUN;
};

void LinearStepper::setZero() {
  setCurrentPosition(0);
  _position = 0;
}

void LinearStepper::setSpeed_mm(float speed) {
  setSpeed(speed * _SPM * _ms);
}

void LinearStepper::setMaxSpeed_mm(float speed) {
  setMaxSpeed(speed * _SPM * _ms);
}

void LinearStepper::setAcc_mm(float acc) {
  setAcceleration(acc * _SPM * _ms);
}

void LinearStepper::setTarget_mm(float target) {
  moveTo_mm(target);
}

void LinearStepper::setState(RunMode s) {
  runMode = s;
}

void LinearStepper::setMs(int ms) {
  _ms = ms;
}

void LinearStepper::moveTo_mm(float x) {
  moveTo(x * _SPM * _ms);
}

float LinearStepper::speed_mm() {
  return speed() / _SPM / _ms;
}

float LinearStepper::maxSpeed_mm() {
  return maxSpeed() / _SPM / _ms;
}

float LinearStepper::acceleration_mm() {
  return acceleration() / _SPM / _ms;
}

float LinearStepper::target_mm() {
  return (double)targetPosition() / _SPM / _ms;
}

float LinearStepper::positon_mm() {
  return (double)currentPosition() / _SPM / _ms;
}

void LinearStepper::routine() {
  switch (runMode) {
    case RUN_SPEED:
      runSpeed();
      break;

    case RUN:
      run();
      break;

    default:
      break;
  }
}