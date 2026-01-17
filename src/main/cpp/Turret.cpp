#include "Turret.h"

void Turret::SetSpeed(double speed) {
m_motorcontrol.Set(speed);
}