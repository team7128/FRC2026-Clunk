#pragma once

#include "Constants.h"

#include <frc2/command/CommandPtr.h>
#include <frc2/command/SubsystemBase.h>

#include <ctre/phoenix/motorcontrol/can/WPI_VictorSPX.h>
#include <frc/DigitalInput.h>

class Winch : public frc2::SubsystemBase {
    private:
    ctre::phoenix::motorcontrol::can::WPI_VictorSPX m_motor{WinchConstants::kSparkID};
    frc::DigitalInput m_limitswitch{WinchConstants::kLimitSwitchID};

    public:
    Winch();

    frc2::CommandPtr Lift();
    frc2::CommandPtr Lower();
};