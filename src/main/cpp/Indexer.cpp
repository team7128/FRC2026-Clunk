#include "Indexer.h"

Indexer::Indexer() {
    m_motorConveyor.Follow(m_motorIndex);
}

void Indexer::SetSpeed(double speed)
{
    m_motorIndex.Set(speed);
}

frc2::CommandPtr Indexer::SetSpeedCmd(std::function<float()> speed) {
    return this->Run([this, speed] { this->m_motorIndex.Set(speed()); });
}