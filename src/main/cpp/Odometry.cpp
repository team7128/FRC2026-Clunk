#include "Odometry.h"

Odometry::Odometry() {}

Odometry::Odometry(std::function<units::meter_t()> leftDistanceSource, std::function<units::meter_t()> rightDistanceSource, std::function<units::degree_t()> turretAngleSource) :
    m_leftDistanceSource(leftDistanceSource),
    m_rightDistanceSource(rightDistanceSource),
    m_turretAngleSource(turretAngleSource)
{}

void Odometry::Periodic() {
    units::meter_t leftDistance = m_leftDistanceSource(),
        rightDistance = m_rightDistanceSource();
    m_poseEstimator.Update(m_navXGyro.GetRotation2d(), leftDistance, rightDistance);

    auto visionResults = m_visionCam.GetAllUnreadResults();
    if (visionResults.size())
    {
        for (auto &result : visionResults)
        {
            if (result.HasTargets())
            {
                auto estimatedPose = m_visionPoseEstimator.EstimateCoprocMultiTagPose(result);

                if (!estimatedPose)
                {
                    estimatedPose = m_visionPoseEstimator.EstimateLowestAmbiguityPose(result);
                }

                if (estimatedPose)
                {
                    m_poseEstimator.AddVisionMeasurement(estimatedPose->estimatedPose.ToPose2d(), estimatedPose->timestamp);
                }
            }
        }
    }
}

void Odometry::UpdateVisionTransform()
{
    const frc::Transform3d turretToCamera{
        frc::Translation3d(300_mm, 0_mm, 430_mm),
        frc::Rotation3d()
    };

    frc::Transform3d turretRotation{
        frc::Translation3d(),
        frc::Rotation3d(0_deg, 0_deg, -m_turretAngleSource())
    };

    frc::Transform3d robotToCamera = turretRotation + turretToCamera;

    m_visionPoseEstimator.SetRobotToCameraTransform(robotToCamera);
}