#pragma once

#include "Constants.h"

#include <rev/SparkMax.h>
#include <frc/controller/PIDController.h>
#include <frc/controller/ProfiledPIDController.h>
#include <frc/controller/SimpleMotorFeedforward.h>
#include <frc/trajectory/TrapezoidProfile.h>
#include <units/angular_velocity.h>
#include <units/angular_acceleration.h>
#include <units/voltage.h>
#include <frc2/command/CommandPtr.h>
#include <frc2/command/SubsystemBase.h>
#include <frc/DigitalInput.h>

class Turret : public frc2::SubsystemBase {
    private:
    rev::spark::SparkMax m_motorcontrol{TurretConstants::kSparkID, rev::spark::SparkLowLevel::MotorType::kBrushless};
    float m_targetangle;

    using ffType = frc::SimpleMotorFeedforward<units::degrees>;

    ffType m_turretfeedforward{TurretConstants::kFFVoltage, units::unit_t<ffType::kv_unit>(TurretConstants::kFFkV), units::unit_t<ffType::ka_unit>(TurretConstants::kFFka)};
    frc::PIDController m_turretpid{TurretConstants::kP, TurretConstants::kI, TurretConstants::kD};

    frc::DigitalInput m_limitSwitch{TurretConstants::kLimitSwitchID};

    public:
    Turret();
    
    frc2::CommandPtr HomePosition();
    frc2::CommandPtr SetSpeed(double speed); 
    frc2::CommandPtr SetSpeedCmd(std::function<double()> speed); 
    void SetTargetAngle(float targetangle);
    void SetTargetLocation(float targetX, float targetY);
    void Periodic();
    frc2::CommandPtr TrackTargetCmd();

    float turretX;
    float turretY;
    float m_targetX;
    float m_targetY;
    float robotAngle;

    float GetAngle();
};