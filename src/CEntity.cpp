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

bool CEntity::checkIfCollisions(CMap &gameMap) {
	vector<vector<char>> map = gameMap.m_CharMap;

	if (map[m_Position.first][m_Position.second] == 'T') {
		if (m_Position == gameMap.m_TeleportIn)
			m_Position = gameMap.m_TeleportOut;
		else
			m_Position = gameMap.m_TeleportIn;
    }

	return ( wallCollision(gameMap, m_Position) || corridorCollision(map, m_Position) );
}

bool CEntity::wallCollision(const CMap &gameMap, pair<size_t, size_t> position) {
	return position.second >= gameMap.m_Width -1 ||
		   position.first >= gameMap.m_Height -1 ||
		   position.second == SIZE_MAX ||
		   position.first == SIZE_MAX  ||
		   gameMap.m_CharMap[position.first][position.second] == '#';
}

bool CEntity::corridorCollision(vector<vector<char>> map, pair<size_t, size_t> position) {
	return  map[position.first][position.second] == ' ' && 
			(map[position.first][position.second - 1] == '#' ||  map[position.first][position.second + 1] == '#' );
}