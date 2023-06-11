#include "CEntity.hpp"
using namespace std;

CEntity::CEntity()
	: m_Position(0,0), m_InitialPosition(0,0), m_Speed(0), m_Character('x'), m_EntityLook(0)
{
	m_CurrentTime = m_PreviousTime = std::chrono::steady_clock::now();
	m_Direction = 'n';
}

bool CEntity::checkIfCollisions(CMap &gameMap, pair<size_t, size_t> futurePosition) {
	vector<vector<char>> map = gameMap.m_CharMap;

	// First check if the position is out of bounds to anticipate SEG fault
	if ( wallCollision(gameMap, futurePosition) )
		return true;

	// If the position overlaps with a teleport, change the futurePosition to the other teleport position
	// --> this method is only used when a ghost is searching for a path using BFS
	if (map[futurePosition.first][futurePosition.second] == 'T') {
		if (futurePosition == gameMap.m_TeleportIn)
			futurePosition = gameMap.m_TeleportOut;
		else
			futurePosition = gameMap.m_TeleportIn;
    }

	return ( corridorCollision(map, futurePosition) );
}

bool CEntity::wallCollision(const CMap &gameMap, pair<size_t, size_t> position) const {
	// Check it the position out of the map bounds or if there is a wall on this position
	return position.second >= gameMap.m_Width -1 ||
		   position.first >= gameMap.m_Height -1 ||
		   gameMap.m_CharMap[position.first][position.second] == '#';
}

bool CEntity::corridorCollision(vector<vector<char>> map, pair<size_t, size_t> position) const {
	return  map[position.first][position.second] == ' ' && 
		   (map[position.first][position.second - 1] == '#' || map[position.first][position.second + 1] == '#' );
}

void CEntity::formatTile(char &tile) const {
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

std::pair<size_t, size_t> CEntity::getPosition() const {
    return m_Position;
}

char CEntity::getDirection() const {
    return m_Direction;
}