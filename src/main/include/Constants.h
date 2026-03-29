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
    constexpr double kHubShooterSpeed = 1;
    constexpr double kPassShooterSpeed = 0.5;
    constexpr int kTurretAxis = 4;
    constexpr double kTurretThreshold = 0.1;

    constexpr float kForwardMultiplier = 0.8f;
    constexpr float kTurnMultiplier = 0.6f;
}

namespace IDConstants {
    constexpr int kSparkFL = 1,
        kSparkFR = 2,
        kSparkBL = 3,
        kSparkBR = 4;

    constexpr int kVictorTransfer = 1;
    constexpr int kVictorConveyor = 2;
    constexpr int kVictorIntake = 3;

    constexpr int kTalonWinchLeft = 1;
    constexpr int kTalonWinchRight = 2;
}

namespace SequenceConstants {
    constexpr auto kIndexDelaySpeed = 0.8_s;
}

namespace ShooterConstants {
    constexpr int kSparkID = 6;
    constexpr double kMaxShooterDistance = 100;
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
}

namespace IndexerConstants {
}

namespace WinchConstants {
    constexpr double kLiftSpeed = 1.0;
    constexpr double kLowerSpeed = -1.0;
    constexpr auto kLiftTime = 2_s; // Todo: time actual speed

    constexpr int kTalonLeftID = 4;
    constexpr int kTalonRightID = 5;
    constexpr int kLimitSwitchID = 1;
}