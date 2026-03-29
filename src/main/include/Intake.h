#pragma once

#include "Constants.h"

#include <frc2/command/CommandPtr.h>
#include <frc2/command/SubsystemBase.h>
#include <ctre/phoenix/motorcontrol/can/VictorSPX.h>

class Intake : public frc2::SubsystemBase {
    private:
    ctre::phoenix::motorcontrol::can::VictorSPX m_motor;

    public:
    Intake();

    frc2::CommandPtr RunCmd(std::function<float()> speed);
    frc2::CommandPtr StopCmd();
};