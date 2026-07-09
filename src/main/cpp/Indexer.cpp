#include "Indexer.h"

using namespace ctre::phoenix::motorcontrol;

Indexer::Indexer() :
    m_motorIndexer(IDConstants::kVictorIndexer),
    m_motorConveyor(IDConstants::kVictorConveyor)
{
    m_motorConveyor.Follow(m_motorIndexer);

    m_motorIndexer.SetNeutralMode(NeutralMode::Brake);
    m_motorConveyor.SetNeutralMode(NeutralMode::Brake);
    m_motorIndexer.SetInverted(InvertType::None);
    m_motorConveyor.SetInverted(InvertType::OpposeMaster);

    SetDefaultCommand(StopCmd());
}

frc2::CommandPtr Indexer::RunCmd(std::function<float()> speed) {
    return this->Run([this, speed] { m_motorIndexer.Set(speed()); });
}

frc2::CommandPtr Indexer::StopCmd()
{
    return this->Run([this] { m_motorIndexer.Set(ControlMode::Disabled, 0); });
}