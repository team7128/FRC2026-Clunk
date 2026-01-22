#include "Turret.h"
#include <frc/smartdashboard/SmartDashboard.h>

Turret::Turret()
{
    rev::spark::SparkBaseConfig motorConfig;
    motorConfig.encoder.PositionConversionFactor(360 / 12.5);

    m_motorcontrol.Configure(motorConfig, rev::ResetMode::kResetSafeParameters, rev::PersistMode::kPersistParameters);
    m_motorcontrol.GetEncoder().SetPosition(0.0);

    m_turretpid.SetTolerance(2_deg);

    frc::SmartDashboard::PutData("Turret PID", &m_turretpid);
}

void Turret::SetSpeed(double speed) {
m_motorcontrol.Set(speed);
}

void Turret::SetTargetAngle(float targetangle) {
m_targetangle = targetangle;
}

void Turret::Periodic() {
    float currentAngle = m_motorcontrol.GetEncoder().GetPosition();
    m_turretpid.SetGoal(units::degree_t(m_targetangle));
    m_motorcontrol.Set(m_turretpid.Calculate(units::degree_t(m_motorcontrol.GetEncoder().GetPosition())) + m_turretfeedforward.Calculate(m_turretpid.GetSetpoint().velocity));

    if (m_turretpid.AtSetpoint())
        m_turretpid.Reset(units::degree_t(currentAngle));
}

float Turret::GetAngle()
{
    return m_motorcontrol.GetEncoder().GetPosition();
}