#include "CGhost.hpp"
using namespace std;
using namespace std::chrono;

CGhost::CGhost(int entityLook)
	: CEntity(), m_GhostSlower(60)
{
	m_DirectionsTable = {
		{'w', 0},
        {'s', 1},
        {'a', 2},
        {'d', 3},
        {'n', 4},
	};
	m_BackDirections = {
		{0, 's'},
        {1, 'w'},
        {2, 'd'},
        {3, 'a'},
        {4, 'x'},
	};

	m_EntityLook = entityLook;
}

void CGhost::move(CMap& gameMap, const CPlayer& player) {
	m_CurrentTime = steady_clock::now();
    auto elapsedTime = duration_cast<milliseconds>(m_CurrentTime - m_PreviousTime).count();

	// Check if the time and decide whether to already move the ghost or not
    if (elapsedTime < m_Speed.count() + m_GhostSlower) {
        return;
	}

	// Set the seed for random generation based on the current time
	srand(time(0));

	// Format the tile the ghost is moving form so that he won't disrupt it
	char tile = gameMap.m_CharMap[m_Position.first][m_Position.second];
	formatTile(tile);
    mvaddch(m_Position.first, m_Position.second, tile);

	// If the player is in berserk mode, run away from him by choosing a random direction
	if (player.getBerserk()) {
		chooseRandomMove(gameMap);
	} else {
    	decideMoveDirection(gameMap, player);
	}

    attron(COLOR_PAIR(m_EntityLook));
    mvaddch(m_Position.first, m_Position.second, m_Character);
    attroff(COLOR_PAIR(m_EntityLook));

	m_PreviousTime = m_CurrentTime; // Update the timer
}

void CGhost::decideMoveDirection(CMap &gameMap, const CEntity &player) {
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

void CGhost::mvUp(CMap& gameMap) {
	pair<size_t, size_t> futurePosition = {m_Position.first-1, m_Position.second};
    if (checkIfCollisions(gameMap, futurePosition)) {
		chooseRandomMove(gameMap);
	} else {
	    --m_Position.first;
		m_Direction = 'w';
	}
}

void CGhost::mvDown(CMap& gameMap) {
	pair<size_t, size_t> futurePosition = {m_Position.first+1, m_Position.second};
    if (checkIfCollisions(gameMap, futurePosition)) {
		chooseRandomMove(gameMap);
	} else {
    	++m_Position.first;
		m_Direction = 's';
	}
}

void CGhost::mvLeft(CMap& gameMap) {
	pair<size_t, size_t> futurePosition = {m_Position.first, m_Position.second-1};
    if (checkIfCollisions(gameMap, futurePosition)) {
		chooseRandomMove(gameMap);
	} else {
    	--m_Position.second;
		m_Direction = 'a';
	}
}

void CGhost::mvRight(CMap& gameMap) {
	pair<size_t, size_t> futurePosition = {m_Position.first, m_Position.second+1};
    if (checkIfCollisions(gameMap, futurePosition)) {
		chooseRandomMove(gameMap);
	} else {
    	++m_Position.second;
		m_Direction = 'd';
	}
}

// Explained in CEntity
bool CGhost::checkIfCollisions(CMap &gameMap, pair<size_t, size_t> futurePosition) {
    vector<vector<char>> map = gameMap.m_CharMap;
	char futureDirection = determineDirection(futurePosition);

	if (wallCollision(gameMap, futurePosition))
		return true;

	if (map[futurePosition.first][futurePosition.second] == 'T') {
		if (futurePosition == gameMap.m_TeleportIn)
			m_Position = gameMap.m_TeleportOut;
		else
			m_Position = gameMap.m_TeleportIn;
    }
	// Additionaly check if moving to the future position would result in turning around and going backwards
	return ( corridorCollision(map, futurePosition) || !checkDirectionOK(futureDirection) );
}

bool CGhost::checkDirectionOK(char futureDirection) const {
	int dirToNum = m_DirectionsTable.at(m_Direction);
	char bannedDirection = m_BackDirections.at(dirToNum);
	
	// Compare the future direction with the banned direction for the current direction
	return !(bannedDirection == futureDirection);
}

char CGhost::determineDirection(pair<size_t, size_t> futurePos) const {
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
        // Stayed in the same position -> same direction
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