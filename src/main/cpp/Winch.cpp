#include "Winch.h"
#include "Constants.h"

Winch::Winch() {}

frc2::CommandPtr Winch::Lift() {
    return this->Run([this] { this->m_motor.Set(WinchConstants::kLiftSpeed); })
        .WithTimeout(WinchConstants::kLiftTime);
}

frc2::CommandPtr Winch::Lower() {
    return this->Run([this] { this->m_motor.Set(WinchConstants::kLowerSpeed); })
        .Until([this] { return !m_limitswitch.Get(); });
}