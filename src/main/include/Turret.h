#pragma once

#include <rev/SparkMax.h>
#include <frc/controller/PIDController.h>

class Turret {
    private:
    rev::spark::SparkMax m_motorcontrol{5, rev::spark::SparkLowLevel::MotorType::kBrushless};
    float m_targetangle;

    frc::PIDController pid{0.0003, 0, 0};

    public:
    Turret();
    
    void SetSpeed(double speed); 
    void SetTargetAngle(float targetangle);
    void Periodic();

    float GetAngle();
};