#include "Odometry.h"

Odometry::Odometry(std::function<units::meter_t()> leftDistanceSource, std::function<units::meter_t()> rightDistanceSource) :
    m_leftDistanceSource(leftDistanceSource),
    m_rightDistanceSource(rightDistanceSource)
{}

void Odometry::Periodic() {
    auto leftDistance = m_leftDistanceSource();
    auto rightDistance = m_rightDistanceSource();
    m_poseEstimator.Update(m_navXGyro.GetRotation2d(), leftDistance, rightDistance);
}