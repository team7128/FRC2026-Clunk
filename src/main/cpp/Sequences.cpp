#include "Sequences.h"

#include <frc2/command/Commands.h>

frc2::CommandPtr RunHubShooterSystem(Shooter *m_shooter, Turret *m_turret, Indexer *m_indexer) {
    return m_shooter->SetSpeedCmd( [] { return RobotConstants::kHubShooterSpeed; })
        .AlongWith(m_turret->TrackTargetCmd()).Repeatedly()
            .AlongWith(frc2::cmd::Wait(SequenceConstants::kIndexDelaySpeed)
                .AndThen(m_indexer->SetSpeedCmd( [] { return RobotConstants::kIndexerSpeed; })).Repeatedly()
    );
}

frc2::CommandPtr RunPassShooterSystem(Shooter *m_shooter, Turret *m_turret, Indexer *m_indexer) {
    return m_shooter->SetSpeedCmd( [] { return RobotConstants::kPassShooterSpeed; })
        .AlongWith(m_turret->TrackTargetCmd()).Repeatedly()
            .AlongWith(frc2::cmd::Wait(SequenceConstants::kIndexDelaySpeed)
                .AndThen(m_indexer->SetSpeedCmd( [] { return RobotConstants::kIndexerSpeed; })).Repeatedly()
    );
}

frc2::CommandPtr StopShooterSystem(Shooter *m_shooter, Indexer *m_indexer) {
    return m_shooter->SetSpeedCmd(0)
        .AlongWith(m_indexer->SetSpeedCmd(0));
}