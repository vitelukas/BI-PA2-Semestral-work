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