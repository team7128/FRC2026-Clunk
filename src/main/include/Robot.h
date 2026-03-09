#pragma once

#include <frc/TimedRobot.h>
#include <frc2/command/CommandPtr.h>
#include "Drivebase.h"
#include "Odometry.h"

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
    Drivebase m_drivebase;
    Odometry m_odometry;
};