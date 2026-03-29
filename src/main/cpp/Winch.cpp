#include "Winch.h"
#include "Constants.h"

#include <frc2/command/Commands.h>
#include <frc2/command/CommandPtr.h>

using namespace ctre::phoenix::motorcontrol;

Winch::Winch() :
    m_motorLeft(IDConstants::kTalonWinchLeft),
    m_motorRight(IDConstants::kTalonWinchRight),
    m_limitswitch(WinchConstants::kLimitSwitchID)
{
    m_motorRight.Follow(m_motorLeft);

    m_motorLeft.SetNeutralMode(NeutralMode::Brake);
    m_motorRight.SetNeutralMode(NeutralMode::Brake);
    m_motorLeft.SetInverted(InvertType::None);
    m_motorRight.SetInverted(InvertType::OpposeMaster);

    SetDefaultCommand(StopCmd());
}

frc2::CommandPtr Winch::Lift() {
    return this->RunCmd(1.0)
        .WithTimeout(WinchConstants::kLiftTime);
}

frc2::CommandPtr Winch::Lower() {
    return this->RunCmd(-1.0)
    .Until([this] { return !m_limitswitch.Get(); });
}

frc2::CommandPtr Winch::RunCmd(float speed) {
    return this->Run([this, speed] { m_motorLeft.Set(ControlMode::PercentOutput, speed); });
}

frc2::CommandPtr Winch::StopCmd()
{
    return this->Run([this] { m_motorLeft.Set(ControlMode::Disabled, 0); });
}