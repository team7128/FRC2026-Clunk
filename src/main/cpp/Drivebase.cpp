#include "Drivebase.h"

Drivebase::Drivebase()
{
    rev::spark::SparkBaseConfig leftMotorConfig;
    float metersPerRev = 6 * 0.00254f * 2 * 3.14159f / 12.75f;
    leftMotorConfig.encoder.PositionConversionFactor(metersPerRev)
        .VelocityConversionFactor(metersPerRev / 60);
    
    rev::spark::SparkBaseConfig rightMotorConfig;
    rightMotorConfig.Apply(leftMotorConfig);
    
    leftMotorConfig.Inverted(false);
    rightMotorConfig.Inverted(true);
    
    m_motorFL.Configure(leftMotorConfig, rev::ResetMode::kResetSafeParameters, rev::PersistMode::kPersistParameters);
    m_motorFR.Configure(rightMotorConfig, rev::ResetMode::kResetSafeParameters, rev::PersistMode::kPersistParameters);
    
    leftMotorConfig.Follow(m_motorFL);
    rightMotorConfig.Follow(m_motorFR);
    
    m_motorBL.Configure(leftMotorConfig, rev::ResetMode::kResetSafeParameters, rev::PersistMode::kPersistParameters);
    m_motorBR.Configure(rightMotorConfig, rev::ResetMode::kResetSafeParameters, rev::PersistMode::kPersistParameters);
}

units::meter_t Drivebase::GetLeftDistance() {
    return units::meter_t{ m_motorFL.GetEncoder().GetPosition() };
}

units::meter_t Drivebase::GetRightDistance() {
    return units::meter_t{ m_motorFR.GetEncoder().GetPosition() };
}

frc2::CommandPtr Drivebase::ArcadeDriveCmd(std::function<float()> forward, std::function<float()> turn) {
    return this->Run([this, forward, turn] { ArcadeDrive(forward(), turn()); });
}

frc2::CommandPtr Drivebase::StopCmd() {
    return this->Run([this] { Stop(); });
}

void Drivebase::ArcadeDrive(float forward, float turn) {
    m_diffDrive.ArcadeDrive(forward, turn);
}

void Drivebase::Stop() {
    m_diffDrive.StopMotor();
}