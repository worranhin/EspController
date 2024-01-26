#ifndef LINEAR_STEPPER_H
#define LINEAR_STEPPER_H

#include "CmdCode.h"
#include <AccelStepper.h>

class LinearStepper : public AccelStepper {
public:
  enum State {
    STOP,
    RUN,
    RUN_SPEED
  } state;

  struct Status {
    long position;
    float speed;
    float acceleration;
    long target;
    long distance;
  };

  LinearStepper(uint8_t step, uint8_t dir, uint ms = 1, bool revertDir = false,
                uint travel = 20, uint spr = 200, uint spm = 200);
  ~LinearStepper(){};
  Status getStatus();
  void setZero();
  void setSpeed_mm(float speed);
  void setMaxSpeed_mm(float speed);
  void setAcc_mm(float acc);
  void setState(State s);
  void setMs(int ms);
  void moveTo_mm(uint8_t x);
  void routine();

private:
  int _position;        // mm
  unsigned int _travel; // 电机行程 (mm)
  unsigned int _SPR;    // steps per revolution
  unsigned int _SPM;    // steps per mm
  unsigned int _ms;     // micro steps
  uint8_t _stepPin;
  uint8_t _dirPin;
  int _direction = 1;
};

#endif