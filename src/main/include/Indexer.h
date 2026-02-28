#pragma once

#include <frc2/command/CommandPtr.h>
#include <frc2/command/SubsystemBase.h>
#include <ctre/phoenix/motorcontrol/can/WPI_VictorSPX.h>

class Indexer : public frc2::SubsystemBase {
    private:
    ctre::phoenix::motorcontrol::can::WPI_VictorSPX m_motorIndex{2};
    ctre::phoenix::motorcontrol::can::WPI_VictorSPX m_motorConveyor{3};

    public:
    Indexer();

    void SetSpeed(double speed);
    frc2::CommandPtr SetSpeedCmd(double speed);
};