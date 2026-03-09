#pragma once

#include "Turret.h"
#include "Intake.h"
#include "Shooter.h"
#include "Indexer.h"
#include "Winch.h"
#include "Constants.h"
#include "Drivebase.h"
#include "Odometry.h"

#include <string>
#include <frc/XboxController.h>
#include <frc/TimedRobot.h>
#include <frc/smartdashboard/SendableChooser.h>
#include <frc2/command/button/CommandXboxController.h>
#include <frc2/command/CommandPtr.h>

class Robot : public frc::TimedRobot {
public:
    Robot();
    void RobotInit() override;
    void RobotPeriodic() override;
    void AutonomousInit() override;
    void AutonomousPeriodic() override;
    void TeleopInit() override;
    void TeleopPeriodic() override;
    void DisabledInit() override;
    void DisabledPeriodic() override;
    void TestInit() override;
    void TestPeriodic() override;
    void SimulationInit() override;
    void SimulationPeriodic() override;

 private:
  frc::SendableChooser<std::string> m_chooser;
  const std::string kAutoNameDefault = "Default";
  const std::string kAutoNameCustom = "My Auto";
  std::string m_autoSelected;
  frc2::CommandXboxController m_controller{RobotConstants::kControllerID};
  Turret m_turret;
  Intake m_intake;
  Shooter m_shooter;
  Indexer m_indexer;
  Winch m_winch;
  Drivebase m_drivebase;
  Odometry m_odometry;
};
