#include "CPlayer.hpp"
using namespace std;
using namespace std::chrono;


CPlayer::CPlayer() 
	: CEntity()
{
	m_PrevDirection = 'n';
	m_Score = 0;
	m_Lifes = 3;
	m_Character = 'p';
	m_EntityLook = 4;
	m_IsBerserk = false;

	m_BerserkTime = milliseconds(6000);
	m_Speed = milliseconds(160);
    m_PreviousTime = steady_clock::now(); // Initialize m_PreviousTime to the current time point
}

void CPlayer::move(CMap & gameMap) {
	m_CurrentTime = steady_clock::now();
    auto elapsedTime = duration_cast<milliseconds>(m_CurrentTime - m_PreviousTime);

	pair<size_t, size_t> prevPosition;
	prevPosition = m_Position;

	timeout(0);
	int userInput = tolower(getch());

	if (userInput != ERR ) {
		m_PrevDirection = m_Direction;
		m_Direction = userInput;
	}

	if (elapsedTime >= m_Speed) {
		mvaddch(m_Position.first, m_Position.second, ' ');
		
		decideMoveDirection(gameMap, *this);

		if (m_Position == prevPosition) {
			m_Direction = m_PrevDirection;
			decideMoveDirection(gameMap, *this);
		}

		m_PrevDirection = m_Direction;
        m_PreviousTime = m_CurrentTime;
    }
	
	// TODO - make attr variable for player character so that it will be formated automatically
	attron(COLOR_PAIR(4));
	mvaddch(m_Position.first, m_Position.second, m_Character);
	attroff(COLOR_PAIR(4));
}

void CPlayer::decideMoveDirection(CMap &gameMap, const CEntity &player) {
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
			break;
	}
}

void CPlayer::mvUp(CMap &gameMap) {
	pair<size_t, size_t> futurePosition = {m_Position.first-1, m_Position.second};
	if ( !checkIfCollisions(gameMap, futurePosition) )
		--m_Position.first;
}

void CPlayer::mvDown(CMap &gameMap) {
	pair<size_t, size_t> futurePosition = {m_Position.first+1, m_Position.second};
	if ( !checkIfCollisions(gameMap, futurePosition) )
		++m_Position.first;
}

void CPlayer::mvLeft(CMap &gameMap) {
	pair<size_t, size_t> futurePosition = {m_Position.first, m_Position.second-1};
	if ( !checkIfCollisions(gameMap, futurePosition) )
		--m_Position.second;
}

void CPlayer::mvRight(CMap &gameMap) {
	pair<size_t, size_t> futurePosition = {m_Position.first, m_Position.second+1};
	if ( !checkIfCollisions(gameMap, futurePosition) )
		++m_Position.second;
}

void CPlayer::collectCoin(CMap &gameMap) {
	gameMap.m_CharMap[m_Position.first][m_Position.second] = ' ';
	m_Score++;
}

bool CPlayer::checkIfCollisions(CMap &gameMap, pair<size_t, size_t> position) {
	vector<vector<char>> map = gameMap.m_CharMap;

	if (wallCollision(gameMap, position))
		return true;

	switch (map[position.first][position.second]) {
        case '.':
            collectCoin(gameMap);
            break;
        case 'B':
            collectCoin(gameMap);
            m_IsBerserk = true;
            break;
        case 'T':
            if (position == gameMap.m_TeleportIn)
                m_Position = gameMap.m_TeleportOut;
            else
                m_Position = gameMap.m_TeleportIn;
            break;
        default:
            break;
    }

	return ( corridorCollision(map, position) );
}