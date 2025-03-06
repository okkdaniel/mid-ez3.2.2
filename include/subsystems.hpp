#pragma once

#include "EZ-Template/api.hpp"
#include "api.h"

extern Drive chassis;

// Your motors, sensors, etc. should go here.  Below are examples

// inline pros::Motor intake(1);
// inline pros::adi::DigitalIn limit_switch('A');

static int armVelocity = 100;
static double stoppedThreshold = 1600; // milliamps

extern double armTarget;

static int armControlVoltage = 12000;
extern bool armInitializing;
extern int armState;


enum armStates
{
    STOWED = 0,
    PRIMED = 1,
    SCORING = 2,
    AUTOWS = 3,
    LIFTED = 4
};

namespace armPositions
{
    static double STOWED = 0;
    static double PRIMED = 125;
    static double SCORING = 500;
    static double AUTOWS = 800;
    static double LIFTED = 275;

}

extern pros::Optical colorSensor;
inline pros::Motor armMotor(-9, pros::v5::MotorGears::green, pros::v5::MotorUnits::degrees); 

extern bool sorting;
extern double IntakeTargetSpeed;

// Autonomous functions
void initializeArm();
void intakeManager();
void armControl();
void armStateManager();
void setArm(double state);
void clampControl(bool state);
void leftdoinkerControl(bool state);
void rightdoinkerControl(bool state);
void intakeControl(bool state);

//TeleOp functions
void armTeleControl();
void intakeTeleControl();
void clampTeleControl();
void leftdoinkerTeleControl();
void detectRing();
void toggleAlliance();
//task
void checkJam_fn(void* param);

void AutoIntake();

bool detectBlueRing();