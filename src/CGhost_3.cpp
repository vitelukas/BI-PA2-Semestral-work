#include "CGhost_3.hpp"
using namespace std;

CGhost_3::CGhost_3(int entityLook) 
	: CGhost(entityLook)
{
    m_Character = '0';
    m_EntityLook = 7;
}

void CGhost_3::decideMoveDirection(CMap& gameMap, const CEntity & player) {
    if (player.getPosition().second < m_Position.second)
        mvLeft(gameMap);
    else if (player.getPosition().second > m_Position.second)
        mvRight(gameMap);
    else if (player.getPosition().first < m_Position.first)
        mvUp(gameMap);
    else if (player.getPosition().first > m_Position.first)
        mvDown(gameMap);
}