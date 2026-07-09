#pragma once

#include "Constants.h"

#include <frc/drive/DifferentialDrive.h>
#include <frc2/command/CommandPtr.h>
#include <frc2/command/SubsystemBase.h>
#include <units/length.h>
#include <rev/SparkMax.h>

class Drivebase : public frc2::SubsystemBase
{
public:
    Drivebase();

	units::meter_t GetLeftDistance();
	units::meter_t GetRightDistance();

    frc2::CommandPtr ArcadeDriveCmd(std::function<float()> forward, std::function<float()> turn);
    frc2::CommandPtr StopCmd();

private:
    void ArcadeDrive(float forward, float turn);
    void Stop();

private:
    rev::spark::SparkMax m_motorFL{ IDConstants::kSparkFL, rev::spark::SparkBase::MotorType::kBrushless},
    m_motorBL{ IDConstants::kSparkFR, rev::spark::SparkBase::MotorType::kBrushless},
    m_motorFR{ IDConstants::kSparkBL, rev::spark::SparkBase::MotorType::kBrushless},
    m_motorBR{ IDConstants::kSparkBR, rev::spark::SparkBase::MotorType::kBrushless};
    
    frc::DifferentialDrive m_diffDrive{ m_motorFL, m_motorFR};
};