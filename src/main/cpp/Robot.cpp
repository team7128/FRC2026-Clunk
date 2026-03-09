#include "Robot.h"
#include "Constants.h"

#include <frc/shuffleboard/Shuffleboard.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <wpi/print.h>

#include <frc2/command/CommandScheduler.h>

Robot::Robot() :
  m_odometry([this] { return m_drivebase.GetLeftDistance(); }, [this] { return m_drivebase.GetRightDistance(); })
{
  m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);
  frc::SmartDashboard::PutNumber("Intake Speed", 0);

  m_turret.SetTargetLocation(RobotConstants::kTargetX, RobotConstants::kTargetY);

  m_controller.Back().WhileTrue(m_turret.HomePosition());
  m_controller.Start().WhileTrue(m_turret.TrackTargetCmd());
  m_controller.LeftBumper().WhileTrue(m_intake.SetSpeedCmd( [] { return RobotConstants::kIntakeSpeed; }));
  m_controller.RightBumper().WhileTrue(m_indexer.SetSpeedCmd( [] { return RobotConstants::kIndexerSpeed; }));
  m_controller.A().WhileTrue(m_shooter.SetSpeedCmd( [] { return RobotConstants::kShooterSpeed; }));
  m_controller.Y().OnTrue(m_winch.Lift());
  m_controller.Y().OnFalse(m_winch.Lower());

  m_controller.AxisMagnitudeGreaterThan(RobotConstants::kTurretAxis, RobotConstants::kTurretThreshold).WhileTrue(m_turret.SetSpeedCmd([this] { return m_controller.GetRightX(); }));
};

void Robot::RobotPeriodic() {
  frc2::CommandScheduler::GetInstance().Run();
}

void Robot::AutonomousInit() {
}

void Robot::AutonomousPeriodic() {
  double targetX = frc::SmartDashboard::GetNumber("Target X", m_turret.GetAngle());
  double targetY = frc::SmartDashboard::GetNumber("Target Y", m_turret.GetAngle());
  
  if (m_controller.B().Get()) {
    m_shooter.SetSpeed(m_shooter.CalculateSpeed(targetX, targetY));
  } else {
    m_shooter.SetSpeed(0);
  }

  m_turret.SetTargetLocation(targetX, targetY);
  m_turret.Periodic();
}

void Robot::TeleopInit() {
}

void Robot::TeleopPeriodic() {
}

void Robot::DisabledInit() {
}

void Robot::DisabledPeriodic() {
}

void Robot::TestInit() {
}

void Robot::TestPeriodic() {
}

void Robot::SimulationInit() {
}

void Robot::SimulationPeriodic() {
}

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif