#include "Turret.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc2/command/Commands.h>

Turret::Turret()
{
    rev::spark::SparkBaseConfig motorConfig;
    motorConfig.OpenLoopRampRate(0.4);
    motorConfig.encoder.PositionConversionFactor(360 / 6.5 / 5);

    m_motorcontrol.Configure(motorConfig, rev::ResetMode::kResetSafeParameters, rev::PersistMode::kPersistParameters);
    m_motorcontrol.GetEncoder().SetPosition(0.0);

    m_turretpid.SetTolerance(2);

    frc::SmartDashboard::PutData("Turret PID", &m_turretpid);

    SetDefaultCommand(this->Run([this]{ m_motorcontrol.StopMotor(); }));
}

frc2::CommandPtr Turret::HomePosition() {
return this->Run([this] { this->m_motorcontrol.Set(-0.1); })
.Until([this] { return !m_limitSwitch.Get(); })
    .AndThen(frc2::cmd::RunOnce([this] { m_motorcontrol.GetEncoder().SetPosition(-100.0); })); // TODO: Actual position
}

frc2::CommandPtr Turret::SetSpeed(double speed) {
return this->Run([this, speed] { this->m_motorcontrol.Set(speed); });
}

frc2::CommandPtr Turret::SetSpeed(std::function<double()> speed) {
return this->Run([this, speed] { this->m_motorcontrol.Set(speed()); });
}

void Turret::SetTargetAngle(float targetangle) {
// m_targetangle = targetangle;
}

void Turret::SetTargetLocation(float targetX, float targetY) {
    m_targetX = targetX;
    m_targetY = targetY;
}

void Turret::Periodic() {
    frc::SmartDashboard::PutNumber("Turret Target", m_targetangle);
}

frc2::CommandPtr Turret::TrackTargetCmd()
{
    return this->Run([this] {
        double turretDifferenceX = m_targetX - turretX;
        double turretDifferenceY = m_targetY - turretY;
        m_targetangle = atan2(turretDifferenceY, turretDifferenceX) / std::numbers::pi * 180.f;
        
        float robotAngle = 0.f;
        float turretRelativeHeading = GetAngle() - robotAngle;
        
        float pidOut = m_turretpid.Calculate(turretRelativeHeading, m_targetangle);
        units::volt_t pidVoltOut{ std::clamp<float>(pidOut, -12, 12) };
        m_motorcontrol.SetVoltage(pidVoltOut);
        // if (m_turretpid.AtSetpoint())
        //     m_turretpid.Reset();
    });
}

float Turret::GetAngle()
{
    return m_motorcontrol.GetEncoder().GetPosition();
}