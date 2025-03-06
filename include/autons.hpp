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
  armMotor.tare_position();
  // Odom coordinate set; relative to center of field
  chassis.odom_xyt_set(-59_in, 13_in, -144_deg);
  
  // Alliance stake
  armTarget = 490;
  pros::delay(400);

  // Clamp goal
  chassis.pid_odom_set({{{-55_in, 18_in}, rev, 110},
    {{-32_in, 22_in, -60_deg}, rev, 100}}, true);
  chassis.pid_wait_until_point({-55_in, 18_in});
  armTarget = -250;
  chassis.pid_wait();
  pros::delay(25);
  clampControl(true);
  pros::delay(25);
  armMotor.tare_position();
  armTarget = 0;
  
  // Move to 8 ring stack and intake
  //chassis.pid_odom_set({{-16_in, 8_in}, rev, 110});
  chassis.pid_wait();
  chassis.pid_turn_set({-1_in,36_in}, fwd, 110, ez::shortest);
  chassis.pid_wait_quick();
  IntakeTargetSpeed = 127;
  chassis.pid_odom_set({{-14_in, 41_in, 0_deg}, fwd, 110});
  chassis.pid_wait();
  chassis.pid_odom_set({{{-14_in, 56_in, 0_deg}, fwd, 50}}, true);
  chassis.pid_wait_quick();
  

  // Move to 2 ring stack and intake
  chassis.pid_odom_set({{-14_in, 48_in, -0_deg}, rev, 110});
  chassis.pid_wait_quick();
  chassis.pid_turn_set({-20_in,48_in}, fwd, 110, ez::shortest);
  chassis.pid_wait_quick();
  chassis.pid_odom_set({{-20_in, 48_in, -90_deg}, fwd, 90});
  chassis.pid_wait();


  // Move to negative corner and intake bottom ring
  chassis.pid_odom_set({{{-52_in, 52_in, -45_deg}, fwd, 110},
    {{-65_in, 65_in, -45_deg}, fwd, 110}}, true);
  chassis.pid_wait_quick();

  // Intake first ring
  pros::delay(200);
  chassis.pid_odom_set({{-61_in, 61_in, -45_deg}, rev, 100});
  chassis.pid_wait();

  // Intake second ring
  pros::delay(400);
  intakeControl(true);
  pros::delay(100);
  chassis.pid_odom_set({{-64_in, 64_in, -45_deg}, fwd, 90});
  chassis.pid_wait();
  pros::delay(200);  
  // Go to tower
  chassis.pid_odom_set({{-14_in, 16_in, -50_deg}, rev, 127}, true);
  pros::delay(100);  
  intakeControl(false);

}