#include "LinearStepper.h"

LinearStepper::LinearStepper(uint8_t step,
                             uint8_t dir,
                             uint ms = 1,
                             bool revertDir = false,
                             uint travel = 20,
                             uint spr = 200,
                             uint spm = 200)
    : AccelStepper(DRIVER, step, dir),
      _stepPin(step),
      _dirPin(dir),
      _ms(ms),
      _travel(travel),
      _SPR(spr),
      _SPM(spm) {
  _position = 0;
  _direction = revertDir ? -1 : 1;
};

LinearStepper::Status LinearStepper::getStatus() {
  long pos = currentPosition();
  float spd = speed();
  float acc = acceleration();
  long tar = targetPosition();
  long dis = distanceToGo();
  Status s = {pos, spd, acc, tar, dis};
  return s;
}

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

void LinearStepper::setState(State s) {
  state = s;
}

void LinearStepper::setMs(int ms) {
  _ms = ms;
}

void LinearStepper::moveTo_mm(uint8_t x) {
  moveTo(x * _SPM * _ms);
}

void LinearStepper::routine() {
  switch (state) {
    case STOP:
      stop();
      break;

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