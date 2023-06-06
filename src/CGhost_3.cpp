#include "CGhost_3.hpp"
using namespace std;
using namespace std::chrono;

CGhost_3::CGhost_3() {
	m_Position = {0 ,0};
}

void CGhost_3::move(CMap& gameMap, const CPlayer& player) {
	auto currentTime = steady_clock::now();
    auto elapsedTime = duration_cast<milliseconds>(currentTime - m_PreviousTime).count();

    if (elapsedTime < m_Speed.count() + 200) {
        return;
	}

	srand(time(0));

	char tile = gameMap.m_CharMap[m_Position.first][m_Position.second];
	formatTile(tile);
    mvaddch(m_Position.first, m_Position.second, tile);

    decideMoveDirection(gameMap, player);

    attron(COLOR_PAIR(6));
    mvaddch(m_Position.first, m_Position.second, '0');
    attroff(COLOR_PAIR(6));

	m_PreviousTime = currentTime; // Update the timer
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
    if (checkCollisions(gameMap, 'w')) {
        ++m_Position.first;
		chooseRandomMove(gameMap);
	} else {
		m_Direction = 'w';
	}
}

void CGhost_3::mvDown(CMap& gameMap) {
    ++m_Position.first;
    if (checkCollisions(gameMap, 's')) {
        --m_Position.first;
		chooseRandomMove(gameMap);
	} else {
		m_Direction = 's';
	}
}

void CGhost_3::mvLeft(CMap& gameMap) {
    --m_Position.second;
    if (checkCollisions(gameMap, 'a')) {
        ++m_Position.second;
		chooseRandomMove(gameMap);
	} else {
		m_Direction = 'a';
	}
}

void CGhost_3::mvRight(CMap& gameMap) {
    ++m_Position.second;
    if (checkCollisions(gameMap, 'd')) {
        --m_Position.second;
		chooseRandomMove(gameMap);
	} else {
		m_Direction = 'd';
	}
}

void CGhost_3::chooseRandomMove(CMap& gameMap) {
	// Generate a pseudo random direction based on the current time
	int direction = rand() % 4 + 1;

	switch (direction) {
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

bool CGhost_3::checkCollisions(CMap& gameMap, char futureDirection) {
    vector<vector<char>> map = gameMap.m_CharMap;

	if (map[m_Position.first][m_Position.second] == 'T') {
		if (m_Position == gameMap.m_TeleportIn)
			m_Position = gameMap.m_TeleportOut;
		else
			m_Position = gameMap.m_TeleportIn;
    }

	return ( wallCollision(gameMap) || corridorCollision(map) || !checkDirectionOK(futureDirection) );
}