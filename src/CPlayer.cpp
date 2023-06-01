#include "CPlayer.hpp"
using namespace std;

#include <ncurses.h>

CPlayer::CPlayer() {
	m_Score = 0;
	m_Lifes = 3;
	m_Position = {0, 0};
	m_Character = 'p';
}

void CPlayer::move(CMap &gameMap){
	char userInput = getch();
	mvaddch(m_Position.first, m_Position.second, ' ');
	switch (tolower(userInput)) {
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
			mvaddch(m_Position.first, m_Position.second, 'O');
			break;
	}
	attron(COLOR_PAIR(4));
	mvaddch(m_Position.first, m_Position.second, m_Character);
	attroff(COLOR_PAIR(4));
}

void CPlayer::mvUp(CMap &gameMap) {
	--m_Position.first;
	if (checkCollisions(gameMap))
		++m_Position.first;
}

void CPlayer::mvDown(CMap &gameMap) {
	++m_Position.first;
	if (checkCollisions(gameMap))
		--m_Position.first;
}

void CPlayer::mvLeft(CMap &gameMap) {
	--m_Position.second;
	if (checkCollisions(gameMap))
		++m_Position.second;
}

void CPlayer::mvRight(CMap &gameMap) {
	++m_Position.second;
	if (checkCollisions(gameMap))
		--m_Position.second;
}

void CPlayer::collectCoin(CMap &gameMap) {
	gameMap.m_CharMap[m_Position.first][m_Position.second] = ' ';
	m_Score++;
}

bool CPlayer::checkCollisions(CMap &gameMap) {
	vector<vector<char>> map = gameMap.m_CharMap;

	switch (map[m_Position.first][m_Position.second]) {
		case '.':
			collectCoin(gameMap);
			break;
		case 'T':
			m_Position = (m_Position == gameMap.m_TeleportIn ? gameMap.m_TeleportOut : gameMap.m_TeleportIn);
			break;
		case 'B':
			// goBerserk();
			break;
		default:
			break;
	}

	return map[m_Position.first][m_Position.second] == '#'
		|| m_Position.second >= gameMap.m_Width - 1
		|| m_Position.second < 0;
}