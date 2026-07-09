#include "Intake.h"


Intake::Intake() :
    m_motor(IDConstants::kTalonIntake)
{
    m_motor.SetNeutralMode(ctre::phoenix6::signals::NeutralModeValue::Brake);

    SetDefaultCommand(StopCmd());
}

frc2::CommandPtr Intake::RunCmd(std::function<float()> speed) {
    return this->Run([this, speed] { m_motor.Set(speed()); });
}

frc2::CommandPtr Intake::StopCmd()
{
    return this->Run([this] { m_motor.Set(0); });
}