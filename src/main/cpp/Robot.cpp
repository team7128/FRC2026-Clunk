// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"
#include "Constants.h"

#include <frc/shuffleboard/Shuffleboard.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <wpi/print.h>

#include <frc2/command/CommandScheduler.h>

Robot::Robot() :
  m_odometry([this] { return m_drivebase.GetLeftDistance(); }, [this] { return m_drivebase.GetRightDistance(); }, [this] { return units::degree_t(m_turret.GetAngle()); })
{
  m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);
  frc::SmartDashboard::PutNumber("Intake Speed", 0);

  m_turret.SetTargetLocation(RobotConstants::kTargetX, RobotConstants::kTargetY);

  m_drivebase.SetDefaultCommand(m_drivebase.ArcadeDriveCmd(
		[this] { return -m_driveController.GetLeftY() * RobotConstants::kForwardMultiplier; },
		[this] { return -m_driveController.GetRightX() * RobotConstants::kTurnMultiplier; }
	));

  m_driveController.Y().WhileTrue(m_intake.SetSpeedCmd( [] { return RobotConstants::kIntakeSpeed; }));
  m_driveController.A().OnTrue(m_winch.Lift());
  m_driveController.B().OnTrue(m_winch.Lower());

  m_shootController.Back().WhileTrue(m_turret.HomePosition());
  m_shootController.Start().WhileTrue(m_turret.TrackTargetCmd());
  m_shootController.LeftBumper().WhileTrue(m_indexer.SetSpeedCmd( [] { return RobotConstants::kIndexerSpeed; }));
  
  m_shootController.X().WhileTrue(m_shooter.SetSpeedCmd( [] { return RobotConstants::kHubShooterSpeed; }));

  m_shootController.Y().WhileTrue(m_shooter.SetSpeedCmd( [] { return RobotConstants::kPassShooterSpeed; }));

  m_shootController.A().WhileTrue(Sequences::RunHubShooterSystem(&m_shooter, &m_turret, &m_indexer));
  m_shootController.B().WhileTrue(Sequences::RunPassShooterSystem(&m_shooter, &m_turret, &m_indexer));

  m_shootController.AxisMagnitudeGreaterThan(RobotConstants::kTurretAxis, RobotConstants::kTurretThreshold).WhileTrue(m_turret.SetSpeedCmd([this] { return m_driveController.GetRightX(); }));

  if (!(m_shootController.A().Get()) && !(m_shootController.B().Get()) && !(m_shootController.X().Get()) && !(m_shootController.Y().Get())) {
    Sequences::StopShooterSystem(&m_shooter, &m_indexer);
  }
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
  
  if (m_shootController.LeftStick().Get()) {
    m_shooter.SetSpeed(m_shooter.CalculateSpeed(targetX, targetY));
  } else {
    m_shooter.SetSpeed(0);
  }

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