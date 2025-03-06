#include "subsystems.hpp"
#include "main.h"
#include "pros/llemu.hpp"
#include "pros/optical.hpp"
#include <type_traits>

pros::Motor intakeMotor (5, pros::v5::MotorGears::blue);
pros::adi::DigitalOut clampPiston('A');
pros::adi::DigitalOut leftdoinker('B');
pros::adi::DigitalOut intakePiston('C');
pros::adi::DigitalOut rightdoinker('D');


pros::Controller master (pros::E_CONTROLLER_MASTER);
pros::Optical colorSensor(10);
bool sorting = false;

 
int armState = -1;

bool userWantsToPrime = false;

double armTarget = 0.0;

const double outtakeTimer = 200;
double timeSinceDetected = 0;
const int sortDelayTime = 70; // Delay before starting eject (in ms)

bool isBlueAlliance = true; // Default to Blue Alliance

double IntakeTargetSpeed = 0.0;





/* 
    Goals:
    - Intake Code
    - Arm Redirect Code
        - Stowed State
        - Primed State
        - Scoring State
    - Hook detect when ring is in redirect
        - Detect voltage spike
*/

using namespace pros;

void armTeleControl()
{

    bool userWantsToScore = master.get_digital(E_CONTROLLER_DIGITAL_L2);

    if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_L1))
    {
        userWantsToPrime = !userWantsToPrime;
    }

    if(userWantsToPrime == true)
    {
        if(userWantsToScore == true)
        {
            armState = armStates::SCORING;
        }
        else
        {
            armState = armStates::PRIMED;
        }
    }
    else
    {
        armState = armStates::STOWED;

    }

    // pros::lcd::print(4, "Arm State: %d", armState);
}

void setIntake(int speed) {    
    static uint32_t detectionTime = 0; // Stores when a ring was detected
    static bool ejecting = false; // Tracks if we're in the eject process

    if (sorting) {
        if (detectionTime == 0) { 
            detectionTime = pros::millis(); // Set the detection time
        }

        if (!ejecting && pros::millis() - detectionTime >= sortDelayTime) { 
            ejecting = true; // Start ejecting after the delay time
        }

        if (ejecting) {
            if (pros::millis() - detectionTime < outtakeTimer + sortDelayTime) { 
                intakeMotor.move_voltage(-2000);
            } else {
                sorting = false;
                detectionTime = 0; // Reset after sorting is done
                ejecting = false;
            }
        }
    } else {
        intakeMotor.move_voltage(speed * 120);
    }

   // pros::lcd::print(4, "Elapsed Time: %d", pros::millis() - detectionTime);
}

bool clampState = false;

void clampControl(bool state) 
{ 
    
    clampPiston.set_value(state); 
    
}

void clampTeleControl() {
  if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) {
    clampControl(true);
  }
  else if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)){
    clampControl(false); 
  }
}

void armControl(){

while(true)
    {
    double CurrentArm = armMotor.get_position();

    double error = armTarget - CurrentArm;

    double kP = .95;

    double Output = kP * error;

    // pros::lcd::print(4, "Arm Current: %lf ", CurrentArm);
    // pros::lcd::print(5, "Arm Target : %lf", armTarget);


    armMotor.move(Output);
    pros::delay(20);
    }


}

void armStateManager()
{
    if (armState == armStates::STOWED)
    {
        armTarget = armPositions::STOWED;
    }
    else if (armState == PRIMED)
    {   
        armTarget = armPositions::PRIMED;

    }   
    else if (armState == armStates::SCORING)
    {
        armTarget = armPositions::SCORING;   
    }
}

void leftdoinkerTeleControl()
{
    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)){
        leftdoinker.set_value(true);
    }
    else if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP)){
        leftdoinker.set_value(false);
    }
}

void leftdoinkerControl(bool state)
{
    leftdoinker.set_value(state);
}


void rightdoinkerControl(bool state)
{
    rightdoinker.set_value(state);
}

void intakeControl(bool state)
{
    intakePiston.set_value(state);
}


void intakeTeleControl()
{
    IntakeTargetSpeed = ((master.get_digital(E_CONTROLLER_DIGITAL_R1) - master.get_digital(E_CONTROLLER_DIGITAL_R2)) * 127);
}

void toggleAlliance() {
        isBlueAlliance = !isBlueAlliance; // Toggle between Red and Blue Alliance
}

void detectRing()
{
    while (true)
    {

        int prox = colorSensor.get_proximity();
        int hue = colorSensor.get_hue();
        const int proxThreshold = 30;

            pros::lcd::print(7, "Alliance: %s", isBlueAlliance ? "Blue" : "Red");


        int minHue = isBlueAlliance ? 0 : 200; // <- real numbers
        int maxHue = isBlueAlliance ? 30 : 230; // <- real numbers

        //pros::lcd::print(7, "prox : %d \n", prox);

        if (prox > proxThreshold && (hue >= minHue && hue <= maxHue))
        {
            sorting = true;
            pros::lcd::print(6, "Sorting %s Ring", isBlueAlliance ? "Blue" : "Red");
        }
        else
        {
            //sorting = false;
            pros::lcd::print(6, "No Ring Detected");
        }

        pros::delay(10);
    }
}

void AutoIntake(){
 while (true) {
        setIntake(IntakeTargetSpeed);
        pros::delay(10);
    } 
}