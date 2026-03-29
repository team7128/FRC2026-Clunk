#include "Indexer.h"

using namespace ctre::phoenix::motorcontrol;

Indexer::Indexer() :
    m_motorTransfer(IDConstants::kVictorTransfer),
    m_motorConveyor(IDConstants::kVictorConveyor)
{
    m_motorConveyor.Follow(m_motorTransfer);

    m_motorTransfer.SetNeutralMode(NeutralMode::Brake);
    m_motorConveyor.SetNeutralMode(NeutralMode::Brake);
    m_motorTransfer.SetInverted(InvertType::None);
    m_motorConveyor.SetInverted(InvertType::OpposeMaster);

    SetDefaultCommand(StopCmd());
}

frc2::CommandPtr Indexer::RunCmd(std::function<float()> speed) {
    return this->Run([this, speed] { m_motorTransfer.Set(speed()); });
}

frc2::CommandPtr Indexer::StopCmd()
{
    return this->Run([this] { m_motorTransfer.Set(ControlMode::Disabled, 0); });
}