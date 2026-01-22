#pragma once

#include <rev/SparkMax.h>
#include <frc/controller/PIDController.h>
#include <frc/controller/ProfiledPIDController.h>
#include <frc/controller/SimpleMotorFeedforward.h>
#include <frc/trajectory/TrapezoidProfile.h>
#include <units/angular_velocity.h>
#include <units/angular_acceleration.h>
#include <units/voltage.h>

class Turret {
    private:
    rev::spark::SparkMax m_motorcontrol{5, rev::spark::SparkLowLevel::MotorType::kBrushless};
    float m_targetangle;

    using ffType = frc::SimpleMotorFeedforward<units::degrees>;

    frc::TrapezoidProfile<units::degree>::Constraints m_turretconstraints{180_deg_per_s, 1800_deg_per_s_sq};
    ffType m_turretfeedforward{0_V, units::unit_t<ffType::kv_unit>(0.0), units::unit_t<ffType::ka_unit>(0)};
    frc::ProfiledPIDController<units::degree> m_turretpid{0.0003, 0, 0, m_turretconstraints};

    public:
    Turret();
    
    void SetSpeed(double speed); 
    void SetTargetAngle(float targetangle);
    void Periodic();

    float GetAngle();
};