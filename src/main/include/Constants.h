#pragma once

#include <units/time.h>
#include <units/voltage.h>
#include <units/angular_velocity.h>
#include <units/angular_acceleration.h>

namespace RobotConstants {
    constexpr double kTargetX = 10;
    constexpr double kTargetY = 10;

    constexpr double kIntakeSpeed = 0.8;
    constexpr double kIndexerSpeed = 1;
    constexpr double kShooterSpeed = 0.2;
    constexpr int kTurretAxis = 4;
    constexpr double kTurretThreshold = 0.1;

    constexpr int kControllerID = 0;
}

namespace ShooterConstants {
    constexpr int kSparkID = 5;
}

namespace TurretConstants {
    constexpr double kConfigOpenLoopRampRate = 0.4;
    constexpr double kConfigPositionConversionFactor = 360 / 6.5 / 5;
    constexpr double kConfigMotorTolerance = 2;
    constexpr double kConfigDefaultEncoderPosition = 0.0;

    constexpr auto kFFVoltage = 0_V;
    constexpr double kFFkV = 0.0;
    constexpr double kFFka = 0;
    constexpr double kP = 0.6;
    constexpr double kI = 0;
    constexpr double kD = 0;

    constexpr double kHomeSpeed = -0.1;
    constexpr double kHomeEncoderPosition = (-100.0); // Todo: get actual position

    constexpr int kPidLowerClamp = -12;
    constexpr int kPidUpperClamp = 12;

    constexpr int kSparkID = 5;
    constexpr int kLimitSwitchID = 0;
}

namespace IntakeConstants {
    constexpr int kVictorID = 1;
}

namespace IndexerConstants {
    constexpr int kVictorIndexerID = 2;
    constexpr int kVictorConveyorID = 3;
}

namespace WinchConstants {
    constexpr double kLiftSpeed = 0.1;
    constexpr double kLowerSpeed = -1;
    constexpr auto kLiftTime = 2_s; // Todo: time actual speed

    constexpr int kSparkID = 2;
    constexpr int kLimitSwitchID = 1;
}