#pragma once

#include <rev/SparkMax.h>

class Turret {
    private:
    rev::spark::SparkMax m_motorcontrol{5, rev::spark::SparkLowLevel::MotorType::kBrushless};

    public:
    void SetSpeed(double speed); 
};