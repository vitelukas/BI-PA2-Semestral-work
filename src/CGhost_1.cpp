#include "CGhost_1.hpp"
using namespace std;
using namespace std::chrono;

CGhost_1::CGhost_1() {
	m_Position = {0 ,0};
}

void CGhost_1::move(CMap& gameMap, const CPlayer& player) {
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

    attron(COLOR_PAIR(5));
    mvaddch(m_Position.first, m_Position.second, '&');
    attroff(COLOR_PAIR(5));

	m_PreviousTime = currentTime; // Update the timer
}

void CGhost_1::decideMoveDirection(CMap& gameMap, const CPlayer & player) {
    if (player.m_Position.first < m_Position.first)
        mvUp(gameMap);
    else if (player.m_Position.first > m_Position.first)
        mvDown(gameMap);
    else if (player.m_Position.second < m_Position.second)
        mvLeft(gameMap);
    else if (player.m_Position.second > m_Position.second)
        mvRight(gameMap);
}

void CGhost_1::mvUp(CMap& gameMap) {
    --m_Position.first;
    if (checkCollisions(gameMap, 'w')) {
        ++m_Position.first;
	}
	m_Direction = 'w';
}

void CGhost_1::mvDown(CMap& gameMap) {
    ++m_Position.first;
    if (checkCollisions(gameMap, 's')) {
        --m_Position.first;
	}
	m_Direction = 's';
}

void CGhost_1::mvLeft(CMap& gameMap) {
    --m_Position.second;
    if (checkCollisions(gameMap, 'a')) {
        ++m_Position.second;
	}
	m_Direction = 'a';
}

void CGhost_1::mvRight(CMap& gameMap) {
    ++m_Position.second;
    if (checkCollisions(gameMap, 'd')) {
        --m_Position.second;
	}
	m_Direction = 'd';
}

bool CGhost_1::checkCollisions(CMap& gameMap, char futureDirection) {
    vector<vector<char>> map = gameMap.m_CharMap;

	return ( wallCollision(gameMap) || corridorCollision(map) || !checkDirectionOK(futureDirection) );
}