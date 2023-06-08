#include "CGhost.hpp"
using namespace std;
using namespace std::chrono;

CGhost::CGhost()
	:CEntity(), m_GhostSlower(100)
{
	m_DirectionsTable = {
		{'w', 0},
        {'s', 1},
        {'a', 2},
        {'d', 3},
        {'x', 4},
	};
	m_BackDirections = {
		{0, 's'},
        {1, 'w'},
        {2, 'd'},
        {3, 'a'},
        {4, 'x'},
	};
}

void CGhost::move(CMap& gameMap, const CPlayer& player) {
	m_CurrentTime = steady_clock::now();
    auto elapsedTime = duration_cast<milliseconds>(m_CurrentTime - m_PreviousTime).count();

    if (elapsedTime < m_Speed.count() + m_GhostSlower) {
        return;
	}

	srand(time(0));
	char tile = gameMap.m_CharMap[m_Position.first][m_Position.second];
	formatTile(tile);
    mvaddch(m_Position.first, m_Position.second, tile);

	if (player.m_IsBerserk) {
		chooseRandomMove(gameMap);
	} else {
    	decideMoveDirection(gameMap, player);
	}

    attron(COLOR_PAIR(m_EntityLook));
    mvaddch(m_Position.first, m_Position.second, m_Character);
    attroff(COLOR_PAIR(m_EntityLook));

	m_PreviousTime = m_CurrentTime; // Update the timer
}

void CGhost::mvUp(CMap& gameMap) {
    --m_Position.first;
    if (checkIfCollisions(gameMap, 'w')) {
        ++m_Position.first;
	}
	m_Direction = 'w';
}

void CGhost::mvDown(CMap& gameMap) {
    ++m_Position.first;
    if (checkIfCollisions(gameMap, 's')) {
        --m_Position.first;
	}
	m_Direction = 's';
}

void CGhost::mvLeft(CMap& gameMap) {
    --m_Position.second;
    if (checkIfCollisions(gameMap, 'a')) {
        ++m_Position.second;
	}
	m_Direction = 'a';
}

void CGhost::mvRight(CMap& gameMap) {
    ++m_Position.second;
    if (checkIfCollisions(gameMap, 'd')) {
        --m_Position.second;
	}
	m_Direction = 'd';
}

bool CGhost::checkIfCollisions(CMap &gameMap, char futureDirection) {
	return checkIfCollisions(gameMap, futureDirection, m_Position);
}

bool CGhost::checkIfCollisions(CMap& gameMap, char futureDirection, pair<size_t, size_t> position) {
    vector<vector<char>> map = gameMap.m_CharMap;

	if (wallCollision(gameMap, position))
		return true;

	if (map[position.first][position.second] == 'T') {
		if (position == gameMap.m_TeleportIn)
			m_Position = gameMap.m_TeleportOut;
		else
			m_Position = gameMap.m_TeleportIn;
    }

	return ( corridorCollision(map, position) || !checkDirectionOK(futureDirection) );
}

bool CGhost::checkDirectionOK(char futureDirection) {
	int dirToNum = m_DirectionsTable[m_Direction];
	char bannedDirection = m_BackDirections[dirToNum];

	return !(bannedDirection == futureDirection);
}

char CGhost::determineDirection(pair<size_t, size_t> futurePos) {
    if (futurePos.first < m_Position.first) {
        // Up
        return 'w';
    } else if (futurePos.first > m_Position.first) {
        // Down
        return 's';
    } else if (futurePos.second < m_Position.second) {
        // Left
        return 'a';
    } else if (futurePos.second > m_Position.second) {
        // Right
        return 'd';
    } else {
        // Staye in the same position -> same direction
        return m_Direction;
    }
}

void CGhost::chooseRandomMove(CMap& gameMap) {
	// Generate a pseudo random direction based on the current seed (time)
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