#include "CEntity.hpp"
using namespace std;

CEntity::CEntity()
	: m_Position(0,0), m_Speed(0), m_Character('x'), m_EntityLook(0)
{
	m_PreviousTime = std::chrono::steady_clock::now();
	m_Direction = 'n';
}

void CEntity::decideMoveDirection(CMap &gameMap) {
	switch (m_Direction) {
		case 'w':
			mvUp(gameMap);
			break;
		case 's':
			mvDown(gameMap);
			break;
		case 'a':
			mvLeft(gameMap);
			break;
		case 'd':
			mvRight(gameMap);
			break;
		default:
			mvaddch(m_Position.first, m_Position.second, m_Character);
			break;
	}
}

bool CEntity::checkIfCollisions(CMap &gameMap, pair<size_t, size_t> position) {
	vector<vector<char>> map = gameMap.m_CharMap;

	if ( wallCollision(gameMap, position) )
		return true;

	if (map[position.first][position.second] == 'T') {
		if (position == gameMap.m_TeleportIn)
			position = gameMap.m_TeleportOut;
		else
			position = gameMap.m_TeleportIn;
    }

	return ( corridorCollision(map, position) );
}


bool CEntity::wallCollision(const CMap &gameMap, pair<size_t, size_t> position) {
	return position.second >= gameMap.m_Width ||
		   position.first >= gameMap.m_Height ||
		   gameMap.m_CharMap[position.first][position.second] == '#';
}

bool CEntity::corridorCollision(vector<vector<char>> map, pair<size_t, size_t> position) {
	return  map[position.first][position.second] == ' ' && 
			(map[position.first][position.second - 1] == '#' ||  map[position.first][position.second + 1] == '#' );
}