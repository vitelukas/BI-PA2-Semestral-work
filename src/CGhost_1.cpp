#include "CGhost_1.hpp"
using namespace std;
using namespace std::chrono;

#include <queue>

CGhost_1::CGhost_1() {
	m_Position = {0 ,0};
}

void CGhost_1::move(CMap& gameMap, const CPlayer& player) {
	auto currentTime = steady_clock::now();
    auto elapsedTime = duration_cast<milliseconds>(currentTime - m_PreviousTime).count();

    if (elapsedTime < m_Speed.count() + 200 ||
		m_Position == player.m_Position) {
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

void CGhost_1::decideMoveDirection(CMap& gameMap, const CPlayer& player) {
    // Create a copy of the map to mark visited positions
    vector<vector<bool>> visited(gameMap.m_Height, vector<bool>(gameMap.m_Width, false));

    // Create a 2D array to store the distance from the ghost to each position
    vector<vector<int>> distance(gameMap.m_Height, vector<int>(gameMap.m_Width, INT_MAX));

    // Create a 2D array to store the previous position for each position in the path
    vector<vector<pair<size_t, size_t>>> previous(gameMap.m_Height, vector<pair<size_t, size_t>>(gameMap.m_Width, {-1, -1}));

    // Get the player's position
    const pair<size_t, size_t>& playerPosition = player.m_Position;

    // Perform BFS starting from the ghost's position
    queue<pair<size_t, size_t>> q;
    q.push(m_Position);
    visited[m_Position.first][m_Position.second] = true;
    distance[m_Position.first][m_Position.second] = 0;

    while (!q.empty()) {
        pair<size_t, size_t> current = q.front();
        q.pop();

        // Check if we reached the player's position
        if (current == playerPosition)
            break;

        // Check all four possible adjacent positions (up, down, left, right)
        vector<pair<size_t, size_t>> adjacent = {
            {current.first - 1, current.second},  // Up
            {current.first + 1, current.second},  // Down
            {current.first, current.second - 1},  // Left
            {current.first, current.second + 1}   // Right
        };

        for (const auto& pos : adjacent) {
            size_t row = pos.first;
            size_t col = pos.second;

            // Check if the position is valid and not visited
            if (row >= 0 && row < gameMap.m_Height && col >= 0 && col < gameMap.m_Width && !visited[row][col] && gameMap.m_CharMap[row][col] != '#' && 
				!(gameMap.m_CharMap[row][col] == ' ' && 
				(gameMap.m_CharMap[row][col - 1] == '#' ||  gameMap.m_CharMap[row][col + 1] == '#' ))) {
                q.push({row, col});
                visited[row][col] = true;
                distance[row][col] = distance[current.first][current.second] + 1;
                previous[row][col] = current;
            }
        }
    }

    // Find the shortest path from the ghost to the player using the distances and previous array
    pair<size_t, size_t> current = playerPosition;
    while (previous[current.first][current.second] != m_Position) {
        current = previous[current.first][current.second];
    }

    // Determine the direction based on the next position in the path
    size_t nextRow = current.first;
    size_t nextCol = current.second;

    if (nextRow < m_Position.first)
        mvUp(gameMap);
    else if (nextRow > m_Position.first)
        mvDown(gameMap);
    else if (nextCol < m_Position.second)
        mvLeft(gameMap);
    else if (nextCol > m_Position.second)
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

	if (map[m_Position.first][m_Position.second] == 'T') {
		if (m_Position == gameMap.m_TeleportIn)
			m_Position = gameMap.m_TeleportOut;
		else
			m_Position = gameMap.m_TeleportIn;
    }

	return ( wallCollision(gameMap) || corridorCollision(map) || !checkDirectionOK(futureDirection) );
}