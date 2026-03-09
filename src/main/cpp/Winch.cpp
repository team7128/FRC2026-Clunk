#include "Winch.h"
#include "Constants.h"

Winch::Winch() {
    m_motorRight.Follow(m_motorLeft);
    m_motorRight.SetInverted(ctre::phoenix::motorcontrol::InvertType::OpposeMaster);
}

frc2::CommandPtr Winch::Lift() {
    return this->Run([this] { this->m_motorLeft.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, WinchConstants::kLiftSpeed); })
        .WithTimeout(WinchConstants::kLiftTime);
}

frc2::CommandPtr Winch::Lower() {
    return this->Run([this] { this->m_motorLeft.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, WinchConstants::kLowerSpeed); })
        .Until([this] { return !m_limitswitch.Get(); });
}