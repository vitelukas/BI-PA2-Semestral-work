#include "CGameMode.hpp"
using namespace std;

CGameMode::CGameMode() 
	: m_EntitySpeed(160), m_GhostSpeed(60), m_PlayerLives(3), m_BerserkerDuration(5000)
{
}

void CGameMode::setAttributes(int lives, int entitySpeed, int ghostSlower, int berserkDuration) {
	m_PlayerLives = lives;
	m_EntitySpeed = entitySpeed;
	m_GhostSpeed = ghostSlower;
	m_BerserkerDuration = berserkDuration;
}