#include "CEntity.hpp"
using namespace std;


bool CEntity::checkCollisions(CMap &gameMap) {
	vector<vector<char>> map = gameMap.m_CharMap;

	return ( wallCollision(gameMap) || corridorCollision(map) );
}

bool CEntity::wallCollision(CMap gameMap) {
	return gameMap.m_CharMap[m_Position.first][m_Position.second] == '#'
			|| m_Position.second >= gameMap.m_Width - 1;
}

bool CEntity::corridorCollision(vector<vector<char>> map) {
	return (m_Position.second < 0
		|| (map[m_Position.first][m_Position.second] == ' ' 
			&& map[m_Position.first][m_Position.second - 1] == '#' )
		|| (map[m_Position.first][m_Position.second] == ' '
			&& map[m_Position.first][m_Position.second + 1] == '#' ) );
}