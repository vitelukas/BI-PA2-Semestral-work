#include "CPlayer.hpp"
using namespace std;
using namespace std::chrono;


CPlayer::CPlayer() {
	m_PrevDirection = 'n';
	m_Score = 0;
	m_Lifes = 3;
	m_Character = 'p';

	m_Speed = milliseconds(160);
	m_ElapsedTime = milliseconds(0);
    m_PreviousTime = steady_clock::now(); // Initialize m_PreviousTime to the current time point
}

void CPlayer::move(CMap & gameMap) {
	auto currentTime = steady_clock::now();
    m_ElapsedTime = duration_cast<milliseconds>(currentTime - m_PreviousTime);

	pair<size_t, size_t> prevPosition;
	prevPosition = m_Position;

	timeout(0);
	char userInput = tolower(getch());

	if (userInput != ERR ) {
		m_PrevDirection = m_Direction;
		m_Direction = userInput;
	}

	if (m_ElapsedTime >= m_Speed) {
		mvaddch(m_Position.first, m_Position.second, ' ');
		
		decideMoveDirection(gameMap);

		if (m_Position == prevPosition) {
			m_Direction = m_PrevDirection;
			decideMoveDirection(gameMap);
		}

		m_PrevDirection = m_Direction;
        m_PreviousTime = currentTime;
    }
	
	// TODO - make attr variable for player character so that it will be formated automatically
	attron(COLOR_PAIR(4));
	mvaddch(m_Position.first, m_Position.second, m_Character);
	attroff(COLOR_PAIR(4));
}

void CPlayer::decideMoveDirection(CMap &gameMap) {
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
			mvaddch(m_Position.first, m_Position.second, 'O');
			break;
	}
}

void CPlayer::mvUp(CMap &gameMap) {
	--m_Position.first;
	if (checkCollisions(gameMap))
		undoCollision(1, 1, gameMap);
}

void CPlayer::mvDown(CMap &gameMap) {
	++m_Position.first;
	if (checkCollisions(gameMap))
		undoCollision(1, 2, gameMap);
}

void CPlayer::mvLeft(CMap &gameMap) {
	--m_Position.second;
	if (checkCollisions(gameMap))
		undoCollision(2, 1, gameMap);
}

void CPlayer::mvRight(CMap &gameMap) {
	++m_Position.second;
	if (checkCollisions(gameMap))
		undoCollision(2, 2, gameMap);
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
        case 'B':
            // goBerserk();
            break;
        case 'T':
            if (m_Position == gameMap.m_TeleportIn)
                m_Position = gameMap.m_TeleportOut;
            else
                m_Position = gameMap.m_TeleportIn;
            break;
        default:
            break;
    }

	return ( wallCollision(gameMap) || corridorCollision(map) );
}

//? value == 1 -> increment
//? value == 2 -> decrement
void CPlayer::undoCollision(int coord, int value, CMap &gameMap) {
	if (coord == 1)
		value == 1 ? ++m_Position.first : --m_Position.first;
	else
		value == 1 ? ++m_Position.second : --m_Position.second;
}