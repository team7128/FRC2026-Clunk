#pragma once

#include "Constants.h"

#include <frc2/command/CommandPtr.h>
#include <frc2/command/SubsystemBase.h>
#include <ctre/phoenix/motorcontrol/can/WPI_VictorSPX.h>

class Indexer : public frc2::SubsystemBase {
    private:
    ctre::phoenix::motorcontrol::can::WPI_VictorSPX m_motorTransfer, m_motorConveyor;

    public:
    Indexer();

    frc2::CommandPtr RunCmd(std::function<float()> speed);
    frc2::CommandPtr StopCmd();
};