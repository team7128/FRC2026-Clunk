#include "Turret.h"
#include <frc/smartdashboard/SmartDashboard.h>

Turret::Turret()
{
    rev::spark::SparkBaseConfig motorConfig;
    motorConfig.encoder.PositionConversionFactor(360 / 12.5);

    m_motorcontrol.Configure(motorConfig, rev::ResetMode::kResetSafeParameters, rev::PersistMode::kPersistParameters);
    m_motorcontrol.GetEncoder().SetPosition(0.0);

    pid.SetTolerance(2);

    frc::SmartDashboard::PutData("Turret PID", &pid);
}

void Turret::SetSpeed(double speed) {
m_motorcontrol.Set(speed);
}

void Turret::SetTargetAngle(float targetangle) {
m_targetangle = targetangle;
}

void Turret::Periodic() {
    float currentAngle = m_motorcontrol.GetEncoder().GetPosition();

    m_motorcontrol.Set(pid.Calculate(m_motorcontrol.GetEncoder().GetPosition(), m_targetangle));

    if (pid.AtSetpoint())
        pid.Reset();
}

float Turret::GetAngle()
{
    return m_motorcontrol.GetEncoder().GetPosition();
}