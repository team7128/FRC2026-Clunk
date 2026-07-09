#include "Winch.h"
#include "Constants.h"

#include <frc2/command/Commands.h>
#include <frc2/command/CommandPtr.h>

using namespace ctre::phoenix::motorcontrol;

Winch::Winch() :
    m_motor(IDConstants::kVictorLift),
    m_limitswitch(WinchConstants::kLimitSwitchID)
{

    m_motor.SetNeutralMode(NeutralMode::Brake);
    m_motor.SetInverted(InvertType::None);

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
    return this->Run([this, speed] { m_motor.Set(ControlMode::PercentOutput, speed); });
}

frc2::CommandPtr Winch::StopCmd()
{
    return this->Run([this] { m_motor.Set(ControlMode::Disabled, 0); });
}