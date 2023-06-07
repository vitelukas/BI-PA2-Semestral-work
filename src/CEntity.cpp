#include "CEntity.hpp"
using namespace std;

CEntity::CEntity()
	: m_Position(0,0), m_Speed(0), m_Direction('n')
{
	m_PreviousTime = std::chrono::steady_clock::now();
	m_backDirections = {
		{'w', 's'},
        {'s', 'w'},
        {'a', 'd'},
        {'d', 'a'},
	};
}

void CEntity::move(CMap &) {
	return;
}

bool CEntity::checkCollisions(CMap &gameMap) {
	vector<vector<char>> map = gameMap.m_CharMap;

	return ( wallCollision(gameMap) || corridorCollision(map) );
}

bool CEntity::wallCollision(CMap gameMap) {
	return gameMap.m_CharMap[m_Position.first][m_Position.second] == '#' ||
		   m_Position.second >= gameMap.m_Width - 1 ||
		   m_Position.first >= gameMap.m_Height - 1 ||
		   m_Position.second < 0 ||
		   m_Position.first < 0;
}

bool CEntity::corridorCollision(vector<vector<char>> map) {
	return  map[m_Position.first][m_Position.second] == ' ' && 
			(map[m_Position.first][m_Position.second - 1] == '#' ||  map[m_Position.first][m_Position.second + 1] == '#' );
}

bool CEntity::checkDirectionOK(char futureDirection) {
	char bannedDirection = m_backDirections[m_Direction];

	return !(bannedDirection == futureDirection);
}

void CEntity::formatTile(char &tile) {
	if (tile == '&' || tile == '@' || tile == '0' || tile == 'T' || tile == 'O') {
		tile = ' ';
		return;
	}

	switch (tile) {
	case '.':
		attron(COLOR_PAIR(2));
		break;
	case 'B':
    	attron(COLOR_PAIR(3));
		break;
	default:
		break;
	}
}