#pragma once

#include <frc2/command/CommandPtr.h>
#include <frc2/command/SubsystemBase.h>
#include <rev/SparkMax.h>

class Shooter : public frc2::SubsystemBase {
    private: 
    rev::spark::SparkMax m_motor{ 5, rev::spark::SparkBase::MotorType::kBrushless };

    public:
    Shooter();

    frc2::CommandPtr SetSpeed(double speed);
    frc2::CommandPtr SetSpeed(std::function<float()> speed);
};