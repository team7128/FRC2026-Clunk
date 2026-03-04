#pragma once

#include "Constants.h"

#include <frc2/command/CommandPtr.h>
#include <frc2/command/SubsystemBase.h>
#include <rev/SparkMax.h>

class Shooter : public frc2::SubsystemBase {
    private: 
    rev::spark::SparkMax m_motor{ShooterConstants::kSparkID, rev::spark::SparkBase::MotorType::kBrushless};

    public:
    Shooter();

    frc2::CommandPtr SetSpeed(double speed);
    frc2::CommandPtr SetSpeedCmd(std::function<float()> speed);
};