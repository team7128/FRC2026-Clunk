#pragma once

#include "Constants.h"

#include <frc2/command/CommandPtr.h>
#include <frc2/command/SubsystemBase.h>
#include <ctre/phoenix/motorcontrol/can/WPI_VictorSPX.h>

class Intake : public frc2::SubsystemBase {
    private:
    ctre::phoenix::motorcontrol::can::WPI_VictorSPX m_motor{IntakeConstants::kVictorID};

    public:
    Intake();

    void SetSpeed(double speed);
    frc2::CommandPtr SetSpeedCmd(std::function<float()> speed);
};