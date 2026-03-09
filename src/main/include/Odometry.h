#pragma once

#include "Drivebase.h"
#include <frc/estimator/DifferentialDrivePoseEstimator.h>
#include <units/length.h>
#include <studica/AHRS.h>

class Odometry : public frc2::SubsystemBase {
    private:
    studica::AHRS m_navXGyro{studica::AHRS::NavXComType::kMXP_SPI};

    frc::DifferentialDriveKinematics m_kinematics{ 0.6_m };
    frc::DifferentialDrivePoseEstimator m_poseEstimator{m_kinematics, m_navXGyro.GetRotation2d(), 0_m, 0_m, frc::Pose2d()};

    public:
    Odometry(std::function<units::meter_t()> leftDistance, std::function<units::meter_t()> rightDistance);
    void Periodic();

    std::function<units::meter_t()> m_leftDistanceSource, m_rightDistanceSource;
};