// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"

#include <frc/shuffleboard/Shuffleboard.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <wpi/print.h>

#include <frc2/command/CommandScheduler.h>

Robot::Robot() {
  m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);

  m_turret.SetTargetLocation(10, 10);

  m_controller.Back().WhileTrue(m_turret.HomePosition());
  m_controller.Start().WhileTrue(m_turret.TrackTargetCmd());

  m_controller.AxisMagnitudeGreaterThan(4, 0.1).WhileTrue(m_turret.SetSpeed([this] { return m_controller.GetRightX(); }));
}

/**
 * This function is called every 20 ms, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic()
{
  frc2::CommandScheduler::GetInstance().Run();
  frc::SmartDashboard::PutNumber("Turret Angle", m_turret.GetAngle());
}

/**
 * This autonomous (along with the chooser code above) shows how to select
 * between different autonomous modes using the dashboard. The sendable chooser
 * code works with the Java SmartDashboard. If you prefer the LabVIEW Dashboard,
 * remove all of the chooser code and uncomment the GetString line to get the
 * auto name from the text box below the Gyro.
 *
 * You can add additional auto modes by adding additional comparisons to the
 * if-else structure below with additional strings. If using the SendableChooser
 * make sure to add them to the chooser code above as well.
 */
void Robot::AutonomousInit() {}

void Robot::AutonomousPeriodic() {
  double targetX = frc::SmartDashboard::GetNumber("Target X", m_turret.GetAngle());
  double targetY = frc::SmartDashboard::GetNumber("Target Y", m_turret.GetAngle());

  m_turret.SetTargetLocation(targetX, targetY);
  m_turret.Periodic();
}

void Robot::TeleopInit() {}

void Robot::TeleopPeriodic() {
  // double turretSpeed = m_controller.GetLeftX();
  // m_turret.SetSpeed(turretSpeed / 10.f);
}

void Robot::DisabledInit() {}

void Robot::DisabledPeriodic() {}

void Robot::TestInit() {}

void Robot::TestPeriodic() {}

void Robot::SimulationInit() {}

void Robot::SimulationPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif