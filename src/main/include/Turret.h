#pragma once

#include <rev/SparkMax.h>

class Turret {
    private:
    rev::spark::SparkMax m_motorcontrol{5, rev::spark::SparkLowLevel::MotorType::kBrushless};
    float m_targetangle;

    public:
    Turret();
    
    void SetSpeed(double speed); 
    void SetTargetAngle(float targetangle);
    void Periodic();

    float GetAngle();
};