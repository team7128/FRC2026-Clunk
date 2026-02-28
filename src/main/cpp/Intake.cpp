#include "Intake.h"

Intake::Intake() {}

void Intake::SetSpeed(double speed)
{
    m_motor.Set(speed);
}

frc2::CommandPtr Intake::SetSpeedCmd(double speed) {
    return this->Run([this, speed] { this->m_motor.Set(speed); });
}