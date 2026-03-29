#include "Intake.h"

using namespace ctre::phoenix::motorcontrol;

Intake::Intake() :
    m_motor(IDConstants::kVictorIntake)
{
    m_motor.SetNeutralMode(NeutralMode::Brake);
    m_motor.SetInverted(InvertType::None);

    SetDefaultCommand(StopCmd());
}

frc2::CommandPtr Intake::RunCmd(std::function<float()> speed) {
    return this->Run([this, speed] { m_motor.Set(ControlMode::PercentOutput, speed()); });
}

frc2::CommandPtr Intake::StopCmd()
{
    return this->Run([this] { m_motor.Set(ControlMode::Disabled, 0); });
}