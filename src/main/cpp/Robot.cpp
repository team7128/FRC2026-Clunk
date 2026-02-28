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
  frc::SmartDashboard::PutNumber("Intake Speed", 0);

  m_turret.SetTargetLocation(10, 10);

  m_controller.Back().WhileTrue(m_turret.HomePosition());
  m_controller.Start().WhileTrue(m_turret.TrackTargetCmd());
  m_controller.LeftBumper().WhileTrue(m_intake.SetSpeedCmd( [] { return 0.8; }));
  m_controller.RightBumper().WhileTrue(m_indexer.SetSpeedCmd( [] { return 1; }));
  m_controller.A().WhileTrue(m_shooter.SetSpeedCmd( [] { return 0.2; }));

  m_controller.AxisMagnitudeGreaterThan(4, 0.1).WhileTrue(m_turret.SetSpeedCmd([this] { return m_controller.GetRightX(); }));
}

void Robot::RobotPeriodic()
{
  frc2::CommandScheduler::GetInstance().Run();
  frc::SmartDashboard::PutNumber("Turret Angle", m_turret.GetAngle());
}

void Robot::AutonomousInit() {
  m_autoSelected = m_chooser.GetSelected();
  // m_autoSelected = SmartDashboard::GetString("Auto Selector",
  //     kAutoNameDefault);
  wpi::print("Auto selected: {}\n", m_autoSelected);

  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
  }
}

void Robot::AutonomousPeriodic() {
  double targetX = frc::SmartDashboard::GetNumber("Target X", m_turret.GetAngle());
  double targetY = frc::SmartDashboard::GetNumber("Target Y", m_turret.GetAngle());

  m_turret.SetTargetLocation(targetX, targetY);
  m_turret.Periodic();
}

void Robot::TeleopInit() {}

void Robot::TeleopPeriodic() {}

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