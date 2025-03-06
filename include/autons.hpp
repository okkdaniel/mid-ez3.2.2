#pragma once
#include "subsystems.hpp"

void default_constants();

void drive_example();
void turn_example();
void drive_and_turn();
void wait_until_change_speed();
void swing_example();
void motion_chaining();
void combining_movements();
void interfered_example();
void odom_drive_example();
void odom_pure_pursuit_example();
void odom_pure_pursuit_wait_until_example();
void odom_boomerang_example();
void odom_boomerang_injected_pure_pursuit_example();
void measure_offsets();


void redRight();
void redLeft();
void redRightGoalRush();

void blueRightGoal();
void blueLeftGoalRush();

void sortingTest();
void autoWith1010G();

void armTest();

inline void redLeft()
{
  // In terms of the center of the field
  
  // Odom coordinate set
  chassis.odom_xyt_set(-59_in, 13_in, -144_deg);
  
  // Alliance stake
  armTarget = 490;
  pros::delay(500);
  // Clamp goal
  chassis.pid_odom_set({{{-55_in, 18_in}, rev, 110},
    {{-32_in, 22_in, -60_deg}, rev, 100}}, true);
  pros::delay(700);
  armTarget = -120;
  
  chassis.pid_wait();
  pros::delay(200);
  clampControl(true);
  pros::delay(200);
  armMotor.tare_position();

  IntakeTargetSpeed = 127;


  chassis.pid_odom_set({{-18_in, 12_in}, rev, 110});
  chassis.pid_wait();
  chassis.pid_turn_set({-10_in,43.5_in}, fwd, 110, ez::shortest);
  chassis.pid_wait_quick();


 // Move to 8 ring stack and intake
  chassis.pid_odom_set({{-12_in, 44_in, 0_deg}, fwd, 80});
  chassis.pid_wait();
  chassis.pid_odom_set({{{-12_in, 60_in, 0_deg}, fwd, 30}}, true);
  chassis.pid_wait();
  chassis.pid_odom_set({{{-12_in, 35_in, -0_deg}, rev, 110},
  {{-23_in, 44_in, -45_deg}, fwd, 110}}, true);
  
  
// //   pros::delay(500);
// //   IntakeTargetSpeed = 0;
//   intakeControl(true);
//   // Doinker rings
//   chassis.pid_wait();
//   rightdoinkerControl(true);
//   chassis.pid_odom_set({{0_in, -48_in, 145_deg}, fwd, 90});
//   chassis.pid_wait();
//   leftdoinkerControl(true);

//   // Back away from middle and raise doinkers
//   chassis.pid_odom_set({{{15_in, -40_in, 135_deg}, rev, 110},
//     {{0_in, -23_in, 0_deg}, rev, 110}}, true);
//     chassis.pid_wait();
//   rightdoinkerControl(false);
//   leftdoinkerControl(false);
//   intakeControl(false);
//   pros::delay(200);

//   // Move to and intake double stack
//   chassis.pid_odom_set({{-27_in, -28_in, 245_deg}, fwd, 100});
//   IntakeTargetSpeed = 100;
//   chassis.pid_wait();
  
//   // Intake middle rings in line
//   chassis.pid_odom_set({{0_in, -28_in, 90_deg}, fwd, 100});
//   chassis.pid_wait();

//   // Go to corner
//   chassis.pid_odom_set({{-43_in, 6_in, -45_deg}, fwd, 80});
//   chassis.pid_wait();

//   // Intake corner ring and back away
//   pros::delay(200);
//   chassis.pid_odom_set(-10_in, 110, true);

}