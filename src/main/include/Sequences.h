#pragma once

#include <frc2/command/CommandPtr.h>

#include "Shooter.h"
#include "Turret.h"
#include "Indexer.h"

namespace Sequences {
    frc2::CommandPtr RunHubShooterSystem(Shooter *m_shooter, Turret *m_turret, Indexer *m_indexer);
    frc2::CommandPtr RunPassShooterSystem(Shooter *m_shooter, Turret *m_turret, Indexer *m_indexer);
    frc2::CommandPtr StopShooterSystem(Shooter *m_shooter, Indexer *m_indexer);
}