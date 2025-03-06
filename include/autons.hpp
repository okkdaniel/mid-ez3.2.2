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
  armTarget = 200;
  chassis.pid_wait();
  pros::delay(25);
  clampControl(true);
  pros::delay(25);

  
  // Move to 8 ring stack and intake
  //chassis.pid_odom_set({{-16_in, 8_in}, rev, 110});
  chassis.pid_wait();
  chassis.pid_turn_set({-1_in,36_in}, fwd, 110, ez::shortest);
  chassis.pid_wait_quick();
  IntakeTargetSpeed = 127;
  chassis.pid_odom_set({{-14_in, 41_in, 0_deg}, fwd, 110});
  chassis.pid_wait();
  chassis.pid_odom_set({{{-14_in, 52_in, 0_deg}, fwd, 50}}, true);
  chassis.pid_wait_quick();
  

  // Move to 2 ring stack and intake
  chassis.pid_odom_set({{-14_in, 48_in, -0_deg}, rev, 110});
  chassis.pid_wait_quick();
  chassis.pid_turn_set({-20_in,48_in}, fwd, 110, ez::shortest);
  chassis.pid_wait_quick();
  chassis.pid_odom_set({{-20_in, 48_in, -90_deg}, fwd, 90});
  chassis.pid_wait();

  armTarget = -250;


  // Move to negative corner and intake bottom ring
  chassis.pid_odom_set({{{-52_in, 52_in, -45_deg}, fwd, 110},
    {{-65_in, 65_in, -45_deg}, fwd, 110}}, true);
  chassis.pid_wait_quick();
  armMotor.tare_position();
  armTarget = 0;

  // Intake first ring
  pros::delay(200);
  chassis.pid_odom_set({{-59_in, 59_in, -45_deg}, rev, 100});
  chassis.pid_wait();

  // Intake second ring
  pros::delay(400);
  intakeControl(true);
  pros::delay(100);
  chassis.pid_odom_set({{-63_in, 63_in, -45_deg}, fwd, 90});
  chassis.pid_wait();
  pros::delay(200);  
  // Go to tower
  chassis.pid_odom_set({{-14_in, 16_in, -50_deg}, rev, 127}, true);
  armTarget = 150;
  pros::delay(200);  
  intakeControl(false);

}

inline void redRight()
{
  // Odom coordinate set; relative to center of field
  chassis.odom_xyt_set(-55_in, -11_in, -90_deg);
  
  // Drive to side of goal
  chassis.pid_odom_set({{{-31_in, -20_in, -60_deg}, rev, 110}}, true);
  chassis.pid_wait();


  // Clamp goal
  pros::delay(25);
  clampControl(true);
  pros::delay(100);

  // Move to middle ring position
  intakeControl(true);
  chassis.pid_turn_set({3_in,4_in}, fwd, 110, ez::shortest);
  chassis.pid_wait();
  chassis.pid_odom_set({{{-12_in, -7_in, 60_deg}, fwd, 110}}, true);
  // Raise intake
  chassis.pid_wait();

  // Doinker rings
  rightdoinkerControl(true);
  pros::delay(100);
  chassis.pid_turn_set({6_in,-4_in}, fwd, 110, ez::shortest);
  chassis.pid_wait();

  leftdoinkerControl(true);
  pros::delay(100);

  // Back away from middle and raise doinkers
  chassis.pid_odom_set({{{-23_in, -20_in}, rev, 110},
    {{-44_in, -30_in, 90_deg}, rev, 110}}, true);
  pros::delay(2000);
  rightdoinkerControl(false);
  leftdoinkerControl(false);
  chassis.pid_wait_quick();
  intakeControl(false);
  IntakeTargetSpeed = 100;
  //pros::delay(150);

  // Move to and intake double stack
  chassis.pid_odom_set({{-26_in, -24_in, 90_deg}, fwd, 110});
  IntakeTargetSpeed = 100;
  chassis.pid_wait();
  
  // Intake middle rings in line
  chassis.pid_turn_set({-26_in,-50_in}, fwd, 110, ez::shortest);
  chassis.pid_wait_quick();
  chassis.pid_odom_set({{-26_in, -50_in, 180_deg}, fwd, 110});
  chassis.pid_wait_quick();

  // Go to corner
  chassis.pid_turn_set({-51_in,-50_in}, fwd, 110, ez::shortest);
  chassis.pid_wait_quick();
  chassis.pid_odom_set({{-51_in, -50_in, -90_deg}, fwd, 110});
  chassis.pid_wait();
  
  // Intake ring
  chassis.pid_odom_set({{-64_in, -64_in, -135_deg}, fwd, 110});
  chassis.pid_wait();
  pros::delay(100);
  chassis.pid_odom_set({{-60_in, -60_in, -135_deg}, rev, 100});
  chassis.pid_wait();

  // Intake second ring
  pros::delay(200);
  intakeControl(true);
  //pros::delay(100);
  chassis.pid_odom_set({{-64_in, -64_in, -135_deg}, fwd, 100});
  chassis.pid_wait();
  pros::delay(200);
  intakeControl(false);
  chassis.pid_odom_set({{-58_in, -58_in, -135_deg}, rev, 127});


}
