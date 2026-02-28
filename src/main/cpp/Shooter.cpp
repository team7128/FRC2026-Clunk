#include "Shooter.h"

Shooter::Shooter() {}

frc2::CommandPtr Shooter::SetSpeed(double speed) {
    return this->Run([this, speed] { this->m_motor.Set(speed); });
}

frc2::CommandPtr Shooter::SetSpeed(std::function<float()> speed)
{
    return this->Run([this, speed] { m_motor.Set(speed()); });
}