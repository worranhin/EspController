#ifndef LINEAR_STEPPER_H
#define LINEAR_STEPPER_H

#include <AccelStepper.h>
#include "CmdCode.h"

class LinearStepper : public AccelStepper {
 public:
  enum RunMode { RUN, RUN_SPEED } runMode;

  LinearStepper(uint8_t step,
                uint8_t dir,
                uint ms = 1,
                uint travel = 20,
                uint spr = 200,
                uint spm = 200);
  ~LinearStepper(){};
  void setZero();
  void setSpeed_mm(float speed);
  void setMaxSpeed_mm(float speed);
  void setAcc_mm(float acc);
  void setTarget_mm(float target);
  void setState(RunMode s);
  void setMs(int ms);
  void moveTo_mm(float x);
  float speed_mm();
  float maxSpeed_mm();
  float acceleration_mm();
  float target_mm();
  float positon_mm();
  void routine();

 private:
  unsigned int _travel;  // 电机行程 (mm)
  unsigned int _SPR;     // steps per revolution
  unsigned int _SPM;     // steps per mm
  unsigned int _ms;      // micro steps
  uint8_t _stepPin;
  uint8_t _dirPin;
};

#endif