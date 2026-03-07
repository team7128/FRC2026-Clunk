#include "Robot.h"
#include <frc2/command/CommandScheduler.h>

void Robot::RobotInit() {
}

void Robot::RobotPeriodic() {
  frc2::CommandScheduler::GetInstance().Run();
}

void Robot::AutonomousInit() {
}

void Robot::AutonomousPeriodic() {
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