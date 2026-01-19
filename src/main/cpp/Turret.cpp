#include "Turret.h"

Turret::Turret()
{
    rev::spark::SparkBaseConfig motorConfig;
    motorConfig.encoder.PositionConversionFactor(360 / 4.2);

    m_motorcontrol.Configure(motorConfig, rev::ResetMode::kResetSafeParameters, rev::PersistMode::kPersistParameters);
    m_motorcontrol.GetEncoder().SetPosition(0.0);
}

void Turret::SetSpeed(double speed) {
m_motorcontrol.Set(speed);
}

void Turret::SetTargetAngle(float targetangle) {
m_targetangle = targetangle;
}

void Turret::Periodic() {
    float currentAngle = m_motorcontrol.GetEncoder().GetPosition();

    if (currentAngle > m_targetangle + 10)
        m_motorcontrol.Set(-0.03);
    else if (currentAngle < m_targetangle - 10)
        m_motorcontrol.Set(0.03);
    else
        m_motorcontrol.StopMotor();
}

float Turret::GetAngle()
{
    return m_motorcontrol.GetEncoder().GetPosition();
}