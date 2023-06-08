#include "CGhost_3.hpp"
using namespace std;

CGhost_3::CGhost_3() 
	: CGhost()
{
    m_Character = '0';
    m_EntityLook = 7;
}

void CGhost_3::decideMoveDirection(CMap& gameMap, const CPlayer & player) {
    if (player.m_Position.first < m_Position.first)
        mvUp(gameMap);
    else if (player.m_Position.first > m_Position.first)
        mvDown(gameMap);
    else if (player.m_Position.second < m_Position.second)
        mvLeft(gameMap);
    else if (player.m_Position.second > m_Position.second)
        mvRight(gameMap);
}

void CGhost_3::mvUp(CMap& gameMap) {
    --m_Position.first;
    if (checkIfCollisions(gameMap, 'w')) {
        ++m_Position.first;
		chooseRandomMove(gameMap);
	} else {
		m_Direction = 'w';
	}
}

void CGhost_3::mvDown(CMap& gameMap) {
    ++m_Position.first;
    if (checkIfCollisions(gameMap, 's')) {
        --m_Position.first;
		chooseRandomMove(gameMap);
	} else {
		m_Direction = 's';
	}
}

void CGhost_3::mvLeft(CMap& gameMap) {
    --m_Position.second;
    if (checkIfCollisions(gameMap, 'a')) {
        ++m_Position.second;
		chooseRandomMove(gameMap);
	} else {
		m_Direction = 'a';
	}
}

void CGhost_3::mvRight(CMap& gameMap) {
    ++m_Position.second;
    if (checkIfCollisions(gameMap, 'd')) {
        --m_Position.second;
		chooseRandomMove(gameMap);
	} else {
		m_Direction = 'd';
	}
}

void CGhost_3::chooseRandomMove(CMap& gameMap) {
	// Generate a pseudo random direction based on the current time
	int randomDirection = rand() % 4 + 1;

	switch (randomDirection) {
	case 1:
		mvUp(gameMap);
		break;
	case 2:
		mvDown(gameMap);
		break;
	case 3:
		mvLeft(gameMap);
		break;
	case 4:
		mvRight(gameMap);
		break;
	default:
		break;
	}
}