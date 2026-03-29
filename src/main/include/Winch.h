#pragma once

#include "Constants.h"

#include <frc2/command/CommandPtr.h>
#include <frc2/command/SubsystemBase.h>

#include <ctre/phoenix/motorcontrol/can/WPI_VictorSPX.h>
#include <ctre/phoenix/motorcontrol/can/WPI_TalonSRX.h>
#include <frc/DigitalInput.h>

class Winch : public frc2::SubsystemBase {
    private:
    ctre::phoenix::motorcontrol::can::TalonSRX m_motorLeft, m_motorRight;
    frc::DigitalInput m_limitswitch;

    public:
    Winch();

    frc2::CommandPtr Lift();
    frc2::CommandPtr Lower();

    frc2::CommandPtr RunCmd(float speed);
    frc2::CommandPtr StopCmd();
};