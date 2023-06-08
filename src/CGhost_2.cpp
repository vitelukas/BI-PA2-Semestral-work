#include "CGhost_2.hpp"
using namespace std;

CGhost_2::CGhost_2() 
	: CGhost() 
{
    m_Character = '@';
    m_EntityLook = 6;
}

void CGhost_2::decideMoveDirection(CMap& gameMap, const CPlayer& player) {
	size_t nextRow, nextCol;

	findShortestPath(gameMap , player, nextRow, nextCol);

    // Determine the next move based on the algorithm's found position
    if (nextRow < m_Position.first)
        mvUp(gameMap);
    else if (nextRow > m_Position.first)
        mvDown(gameMap);
    else if (nextCol < m_Position.second)
        mvLeft(gameMap);
    else if (nextCol > m_Position.second)
        mvRight(gameMap);
    else {
        CEntity::decideMoveDirection(gameMap);
		//todo pokud pozice zustane stejna, proved random pohyb
		//todo - if the position remains the same, make a random move
	}
		
}

// Perform BFS to find the shortest path to the player
void CGhost_2::findShortestPath(CMap& gameMap, const CPlayer& player, size_t &nextRow, size_t &nextCol) {
    vector<vector<bool>> visited(gameMap.m_Height, vector<bool>(gameMap.m_Width, false));
    vector<vector<pair<size_t, size_t>>> parent(gameMap.m_Height, vector<pair<size_t, size_t>>(gameMap.m_Width, make_pair(SIZE_MAX, SIZE_MAX)));
    char futureDir = 'n';
	pair<size_t, size_t> playersPosition = player.m_Position;

	if (player.m_Direction == 'a' || player.m_Direction == 'd') {
		playersPosition.second = min(player.m_Position.second + 4, gameMap.m_Width-2);
	} else {
		playersPosition.first = min(player.m_Position.first + 4, gameMap.m_Height-2);
		playersPosition.second = min(player.m_Position.second + 4, gameMap.m_Width-2);
	}

    // Repeat the BFS algorithm until we find a valid path towards the player
    // (if the current found path would mean that the ghost would have to turn around -> search again)
    do {
        queue<pair<size_t, size_t>> q;

        q.push(m_Position);
        visited[m_Position.first][m_Position.second] = true;

        while (!q.empty()) {
            pair<size_t, size_t> current = q.front();
            q.pop();

            if (current == playersPosition)
                break;

            // Check adjacent cells
            vector<pair<size_t, size_t>> neighbors = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
            for (const auto& neighbor : neighbors) {
                size_t x = current.second + neighbor.second;
                size_t y = current.first + neighbor.first;

                if ( !CEntity::checkIfCollisions(gameMap, {y, x}) && !visited[y][x] ) {
                    q.push({y, x});
                    visited[y][x] = true;
                    parent[y][x] = current;
                }
            }
        }

        // If the queue is empty and player's position is not reached, break the do while loop (BFS algorithm)
        if (q.empty()) {
            nextRow = m_Position.first;
            nextCol = m_Position.second;
            break;
        }

        // Trace back the path from player's position to ghost
        vector<pair<size_t, size_t>> path;
        pair<size_t, size_t> current = playersPosition;
        while (current != m_Position) {
            path.push_back(current);
            current = parent[current.first][current.second];
        }

        nextRow = path.back().first;
        nextCol = path.back().second;

        // (Re)set the temporary variables in case we would have to perform BFS again
        visited.assign(gameMap.m_Height, vector<bool>(gameMap.m_Width, false));
        parent.assign(gameMap.m_Height, vector<pair<size_t, size_t>>(gameMap.m_Width, make_pair(SIZE_MAX, SIZE_MAX)));
        path.clear();

        // Add the futurePosition into the visited in case it won't be valid ( == the direction to move towards this position is banned)
        visited[nextRow][nextCol] = true;

        pair<size_t, size_t> futurePos = make_pair(nextRow, nextCol);
        futureDir = determineDirection(futurePos);

    } while (!checkDirectionOK(futureDir));
}