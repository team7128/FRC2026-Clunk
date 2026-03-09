#include "Shooter.h"


Shooter::Shooter() {}

frc2::CommandPtr Shooter::SetSpeed(double speed) {
    return this->Run([this, speed] { this->m_motor.Set(speed); });
}

frc2::CommandPtr Shooter::SetSpeedCmd(std::function<float()> speed)
{
    return this->Run([this, speed] { m_motor.Set(speed()); });
}

double Shooter::CalculateSpeed(float shooterTargetX, float shooterTargetY) {
    double shooterDifferenceX = shooterTargetX - shooterX;
    double shooterDifferenceY = shooterTargetY - shooterY;
    double shooterDifference = std::hypot(shooterDifferenceX, shooterDifferenceY);
    shooterSpeed = shooterDifference / ShooterConstants::kMaxShooterDistance;
    return shooterSpeed;
}