#include "Winch.h"

Winch::Winch() {}

frc2::CommandPtr Winch::SetSpeed(double speed) {
    return this->Run([this, speed] { this->m_motor.Set(speed); });
}